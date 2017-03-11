//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_QUADREEE_H
#define MZLIB_QUADREEE_H

#include "quadtree_node.h"
#include "quadtree_it_bodies.h"
#include "quadtree_it_masscentres.h"
#include "nature/vector.h"
#include "nature/body.h"
#include "utils/missing_std.h"
#include "screen_rectangle.h"
#include "lang/optional.h"
#include "lang/binary_options.h"
#include "unique.h"

namespace mzlib {
   
class quadtree
{
    
private:
    
   const double m_min_node_size;
   const double m_max_tree_size;
   std::shared_ptr<quadnode> m_root = nullptr;
   
   // A container for all bodies, even ones that didn't get into the tree itself.
   // Every self respecting container should store stuff it promises.
   std::vector<std::unique_ptr<body_core2d>> m_all_bodies;
   
   void create_root_from_location(const vector2d& location)
   {
      // todo: implement with operations over rectangles
      vector2d top_left    {location[0]-m_min_node_size, location[1]-m_min_node_size};
      vector2d bottom_right{location[0]+m_min_node_size, location[1]+m_min_node_size};
      m_root->create({top_left, bottom_right}, m_min_node_size);
   }
   
   void expand_tree_towards_location(const vector2d& location)
   {
      // get coordinates for new root
      const auto& old_root_rect = m_root->get_node_rectangle();
      mzlib::law::screen_rectangles2d law;
      law.consider(old_root_rect);
      direction expansion_direction = law.solve_for_direction_of_point(location);
      const auto enlarged_rectangle = law.enlarge_rectangle (expansion_direction, 2);
      
      if (law.solve_for_width()  >= m_max_tree_size ||
          law.solve_for_height() >= m_max_tree_size) {
         return; // don/t enlarge if it would make tree larger than max size
      }
      
      // create and groom new root
      std::shared_ptr<quadnode> new_root = std::make_shared<quadnode>();
      new_root->create(
         enlarged_rectangle,
         m_min_node_size);
      new_root->m_bodies.insert(
         new_root->m_bodies.begin(),
         m_root->m_bodies.begin(),
         m_root->m_bodies.end());

      // finally, substitute old root with new
      new_root->attach_child_node(
         the_opposite_direction(expansion_direction), 
         m_root);
      m_root = new_root;
   }
      
   void adjust_dynamic_tree (const vector2d& location)
   {
      if (!is_in(location)) {
         if (!m_root->has_children()) {
            create_root_from_location (location);
         }
         else {
            expand_tree_towards_location (location);
         }
      }
   }
   
   optional<int> find_index (const unique tag) const
   {
      optional<int> index;
      for (size_t i=0; i<m_all_bodies.size(); ++i) {
         if (m_all_bodies[i]->tag == tag) {
            index = i;
            break;
         }
      }
      return index;
   }
    
public:
       
   typedef quadtree_it_bodies      it_bodies;
   typedef quadtree_it_masscentres it_masscentres;
      
   explicit quadtree (
      const double min_node_size,
      const double max_tree_size) : 
         m_min_node_size (min_node_size),
         m_max_tree_size (max_tree_size),
         m_root (std::make_shared<quadnode>())
   {
   }
   
   quadtree (
      const screen_rectangle2d& rectangle, 
      const double min_node_size,
      const double max_tree_size) :
         quadtree (
            min_node_size,
            max_tree_size)
   {
      m_root->create(rectangle, m_min_node_size);
   }
        
   // can't allow copying due to std::unique_ptrs that are used
   quadtree (const quadtree&) = delete;
   quadtree& operator= (const quadtree&) = delete;
   
   // allow moving
   quadtree (quadtree && ) = default;
   quadtree& operator= (quadtree&&) = default;
   
   virtual ~quadtree () = default;
   
   unique add (std::unique_ptr<body_core2d> body)
   {
      unique tag = body->tag;
      adjust_dynamic_tree (body->centre.location);
      
      // Can still be out of the tree even after it has been resized, because it
      // might not have been: there is a defined limitation to the maximum tree
      // that will be respected by above function.
      
      // The fact that there is no check whether the location of body is in the tree
      // or not is because the quadtree_node::add function is resilient enough to
      // check this anyway, so there is not need to check twice. Especially so,
      // because nothing in particular needs to be done if it is not.
      
      m_root->add(body.get());
      m_all_bodies.push_back(std::move(body));
      return tag;
   }
   
   unique add_copy (const body_core2d& body_core) 
   {
      auto body_core_ptr = std::make_unique<body_core2d>(body_core);
      unique tag = add (std::move(body_core_ptr));
      return tag;
   }
   
   unique add_create (const vector2d location, const double mass = 0) 
   { 
      auto body_ptr = std::make_unique<body_core2d>();
      body_ptr->centre = {location, mass};
      unique tag = add (std::move(body_ptr));
      return tag;
   }
   
   option::exists move (const unique tag, vector2d new_location)
   {
      auto index = find_index (tag);
      if (!index.is_set()) return option::exists::no;
      
      adjust_dynamic_tree (new_location);
      m_root->move (tag,new_location);
      m_all_bodies[index.get()]->centre.location = new_location;
      return option::exists::yes;
   }
   
   option::changed change_mass (const unique tag, double new_mass)
   {
      return m_root->change_mass(tag,new_mass);
   }
   
   option::removed remove (const unique tag)
   {
      if(m_root->remove(tag) == option::removed::yes) {
         for(size_t i=0; i!=m_all_bodies.size(); ++i) {
            if( m_all_bodies[i]->tag == tag) {
               m_all_bodies.erase(m_all_bodies.begin() + i);
               return option::removed::yes;
            }
         }
      }
      return option::removed::no;
   }
   
   const mass_centre2d& get_mass_centre () const
   {
      return m_root->get_mass_centre();
   }
   
   const body_core2d* find (const unique tag) const
   {
      auto index = find_index (tag);
      if (index.is_set()) {
         return m_all_bodies[index.get()].get();
      }
      else {
         return nullptr;
      }
   }
   
   bool is_in (vector2d location) const 
   { 
      return m_root->is_in(location); 
   }

   it_bodies begin () const
   { 
      return it_bodies(m_all_bodies.begin()); 
   }
   
   it_bodies end () const
   { 
      return it_bodies(m_all_bodies.end()); 
   }
        
   it_masscentres begin_masscentres (const unique tag, double quotient)
   {
      return it_masscentres(m_root.get(), tag, quotient);
   }
   
   const it_masscentres end_masscentres () const
   {
      static it_masscentres end;
      return end; // to avoid creating new ends every time; I know they are all the same
   }
   
}; 
    
} // namespace

#endif	/* MZLIB_QUADREEE_H */

