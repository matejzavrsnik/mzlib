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
#include "vector.h"
#include "body.h"
#include "utils/missing_std.h"
#include "screen_rectangle.h"
#include "optional.h"
#include "binary_options.h"

namespace mzlib {
   
template<class T>
class quadtree
{
    
private:
    
   const double m_min_node_size;
   const double m_max_tree_size;
   std::shared_ptr<quadnode<T>> m_root = nullptr;
   
   // A container for all bodies, even ones that didn't get into the tree itself.
   // Every self respecting container should store stuff it promises.
   std::vector<std::unique_ptr<body_frame2d<T>>> m_all_bodies;
   
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
      std::shared_ptr<quadnode<T>> new_root = std::make_shared<quadnode<T>>();
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
   
   optional<int> find_index (const T& data)
   {
      optional<int> index;
      for (size_t i=0; i<m_all_bodies.size(); ++i) {
         if (m_all_bodies[i]->data == data) {
            index = i;
            break;
         }
      }
      return index;
   }
    
public:
       
   // And the 1st prize for the longest type name goes to:
   typedef quadtree_it_bodies<T>             it_bodies;
   typedef quadtree_it_masscentres<T>        it_masscentres;
      
   explicit quadtree (
      const double min_node_size,
      const double max_tree_size) : 
         m_min_node_size (min_node_size),
         m_max_tree_size (max_tree_size),
         m_root (std::make_shared<quadnode<T>>())
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
   
   void add (std::unique_ptr<body_frame2d<T>> mass_centre)
   {
      adjust_dynamic_tree (mass_centre->mass_c.location);
      
      // Can still be out of the tree even after it has been resized, because it
      // might not have been: there is a defined limitation to the maximum tree
      // that will be respected by above function.
      
      // The fact that there is no check whether the location of body is in the tree
      // or not is because the quadtree_node::add function is resilient enough to
      // check this anyway, so there is not need to check twice. Especially so,
      // because nothing in particular needs to be done if it is not.
      
      m_root->add(mass_centre.get());
      m_all_bodies.push_back(std::move(mass_centre));
   }
   
   void add (body_frame2d<T> mass_centre) 
   {
      auto mc_ptr = std::make_unique<body_frame2d<T>>(mass_centre);
      add (std::move(mc_ptr));
   }
   
   void add (T data, vector2d location, double mass = 0) 
   { 
      auto mc_ptr = std::make_unique<body_frame2d<T>>(data, location, mass);
      add (std::move(mc_ptr));
   }
   
   option::exists move (const T& data, vector2d new_location)
   {
      auto index = find_index (data);
      if (!index.is_set()) return option::exists::no;
      
      adjust_dynamic_tree (new_location);
      m_root->move (data,new_location);
      m_all_bodies[index.get()]->mass_c.location = new_location;
      return option::exists::yes;
   }
   
   option::changed change_mass (const T& data, double new_mass)
   {
      return m_root->change_mass(data,new_mass);
   }
   
   option::removed remove (const T& data)
   {
      if(m_root->remove(data) == option::removed::yes) {
         for(size_t i=0; i!=m_all_bodies.size(); ++i) {
            if( m_all_bodies[i]->data == data) {
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
   
   const body_frame2d<T>* find (const T& data)
   {
      auto index = find_index (data);
      if (index.is_set()) {
         return m_all_bodies[index.get()].get();
      }
      else {
         return nullptr;
      }
   }
   
   T& access_data(const body2d& body)
   {
      // I know it looks stupid, but why searching for the body again?
      // If someone deliberately wants to game the system, they can just 
      // const_cast themselves. There is no const police.
      return const_cast<T&>(body.data);
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
        
   it_masscentres begin_masscentres (const T& data, double quotient)
   {
      return it_masscentres(m_root.get(), data, quotient);
   }
   
   const it_masscentres end_masscentres () const
   {
      static it_masscentres end;
      return end; // to avoid creating new ends every time; I know they are all the same
   }
   
}; 
    
} // namespace

#endif	/* MZLIB_QUADREEE_H */

