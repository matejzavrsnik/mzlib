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
#include "quadtree_it_postorder.h"
#include "quadtree_it_breadthfirst.h"
#include "vector.h"
#include "body.h"
#include "utils_missing_std.h"
#include "rectangle.h"
#include "optional.h"
#include "enums.h"

namespace mzlib {
   
template<class T>
class cquadtree
{
    
private:
    
   std::shared_ptr<cquadnode<T>> m_root = nullptr;
   const double m_min_node_size;
   const double m_max_tree_size;
   
   // A container for all bodies, even ones that didn't get into the tree itself.
   // Every self respecting container should store stuff it promises.
   std::vector<std::unique_ptr<cbinded_mass_centre2d<T>>> m_all_bodies;
   
   void create_root_from_location(const cvector2d& location)
   {
      cvector2d top_left    {location[0]-m_min_node_size, location[1]-m_min_node_size};
      cvector2d bottom_right{location[0]+m_min_node_size, location[1]+m_min_node_size};
      m_root->create(top_left, bottom_right, m_min_node_size, nullptr);
   }
   
   void expand_tree_towards_location(const cvector2d& location)
   {
      // get coordinates for new root
      const auto& old_root_rect = m_root->get_node_rectangle();
      edirection expansion_direction = old_root_rect.direction_of_point (location);
      const auto enlarged_rectangle = old_root_rect.enlarge_rectangle (expansion_direction, 2);
      
      if (enlarged_rectangle.get_width()  >= m_max_tree_size ||
          enlarged_rectangle.get_height() >= m_max_tree_size) {
         return; // don/t enlarge if it would make tree larger than max size
      }
      
      // create and groom new root
      std::shared_ptr<cquadnode<T>> new_root = std::make_shared<cquadnode<T>>();
      new_root->create(
         enlarged_rectangle.get_top_left(), 
         enlarged_rectangle.get_bottom_right(), 
         m_min_node_size, 
         nullptr); // todo: not clear
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
      
   void adjust_dynamic_tree (const cvector2d& location)
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
   
   coptional<int> find_index (const T& data)
   {
      coptional<int> index;
      for (int i=0; i<m_all_bodies.size(); ++i) {
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
   typedef quadtree_it_nodes_postorder<T>    it_nodes_postorder;
   typedef quadtree_it_nodes_breadthfirst<T> it_nodes_breadthfirst;
      
   explicit cquadtree (
      const double min_node_size,
      const double max_tree_size) : 
         m_min_node_size (min_node_size),
         m_max_tree_size (max_tree_size),
         m_root (std::make_shared<cquadnode<T>>())
   {
   }
   
   cquadtree (
      const cvector2d& top_left, 
      const cvector2d& bottom_right, 
      const double min_node_size,
      const double max_tree_size) :
         cquadtree (
            min_node_size,
            max_tree_size)
   {
      m_root->create(top_left, bottom_right, m_min_node_size, nullptr);
   }
        
   // can't allow copying due to std::unique_ptrs that are used
   cquadtree (const cquadtree&) = delete;
   cquadtree& operator= (const cquadtree&) = delete;
   
   // allow moving
   cquadtree (cquadtree && ) = default;
   cquadtree& operator= (cquadtree&&) = default;
   
   virtual ~cquadtree () = default;
   
   void add (std::unique_ptr<cbinded_mass_centre2d<T>> mass_centre)
   {
      adjust_dynamic_tree (mass_centre->location);
      
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
   
   void add (cbinded_mass_centre2d<T> mass_centre) 
   {
      auto mc_ptr = std::make_unique<cbinded_mass_centre2d<T>>(mass_centre);
      add (std::move(mc_ptr));
   }
   
   void add (T data, cvector2d location, double mass = 0) 
   { 
      auto mc_ptr = std::make_unique<cbinded_mass_centre2d<T>>(data, location, mass);
      add (std::move(mc_ptr));
   }
   
   ebody_exists move (const T& data, cvector2d new_location)
   {
      auto index = find_index (data);
      if (!index.is_set()) return ebody_exists::no;
      
      adjust_dynamic_tree (new_location);
      m_root->move (data,new_location);
      m_all_bodies[index.get()]->location = new_location;
      return ebody_exists::yes;
   }
   
   bool change_mass (const T& data, double new_mass)
   {
      return m_root->change_mass(data,new_mass);
   }
   
   bool remove (const T& data)
   {
      if(m_root->remove(data)) {
         for(int i=0; i!=m_all_bodies.size(); ++i) {
            if( m_all_bodies[i]->data == data) {
               m_all_bodies.erase(m_all_bodies.begin() + i);
               return true;
            }
         }
      }
      return false;
   }
   
   const cmass_centre2d& get_mass_centre () const
   {
      return m_root->get_mass_centre();
   }
   
   const cbinded_mass_centre2d<T>* find (const T& data)
   {
      auto index = find_index (data);
      if (index.is_set()) {
         return m_all_bodies[index.get()].get();
      }
      else {
         return nullptr;
      }
   }
   
   T& access_data(const cbody2d& body)
   {
      // I know it looks stupid, but why searching for the body again?
      // If someone deliberately wants to game the system, they can just 
      // const_cast themselves. There is no const police.
      return const_cast<T&>(body.data);
   }
   
   bool is_in (cvector2d location) const 
   { 
      return m_root->is_in(location); 
   }

   it_bodies begin () const
   { 
      return it_bodies(m_all_bodies.cbegin()); 
   }
   
   it_bodies end () const
   { 
      return it_bodies(m_all_bodies.cend()); 
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
   
   it_nodes_postorder begin_nodes_postorder ()
   { 
      return it_nodes_postorder(m_root.get()); 
   }

   it_nodes_postorder end_nodes_postorder ()
   {
      return it_nodes_postorder(nullptr); 
   }
        
   it_nodes_breadthfirst begin_nodes_breadthfirst ()
   { 
      return it_nodes_breadthfirst(m_root.get()); 
   }
   
   it_nodes_breadthfirst end_nodes_breadthfirst ()
   { 
      return it_nodes_breadthfirst(nullptr); 
   }
}; 
    
} // namespace

#endif	/* MZLIB_QUADREEE_H */

