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
        
   // TODO: A monstrosity!! Space dimensions are undefined. Make quadtree dynamic at some point
   cuniverse (
      const mzlib::math::cvector2d& top_left, 
      const mzlib::math::cvector2d& bottom_right, 
      const double smallest_node_width) 
      : 
      m_bodies (
         top_left,
         bottom_right,
         smallest_node_width)
   {
   }

   cuniverse () : 
      m_bodies (
         {-10e50,-10e50},
         { 10e50, 10e50},
         10e50/2-1)
   {
   }

   cuniverse (const cuniverse&) = default;
   cuniverse (cuniverse && ) = default;
   cuniverse& operator= (const cuniverse&) = default;
   cuniverse& operator= (cuniverse&&) = default;
   ~cuniverse () = default;
        
   void add_body (cbody2d& body) 
   {
      m_bodies.add(body);
   }
   
   const cbody2d* find_body (cbody2d& body)
   {
      for (std::shared_ptr<cbody2d> found : m_bodies) {
         if (found->data == body.data) {
            return found.get();
         }
      }
      return nullptr;
   }
        
   cquadtree<cbody_properties2d>& get_bodies ()
   {
      return m_bodies;
   }
        
   void set_gravitational_constant (double gravitational_constant) 
   {
      m_gravitational_constant = gravitational_constant;
   }
        
   double get_gravitational_constant () const 
   {
      return m_gravitational_constant;
   }
        
   void set_law_of_gravitation (ilaw_of_gravitation2d new_law) 
   {
      m_fun_law_of_gravitation = new_law;
   }
        
   void calculate_forces () 
   {
      for (std::shared_ptr<cbody2d> this_body : m_bodies) {
         this_body->data.force = {0.0,0.0};
         for (std::shared_ptr<cbody2d> another_body : m_bodies) {
            if (this_body.get() != another_body.get()) {
               math::cvector2d gravity_force = m_fun_law_of_gravitation(
                  *this_body, 
                  *another_body, 
                  m_gravitational_constant);
               this_body->data.force += gravity_force;
            }
         }
      }
   }
        
   void calculate_positions (double time_pixel) 
   {
      for (std::shared_ptr<cbody2d> body : m_bodies) {
         math::cvector2d velocity_initial = body->data.velocity;
         math::cvector2d acceleration{0};
         acceleration = body->data.force / body->mass;
         math::cvector2d velocity_final = velocity_initial + acceleration * time_pixel;
         if (velocity_final.length() > m_max_velocity) {
            acceleration = {0.0,0.0};
            velocity_final = velocity_initial;
         }
         math::cvector2d location_final = (velocity_initial*time_pixel) + (acceleration*time_pixel)/2; 
         body->location += location_final;
         body->data.velocity = velocity_final;
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

   cquadtree<cbody_properties2d> m_bodies;
   double m_gravitational_constant = consts::gravitational_constant;
   double m_max_velocity = consts::light_speed;
   ilaw_of_gravitation2d m_fun_law_of_gravitation = universal_law_of_gravitation2d;
        
};

} // namespace mzlib

#endif // SPACE_H
