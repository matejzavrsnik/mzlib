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
   
   //todo: there are no tests for these
   using forces_applicator_function = std::function<void(const body_core2d&,mass_centre2d&)>;
   
   virtual unique add_copy (const body_core2d&) = 0;
   virtual void remove (const unique) = 0;
   virtual const body_core2d* find_body_core (const unique) const = 0;
   virtual void move (const unique, vector2d) = 0;
   virtual void for_every_mass_centre_combination (forces_applicator_function) = 0;

};

class universe_container_vector : public iuniverse_container
{
   
public:
   
   unique add_copy (const body_core2d& body) override
   {
      m_vector.push_back(body);
      return body.tag;
   }
   
   void remove (const unique tag) override
   {
      auto element_it = std::find_if(m_vector.begin(), m_vector.end(),
         [&tag](const body_core2d& element) {
            return element.tag == tag;
         });
      m_vector.erase(element_it);
   }
      
   const body_core2d* find_body_core (const unique tag) const override
   {
      for (const body_core2d& found : m_vector) {
         if (found.tag == tag) {
            return &found;
         }
      }
      return nullptr;
   }
   
   void move (const unique tag, vector2d new_location) override
   {
      for (body_core2d& found : m_vector) {
         if (found.tag == tag) {
            found.centre.location = new_location;
            break;
         }
      }
   }
   
   void for_every_mass_centre_combination (forces_applicator_function forces_applicator) override
   {
      for (body_core2d& this_body : m_vector) {
         for (body_core2d& that_body : m_vector) {
            if (this_body.tag != that_body.tag) { // body can't exert a force on itself,
               forces_applicator(this_body, that_body.centre);
            }
         }
      }         
   }
        
private:

   std::vector<body_core2d> m_vector;

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
   
   unique add_copy (const body_core2d& body) override
   {
      unique tag = m_quad_tree.add_copy(body);
      return tag;
   }
   
   void remove (const unique tag) override
   {
      m_quad_tree.remove(tag);
   }
   
   const body_core2d* find_body_core (const unique tag) const override
   {
      const body_core2d* body_core = m_quad_tree.find(tag);
      return body_core;
   }

   void move (const unique tag, vector2d new_location) override
   {
      m_quad_tree.move(tag, new_location);
   }
        
   void for_every_mass_centre_combination (forces_applicator_function forces_applicator) override
   {
      for (const body_core2d& this_body_core : m_quad_tree) {
         quadtree::it_masscentres mass_centres_it = 
            m_quad_tree.begin_masscentres(this_body_core.tag, m_quotient);
         for (; mass_centres_it != m_quad_tree.end_masscentres(); ++mass_centres_it) {
            forces_applicator(this_body_core, *mass_centres_it);
         }
      }
   }
        
private:

   quadtree m_quad_tree;
   double m_quotient;
   
};


} // namespace

#endif /* MZLIB_UNIVERSE_CONTAINERS_H */

