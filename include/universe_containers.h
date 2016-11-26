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
   
   virtual void add (cbody2d&) = 0;
   virtual void remove (const cbody2d&) = 0;
   virtual cbody2d const* find (const cbody2d&) const = 0;
   virtual void move (cbody2d&, cvector2d) = 0;
   virtual void for_every_mass_centre_combination (std::function<void(cbody2d&,cmass_centre2d&)>) = 0;
   virtual void for_every_body (std::function<void(cbody2d&)>) = 0;

};

class cuniverse_container_vector : public iuniverse_container
{
   
public:
   
   void add (cbody2d& body) 
   {
      m_vector.push_back(body);
   }
   
   void remove (const cbody2d& body)
   {
      std::remove_if(m_vector.begin(), m_vector.end(),
         [&body](const cbody2d& element) {
            return element.data == body.data;
         });         
   }
      
   cbody2d const* find (const cbody2d& body) const
   {
      for (const cbody2d& found : m_vector) {
         if (found.data == body.data) {
            return &found;
         }
      }         
      return nullptr;
   }
   
   void move (cbody2d& body, cvector2d new_location)
   {
      for (cbody2d& found : m_vector) {
         if (found.data == body.data) {
            found.mass_centre.location = new_location;
            break;
         }
      }
   }
   
   void for_every_mass_centre_combination (std::function<void(cbody2d&,cmass_centre2d&)> calculate_forces_operation)
   {
      for (cbody2d& this_body : m_vector) {
         for (cbody2d& that_body : m_vector) {
            if (this_body.data != that_body.data) { // body can't exert a force on itself,
               calculate_forces_operation(this_body, that_body.mass_centre);
            }
         }
      }         
   }
   
   void for_every_body (std::function<void(cbody2d&)> body_properties_operation)
   {
      for (cbody2d& body : m_vector) {
         body_properties_operation (body);
      }         
   }
   
        
private:

   std::vector<cbody2d> m_vector;

};

class cuniverse_container_quadtree : public iuniverse_container
{
   
public:
   
   cuniverse_container_quadtree (
      const crectangle2d& rectangle, 
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
 
   cuniverse_container_quadtree (
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

   
   cuniverse_container_quadtree (const cuniverse_container_quadtree&) = default;
   cuniverse_container_quadtree (cuniverse_container_quadtree&& ) = default;
   cuniverse_container_quadtree& operator= (const cuniverse_container_quadtree&) = default;
   cuniverse_container_quadtree& operator= (cuniverse_container_quadtree&&) = default;
   ~cuniverse_container_quadtree () = default;
   
   void add (cbody2d& body) 
   {
      m_quad_tree.add(body);
   }
   
   void remove (const cbody2d& body)
   {
      m_quad_tree.remove(body.data);
   }
      
   cbody2d const* find (const cbody2d& body) const
   {
      for (const cbody2d& found : m_quad_tree) {
         if (found.data == body.data) {
            return &found;
         }
      }
      return nullptr;
   }

   void move (cbody2d& body, cvector2d new_location)
   {
      m_quad_tree.move(body.data, new_location);
   }
        
   void for_every_mass_centre_combination (std::function<void(cbody2d&,cmass_centre2d&)> calculate_forces_operation)
   {
      for (cbody2d& this_body : m_quad_tree) {
         cquadtree<cbody_properties2d>::it_masscentres mass_centres_it = 
            m_quad_tree.begin_masscentres(this_body.data, m_quotient);
         for (; mass_centres_it != m_quad_tree.end_masscentres(); ++mass_centres_it) {
            calculate_forces_operation(this_body, *mass_centres_it);
         }
      }
   }
   
   
   void for_every_body (std::function<void(cbody2d&)> body_properties_operation)
   {
      for (cbody2d& body : m_quad_tree) {
         body_properties_operation (body);
      }
   }
        
private:

   cquadtree<cbody_properties2d> m_quad_tree; // if quadtree implementation chosen
   double m_quotient;

};


} // namespace

#endif /* MZLIB_UNIVERSE_CONTAINERS_H */

