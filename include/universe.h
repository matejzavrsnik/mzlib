//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_UNIVERSE_H
#define MZLIB_UNIVERSE_H

#include <vector>
#include <map>
#include <algorithm>

#include "body.h"
#include "consts.h"
#include "universe_containers.h"
#include "screen_rectangle.h"

#include "laws/constant_linear_acceleration.h"
#include "laws/acceleration.h"
#include "laws/gravitation.h"

namespace mzlib {
   
class universe
{
        
public:
   
   enum class implementation {
      barnes_hut,
      naive
   };
   
   enum class law_of_gravitation {
      realistic,
      entertaining
   };
   
   struct tproperties {
      double m_gravitational_constant = consts::gravitational_constant;
      double m_max_velocity = consts::light_speed;
      law_of_gravitation m_law_of_gravitation = law_of_gravitation::realistic;
      double m_barnes_hut_quotient = 1.5;
      implementation m_implementation = implementation::barnes_hut;
      optional<screen_rectangle2d> m_rectangle;
      double m_min_node_size = 10e50/8; // not a very efficient default, but it needs to cover the whole space
      double m_max_tree_size = 10e50;
   };
        
   universe ( 
      const screen_rectangle2d rectangle,
      const double min_node_size,
      const double max_tree_size) 
   {
      m_properties.m_rectangle = rectangle;
      m_properties.m_min_node_size = min_node_size;
      m_properties.m_max_tree_size = max_tree_size;
      apply_properties ();
   }
   
   universe ()
   {
      apply_properties(); // leave defaults
   }

   // can't allow copying because container uses std::unique_ptr
   universe& operator= (const universe&) = delete;
   universe (const universe&) = delete; 
   
   // allow move
   universe (universe && ) = default;
   universe& operator= (universe&&) = default;
   
   ~universe () = default;

   tproperties get_properties () 
   {
      return m_properties;
   }
   
   void set_properties (tproperties properties) 
   {
      m_properties = properties;
      apply_properties ();
   }
   
   // todo: rename to add_copy or something. or force people to std::move into. or something.
   void add (body2d& body) 
   {
      m_container->add(body);
      // Forces should show up immediately after adding
      calculate_forces();
   }
   
   void remove (const body2d& body)
   {
      m_container->remove(body.tag);
      // Forces should show up immediately after removing
      calculate_forces();
   }
   
   // todo: rethink this one. Why is it needed? it returns copy now.
   //       split to get_core and get_properties? return const reference and keep
   //       yet another collection of those?
   body2d find (const body2d& body) const
   {
      return m_container->find(body.tag);
   }
   
   void move (body2d& body, vector2d new_location)
   {
      m_container->move(body.tag, new_location);
   }
        
   void forward_time (double seconds, double time_pixel) 
   {
      // Time pixel idea stems from the fact that calculations are done in discreet time intervals.
      // If it is about some linear motion it doesn't matter, but if you are trying to calculate other
      // motions, particularly if over larger span of time, you might get dramatically different results
      // if you don't break the time in smaller chunks, time pixels. This way you can forward_time for
      // instance to one year in the future, but retain positions and forces recalculations on every 0.1 
      // seconds to minimise the error. Of course, you could as well call a function in a loop for a couple 
      // of times, but isn't it nicer to simply operate with points in time and not think about the rest?
      for (double time=0; time<seconds; time += time_pixel) {
         calculate_positions(time_pixel);
         calculate_forces();
      }
   }

   void for_every_body (std::function<void(body_core2d&,body_properties2d&)> execute)
   {
      m_container->for_every_body(execute);
   }
   
private:
        
   std::tuple<vector2d, vector2d> 
   calculate_final_velocity_and_position(
      const vector2d& gravity,
      const vector2d& velocity,
      const vector2d& location,
      const double mass,
      const double time) const
   {
      law::acceleration2d acceleration_equation;
      acceleration_equation.f = gravity;
      acceleration_equation.m = mass;
      acceleration_equation.solve_for_acceleration();

      law::constant_linear_acceleration2d final_parameters_equation;
      final_parameters_equation.a = acceleration_equation.a.get();
      final_parameters_equation.v_0 = velocity;
      final_parameters_equation.r_0 = location;
      final_parameters_equation.t = time;
      final_parameters_equation.solve_for_final_location();
      final_parameters_equation.solve_for_final_velocity();

      vector2d velocity_final = final_parameters_equation.v_f.get();
      vector2d location_final = final_parameters_equation.r_f.get();
      
      // cap it at predefined max velocity
      if (velocity_final.length() > m_properties.m_max_velocity) {
         velocity_final = velocity_final.normalise() * m_properties.m_max_velocity;
      }
      
      // ship it!
      return std::make_tuple(location_final, velocity_final);
   }

   void calculate_forces () 
   {
      body_core2d* previous_body = nullptr;
      m_container->for_every_mass_centre_combination(
         [this, &previous_body] (body_core2d& body_core,body_properties2d& body_properties, mass_centre2d& mass_c) 
         {
            if (previous_body != &body_core)
            {
               body_properties.gravity = {0.0,0.0};
               previous_body = &body_core;
            }
            law::gravitation2d law;
            law.m_1 = body_core.centre;
            law.m_2 = mass_c;
            law.G = m_properties.m_gravitational_constant;
            if (m_properties.m_law_of_gravitation == law_of_gravitation::realistic) {
               law.solve_for_force();
            }
            else {
               law.solve_for_fun_force();
            }
            body_properties.gravity += law.f_1.get();
         }
      );
   }
   
   void calculate_positions (double time_pixel) 
   {
      m_container->for_every_body(
         [this, &time_pixel](body_core2d& body_core,body_properties2d& body_properties)
         {
            vector2d location_final, velocity_final;
            // can't wait for "auto [location, velocity]" feature of C++17 !!
            std::tie(location_final, velocity_final) = calculate_final_velocity_and_position (
               body_properties.gravity, body_properties.velocity, body_core.centre.location, body_core.centre.mass, time_pixel);
            m_container->move (body_core.tag, location_final);
            body_properties.velocity = velocity_final;
         }
      );
   }
   
   void apply_properties () 
   {
      if (m_properties.m_implementation == implementation::barnes_hut) {
         if (m_properties.m_rectangle.is_set()) {
            m_container = std::make_unique<universe_container_quadtree>(
               m_properties.m_rectangle.get(),
               m_properties.m_min_node_size,
               m_properties.m_max_tree_size,
               m_properties.m_barnes_hut_quotient);            
         }
         else {
            m_container = std::make_unique<universe_container_quadtree>(
               m_properties.m_min_node_size,
               m_properties.m_max_tree_size,
               m_properties.m_barnes_hut_quotient);            
         }
      }
      else if (m_properties.m_implementation == implementation::naive) {
         m_container = std::make_unique<universe_container_vector>();
      }
   }
   
   std::unique_ptr<iuniverse_container> m_container;
   tproperties m_properties;

};

} // namespace

#endif /* MZLIB_UNIVERSE_H */

