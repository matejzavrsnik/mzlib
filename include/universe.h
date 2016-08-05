//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef SPACE_H
#define SPACE_H

#include <vector>
#include <map>
#include "vector.h"
#include "body.h"
#include "consts.h"
#include "quadtree.h"
#include "laws.h"

namespace mzlib {

class cuniverse
{
        
public:
   
   enum class implementation {
      barnes_hut,
      naive
   };
   
   struct tproperties {
      double m_gravitational_constant = consts::gravitational_constant;
      double m_max_velocity = consts::light_speed;
      ilaw_of_gravitation2d m_law_of_gravitation = universal_law_of_gravitation2d;
      double m_barnes_hut_quotient = 1.5;
      implementation m_implementation = implementation::barnes_hut;
   };
        
   // TODO: A monstrosity!! Space dimensions are undefined. Make quadtree dynamic at some point
   cuniverse (
      const mzlib::math::cvector2d& top_left, 
      const mzlib::math::cvector2d& bottom_right, 
      const double smallest_node_width) 
      : 
      m_quad_tree (
         top_left,
         bottom_right,
         smallest_node_width)
   {
   }

   cuniverse () : 
      m_quad_tree (
         mzlib::math::cvector2d({-10e50,-10e50}),
         mzlib::math::cvector2d({ 10e50, 10e50}),
         10e50/2-1)
   {
   }

   // prevent copying
   cuniverse (const cuniverse&) = delete;
   cuniverse& operator= (const cuniverse&) = delete;
   
   // allow moving
   cuniverse (cuniverse && ) = default;
   cuniverse& operator= (cuniverse&&) = default;
   
   ~cuniverse () = default;
        
   void add_body (cbody2d& body) 
   {
      if (m_properties.m_implementation == implementation::barnes_hut) {
         m_quad_tree.add(body);
      }
      else if (m_properties.m_implementation == implementation::naive) {
         m_vector.push_back(body);
      }
   }
   
   cbody2d const * find_body (const cbody2d& body) const
   {
      if (m_properties.m_implementation == implementation::barnes_hut) {
         for (const cbody2d& found : m_quad_tree) {
            if (found.data == body.data) {
               return &found;
            }
         }
      }
      else if (m_properties.m_implementation == implementation::naive) {
         for (const cbody2d& found : m_vector) {
            if (found.data == body.data) {
               return &found;
            }
         }         
      }
      return nullptr;
   }
        
   cquadtree<cbody_properties2d>& get_tree ()
   {
      return m_quad_tree;
   }
   
   std::vector<cbody2d>& get_vector ()
   {
      return m_vector;
   }
        
   tproperties get_properties () 
   {
      return m_properties;
   }
   
   void set_properties (tproperties properties) 
   {
      m_properties = properties;
   }
        
   void calculate_forces () 
   {
      if(m_properties.m_implementation == implementation::barnes_hut) {
         for (const cbody2d& this_body : m_quad_tree) {
            m_quad_tree.access_data(this_body).force = {0.0,0.0};
            cquadtree<cbody_properties2d>::it_masscentres mass_centres_it = 
               m_quad_tree.begin_masscentres(this_body.data, m_properties.m_barnes_hut_quotient);
            for (; mass_centres_it != m_quad_tree.end_masscentres(); ++mass_centres_it) {
               auto another_mass_centre = *mass_centres_it;
               math::cvector2d gravity_force = m_properties.m_law_of_gravitation(
                  this_body, 
                  another_mass_centre, 
                  m_properties.m_gravitational_constant);
               m_quad_tree.access_data(this_body).force += gravity_force;
            }
         }
      }
      else if(m_properties.m_implementation == implementation::naive) {
         for (cbody2d& this_body : m_vector) {
            this_body.data.force = {0.0,0.0};
            for (cbody2d& that_body : m_vector) {
               if (this_body.data != that_body.data) { // body can't exert a force on itself,
                  math::cvector2d gravity_force = m_properties.m_law_of_gravitation(
                     this_body, 
                     that_body, 
                     m_properties.m_gravitational_constant);
                  this_body.data.force += gravity_force;
               }
            }
         }         
      }
   }
        
   void calculate_positions (double time_pixel) 
   {
      if (m_properties.m_implementation == implementation::barnes_hut) {
         for (const cbody2d& body : m_quad_tree) {
            math::cvector2d velocity_initial = body.data.velocity;
            math::cvector2d acceleration{0};
            acceleration = body.data.force / body.mass;
            math::cvector2d velocity_final = velocity_initial + acceleration * time_pixel;
            if (velocity_final.length() > m_properties.m_max_velocity) {
               acceleration = {0.0,0.0};
               velocity_final = velocity_initial;
            }
            math::cvector2d location_final = (velocity_initial*time_pixel) + (acceleration*time_pixel)/2; 
            m_quad_tree.move(body.data, body.location + location_final);
            m_quad_tree.access_data(body).velocity = velocity_final;
         }
      }
      else if (m_properties.m_implementation == implementation::naive) {
         for (cbody2d& body : m_vector) {
            math::cvector2d velocity_initial = body.data.velocity;
            math::cvector2d acceleration{0};
            acceleration = body.data.force / body.mass;
            math::cvector2d velocity_final = velocity_initial + acceleration * time_pixel;
            if (velocity_final.length() > m_properties.m_max_velocity) {
               acceleration = {0.0,0.0};
               velocity_final = velocity_initial;
            }
            math::cvector2d location_final = (velocity_initial*time_pixel) + (acceleration*time_pixel)/2; 
            body.location += location_final;
            body.data.velocity = velocity_final;
         }         
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
        
private:

   cquadtree<cbody_properties2d> m_quad_tree; // if quadtree implementation chosen
   std::vector<cbody2d> m_vector; // if naive implementation chosen
   tproperties m_properties;

};

} // namespace mzlib

#endif // SPACE_H

