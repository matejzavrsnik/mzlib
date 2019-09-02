//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_UNIVERSE_H
#define MZLIB_UNIVERSE_H

#include "body.h"
#include "consts.h"
#include "universe_containers.h"
#include "screen_rectangle.h"
#include "../laws/constant_linear_acceleration.h"
#include "../laws/acceleration.h"
#include "../laws/gravitation.h"
#include <map>

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
      std::optional<screen_rectangle2d> m_rectangle;
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
   
   unique add_copy (const body2d& body) 
   {
      unique tag = m_body_cores->add_copy(body.core);
      m_full_bodies[tag] = body;
      // Forces should show up immediately after adding
      calculate_forces();
      return tag;
   }
   
   void remove (const unique tag)
   {
      m_body_cores->remove(tag);
      auto found = m_full_bodies.find(tag);
      if (found != m_full_bodies.end()) {
         m_full_bodies.erase(found);
      }
      // Forces should show up immediately after removing
      calculate_forces();
   }
   
   const body_core2d& get_body_core (const unique tag) const
   {
      auto found = m_full_bodies.find(tag);
      if (found != m_full_bodies.end()) {
         return found->second.core;
      }
      throw mzlib::exception::not_found();
   }
   
   body_properties2d& get_body_properties (const unique tag)
   {
      auto found = m_full_bodies.find(tag);
      if (found != m_full_bodies.end()) {
         return found->second.properties;
      }
      throw mzlib::exception::not_found();
   }
   
   void move (const unique tag, const vector2d new_location)
   {
      m_body_cores->move(tag, new_location);
      auto found = m_full_bodies.find(tag);
      if (found != m_full_bodies.end()) {
         found->second.core.centre.location = new_location;
      }
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

   void for_each_body_core (std::function<void(const body_core2d&)> body_core_fun)
   {
      for(const auto& body_pair : m_full_bodies) {
         body_core_fun (body_pair.second.core);
      }
   }
   
   void for_each_body_properties (std::function<void(body_properties2d&)> body_properties_fun)
   {
      for(auto& body_pair : m_full_bodies) {
         body_properties_fun (body_pair.second.properties);
      }
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
      final_parameters_equation.a = acceleration_equation.a.value();
      final_parameters_equation.v_0 = velocity;
      final_parameters_equation.r_0 = location;
      final_parameters_equation.t = time;
      final_parameters_equation.solve_for_final_location();
      final_parameters_equation.solve_for_final_velocity();

      vector2d velocity_final = final_parameters_equation.v_f.value();
      vector2d location_final = final_parameters_equation.r_f.value();
      
      // cap it at predefined max velocity
      if (law::vector::length(velocity_final) > m_properties.m_max_velocity) {
         velocity_final = law::vector::normalise(velocity_final) * m_properties.m_max_velocity;
      }
      
      // ship it!
      return std::make_tuple(location_final, velocity_final);
   }

   void calculate_forces () 
   {
      const body_core2d* previous_body = nullptr;
      m_body_cores->for_every_mass_centre_combination(
         [this, &previous_body] (const body_core2d& body_core, mass_centre2d& mass_c) 
         {
            if (previous_body != &body_core)
            {
               get_body_properties(body_core.tag).gravity = {0.0,0.0};
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
            get_body_properties(body_core.tag).gravity += law.f_1.value();
         }
      );
   }
   
   void calculate_positions (double time_pixel) 
   {
      for(auto& body_pair : m_full_bodies)
      {
         body_properties2d& body_properties = body_pair.second.properties;
         body_core2d& body_core = body_pair.second.core;
         auto [location_final, velocity_final] = calculate_final_velocity_and_position (
            body_properties.gravity, body_properties.velocity, body_core.centre.location, body_core.centre.mass, time_pixel);
         m_body_cores->move (body_core.tag, location_final);
         body_core.centre.location = location_final;
         body_properties.velocity = velocity_final;
      };
   }
   
   void apply_properties () 
   {
      if (m_properties.m_implementation == implementation::barnes_hut) {
         if (m_properties.m_rectangle.has_value()) {
            m_body_cores = std::make_unique<universe_container_quadtree>(
               m_properties.m_rectangle.value(),
               m_properties.m_min_node_size,
               m_properties.m_max_tree_size,
               m_properties.m_barnes_hut_quotient);            
         }
         else {
            m_body_cores = std::make_unique<universe_container_quadtree>(
               m_properties.m_min_node_size,
               m_properties.m_max_tree_size,
               m_properties.m_barnes_hut_quotient);            
         }
      }
      else if (m_properties.m_implementation == implementation::naive) {
         m_body_cores = std::make_unique<universe_container_vector>();
      }
   }
   
   // Why are body properties held separately in a map, and not in the body containers
   // themselves? Body properties semantically do not belong to the body itself; an
   // argument being the body can still be the same body even when forces on the body
   // and other such properties change. As an extention, properties do not belong to 
   // a collection of bodies. Other thing to consider is speed. More bodies fit in
   // cache at the same time and that can have measurable speed improvements when
   // iterating (see my blog post). And for any decent simulation I need to do lots
   // of iterating. Now to the part about why the rest of the body data and why map? 
   // According to standard, insertions and deletions from map will not invalidate 
   // existing references (23.1.2/8: "The insert members shall not affect the validity 
   // of iterators and references to the container, and the erase members shall 
   // invalidate only iterators and references to the erased elements.") This is 
   // handy for users of this class because they can just monitor these references 
   // and see the changes whenever they see fit, without additional hassle.

   std::unique_ptr<iuniverse_container> m_body_cores;
   std::map<unique, body2d> m_full_bodies;
   tproperties m_properties;

};

} // namespace

#endif /* MZLIB_UNIVERSE_H */
