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
#include <map>

#include "vector.h"
#include "body.h"
#include "quadtree.h"

namespace mzlib {

class iuniverse_container
{
   
public:
   
   virtual void add (body2d&) = 0;
   virtual void remove (const int) = 0;
   virtual body2d find (const int) const = 0;
   virtual void move (const int, vector2d) = 0;
   // todo: make some nicer typedef signature
   // todo: make core const, now it can be done
   virtual void for_every_mass_centre_combination (std::function<void(body_core2d&,body_properties2d&,mass_centre2d&)>) = 0;
   virtual void for_every_body (std::function<void(body_core2d&,body_properties2d&)>) = 0;

};

class universe_container_vector : public iuniverse_container
{
   
public:
   
   void add (body2d& body) 
   {
      m_vector.push_back(body);
   }
   
   void remove (const int tag)
   {
      std::remove_if(m_vector.begin(), m_vector.end(),
         [&tag](const body2d& element) {
            return element.tag.id() == tag;
         });         
   }
      
   body2d find (const int tag) const
   {
      for (const body2d& found : m_vector) {
         if (found.tag.id() == tag) {
            return found;
         }
      }
      throw mzlib::exception::not_found();
   }
   
   void move (const int tag, vector2d new_location)
   {
      for (body2d& found : m_vector) {
         if (found.tag.id() == tag) {
            found.centre.location = new_location;
            break;
         }
      }
   }
   
   void for_every_mass_centre_combination (std::function<void(body_core2d&,body_properties2d&,mass_centre2d&)> calculate_forces_operation)
   {
      for (body2d& this_body : m_vector) {
         for (body2d& that_body : m_vector) {
            if (this_body.tag.id() != that_body.tag.id()) { // body can't exert a force on itself,
               calculate_forces_operation(this_body, this_body.properties, that_body.centre);
            }
         }
      }         
   }
   
   void for_every_body (std::function<void(body_core2d&,body_properties2d&)> body_properties_operation)
   {
      for (body2d& body : m_vector) {
         body_properties_operation (body, body.properties);
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
      m_body_properties[body.tag.id()] = body.properties;
   }
   
   void remove (const int tag)
   {
      m_quad_tree.remove(tag);
      auto found = m_body_properties.find(tag);
      if (found != m_body_properties.end()) {
         m_body_properties.erase(found);
      }
   }
   
   body2d find (const int tag) const
   {
      auto body_core = m_quad_tree.find(tag);
      if (body_core == nullptr) {
         throw mzlib::exception::not_found();
      }
      
      return recreate_body(body_core);
   }

   void move (const int tag, vector2d new_location)
   {
      m_quad_tree.move(tag, new_location);
   }
        
   void for_every_mass_centre_combination (std::function<void(body_core2d&,body_properties2d&,mass_centre2d&)> calculate_forces_operation)
   {
      for (body_core2d& this_body_core : m_quad_tree) {
         quadtree::it_masscentres mass_centres_it = 
            m_quad_tree.begin_masscentres(this_body_core.tag.id(), m_quotient);
         for (; mass_centres_it != m_quad_tree.end_masscentres(); ++mass_centres_it) {
            calculate_forces_operation(this_body_core, m_body_properties[this_body_core.tag.id()], *mass_centres_it);
         }
      }
   }
   
   
   void for_every_body (std::function<void(body_core2d&,body_properties2d&)> body_properties_operation)
   {
      for (body_core2d& body_core : m_quad_tree) {
         body_properties_operation (body_core, m_body_properties[body_core.tag.id()]);
      }
   }
        
private:

   quadtree m_quad_tree;
   std::map<int, body_properties2d> m_body_properties;
   double m_quotient;

   body2d recreate_body(const body_core2d* const body_core) const
   {
      auto body_properties = m_body_properties.find(body_core->tag.id());
      if (body_properties == m_body_properties.end()) {
         throw mzlib::exception::not_found();
      }
      
      body2d found_body;
      found_body.centre = body_core->centre;
      found_body.tag = body_core->tag;
      found_body.properties = body_properties->second;
      return found_body;
   }
   
};


} // namespace

#endif /* MZLIB_UNIVERSE_CONTAINERS_H */

