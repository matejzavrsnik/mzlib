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

namespace mzlib {
   
template<class T>
class cquadtree
{
    
private:
    
   std::shared_ptr<cquadnode<T>> m_root = nullptr;
   const double m_smallest_node_width;
   // A container for all bodies, even ones that didn't get into the tree itself.
   // Every self respecting container should store stuff it promises.
   std::vector<std::unique_ptr<cbinded_mass_centre2d<T>>> m_all_bodies;
   
   void create_root_from_location(const cvector2d location)
   {
      cvector2d top_left    {location[0]-m_smallest_node_width, location[1]-m_smallest_node_width};
      cvector2d bottom_right{location[0]+m_smallest_node_width, location[1]+m_smallest_node_width};
      m_root->create(top_left, bottom_right, m_smallest_node_width, nullptr);
   }
    
public:
       
   // And the 1st prize for the longest type name goes to:
   typedef quadtree_it_bodies<T> it_bodies;
   typedef quadtree_it_masscentres<T>        it_masscentres;
   typedef quadtree_it_nodes_postorder<T>    it_nodes_postorder;
   typedef quadtree_it_nodes_breadthfirst<T> it_nodes_breadthfirst;
      
   explicit cquadtree (const double smallest_node_width) :
      m_smallest_node_width(smallest_node_width),
      m_root(std::make_shared<cquadnode<T>>())
   {
      
   }
   
   cquadtree (
      const cvector2d& top_left, 
      const cvector2d& bottom_right, 
      const double smallest_node_width ) :
      cquadtree (smallest_node_width)
   {
      m_root->create(top_left, bottom_right, m_smallest_node_width, nullptr);
   }
        
   // can't allow copying due to std::unique_ptrs that are used
   cquadtree (const cquadtree&) = delete;
   cquadtree& operator= (const cquadtree&) = delete;
   
   // allow moving
   cquadtree (cquadtree && ) = default;
   cquadtree& operator= (cquadtree&&) = default;
   
   virtual ~cquadtree () = default;
   
   bool add (cbinded_mass_centre2d<T> mass_centre) 
   {
      if (!is_in(mass_centre.location)) {
         if (!m_root->has_children()) {
            // create
            create_root_from_location (mass_centre.location);
         }
         else {
            // expand
            edirection expansion_direction = m_root->get_node_rectangle().direction_of_point(mass_centre.location);
            const crectangle2d enlarged_rectangle = m_root->get_node_rectangle().enlarge_rectangle (expansion_direction, 2);
            std::shared_ptr<cquadnode<T>> new_root = std::make_shared<cquadnode<T>>();
            new_root->attach_child_node(
               the_opposite_direction(expansion_direction), 
               m_root);
            new_root->create(
               enlarged_rectangle.get_top_left(), 
               enlarged_rectangle.get_bottom_right(), 
               m_smallest_node_width, 
               nullptr);
            m_root = new_root;
         }
      }
      std::unique_ptr<cbinded_mass_centre2d<T>> mass_centre_ptr = 
         std::make_unique<cbinded_mass_centre2d<T>>(mass_centre);
      m_root->add(mass_centre_ptr.get());
      m_all_bodies.push_back(std::move(mass_centre_ptr));
      return true;
   }
   
   bool add (T data, cvector2d location, double mass = 0) 
   { 
      if (!is_in(location)) { 
         create_root_from_location (location);
      }
      std::unique_ptr<cbinded_mass_centre2d<T>> mass_centre_ptr = 
         std::make_unique<cbinded_mass_centre2d<T>>(data, location, mass);
      m_root->add(mass_centre_ptr.get());
      m_all_bodies.push_back(std::move(mass_centre_ptr));
      return true;
   }
   
   bool move (const T& data, cvector2d new_location)
   {
      bool moved_into_tree = m_root->move(data,new_location);
      
      // if moving within the tree didn't succeed, but has been added to the tree,
      // change properties on the body anyway and if new location is in the tree,
      // re-insert it again
      if(!moved_into_tree) { 
         for(int i=0; i!=m_all_bodies.size(); ++i) {
            if( m_all_bodies[i]->data == data) {
               if(m_root->is_in(new_location)) {
                  auto mass_centre_it = (m_all_bodies.begin() + i);
                  cbinded_mass_centre2d<T>* mass_centre_ptr = (*mass_centre_it).get();
                  m_root->add(mass_centre_ptr); // add back
                  moved_into_tree = true;
               }
               else {
                  m_all_bodies[i]->location = new_location;
                  moved_into_tree = false;
               }
               break;
            }
         }
      }
      return moved_into_tree;
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
      return m_root->find(data);
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

