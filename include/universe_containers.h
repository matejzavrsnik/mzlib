//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_UNIVERSE_CONTAINERS_H
#define MZLIB_UNIVERSE_CONTAINERS_H

#include <vector>
#include <algorithm>

#include "vector.h"
#include "body.h"
#include "quadtree.h"

namespace mzlib {

class iuniverse_container
{
   
public:
   
   virtual void add (body2d&) = 0;
   virtual void remove (const body2d&) = 0;
   virtual body2d const* find (const body2d&) const = 0;
   virtual void move (body2d&, vector2d) = 0;
   virtual void for_every_mass_centre_combination (std::function<void(body2d&,mass_centre2d&)>) = 0;
   virtual void for_every_body (std::function<void(body2d&)>) = 0;

};

class universe_container_vector : public iuniverse_container
{
   
public:
   
   void add (body2d& body) 
   {
      m_vector.push_back(body);
   }
   
   void remove (const body2d& body)
   {
      std::remove_if(m_vector.begin(), m_vector.end(),
         [&body](const body2d& element) {
            return element.tag.id() == body.tag.id();
         });         
   }
      
   body2d const* find (const body2d& body) const
   {
      for (const body2d& found : m_vector) {
         if (found.tag.id() == body.tag.id()) {
            return &found;
         }
      }         
      return nullptr;
   }
   
   void move (body2d& body, vector2d new_location)
   {
      for (body2d& found : m_vector) {
         if (found.tag.id() == body.tag.id()) {
            found.mass_c.location = new_location;
            break;
         }
      }
   }
   
   void for_every_mass_centre_combination (std::function<void(body2d&,mass_centre2d&)> calculate_forces_operation)
   {
      for (body2d& this_body : m_vector) {
         for (body2d& that_body : m_vector) {
            if (this_body.tag.id() != that_body.tag.id()) { // body can't exert a force on itself,
               calculate_forces_operation(this_body, that_body.mass_c);
            }
         }
      }         
   }
   
   void for_every_body (std::function<void(body2d&)> body_properties_operation)
   {
      for (body2d& body : m_vector) {
         body_properties_operation (body);
      }         
   }
   
        
private:

   std::vector<body2d> m_vector;

};

class universe_container_quadtree : public iuniverse_container
{
   
public:
   
   universe_container_quadtree (
      const screen_rectangle2d& rectangle, 
      const double min_node_size,
      const double max_tree_size,
      const double quotient) 
         : 
      m_quad_tree (
         rectangle,
         min_node_size,
         max_tree_size),
      m_quotient (quotient)
   {
   }
 
   universe_container_quadtree (
      const double min_node_size,
      const double max_tree_size,
      const double quotient) 
         : 
      m_quad_tree ( // not a very efficient default, but it needs to cover the whole space
         min_node_size,
         max_tree_size),
      m_quotient (quotient)
   {
   }

   
   universe_container_quadtree (const universe_container_quadtree&) = default;
   universe_container_quadtree (universe_container_quadtree&& ) = default;
   universe_container_quadtree& operator= (const universe_container_quadtree&) = default;
   universe_container_quadtree& operator= (universe_container_quadtree&&) = default;
   ~universe_container_quadtree () = default;
   
   void add (body2d& body) 
   {
      m_quad_tree.add(body);
   }
   
   void remove (const body2d& body)
   {
      m_quad_tree.remove(body.tag.id());
   }
      
   body2d const* find (const body2d& body) const
   {
      for (const body2d& found : m_quad_tree) {
         if (found.tag.id()== body.tag.id()) {
            return &found;
         }
      }
      return nullptr;
   }

   void move (body2d& body, vector2d new_location)
   {
      m_quad_tree.move(body.tag.id(), new_location);
   }
        
   void for_every_mass_centre_combination (std::function<void(body2d&,mass_centre2d&)> calculate_forces_operation)
   {
      for (body2d& this_body : m_quad_tree) {
         quadtree<body_properties2d>::it_masscentres mass_centres_it = 
            m_quad_tree.begin_masscentres(this_body.tag.id(), m_quotient);
         for (; mass_centres_it != m_quad_tree.end_masscentres(); ++mass_centres_it) {
            calculate_forces_operation(this_body, *mass_centres_it);
         }
      }
   }
   
   
   void for_every_body (std::function<void(body2d&)> body_properties_operation)
   {
      for (body2d& body : m_quad_tree) {
         body_properties_operation (body);
      }
   }
        
private:

   quadtree<body_properties2d> m_quad_tree; // if quadtree implementation chosen
   double m_quotient;

};


} // namespace

#endif /* MZLIB_UNIVERSE_CONTAINERS_H */

