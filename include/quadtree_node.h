//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_QUADTREE_NODE_H
#define	MZLIB_QUADTREE_NODE_H

#include <memory>
#include <algorithm> // std::find_if
#include "vector.h"
#include "mass_centre.h"
#include "utils_missing_std.h"
#include "body.h"
#include "rectangle.h"
#include "enums.h"

namespace mzlib {

// Assumptions to be aware of: 
//    - The coordinate system is such that values increase down (south) and right (east).
//    - Leftmost (E) and topmost (N) coordinates are exclusive.
//    - Rightmost (W) and downmost (S) coordinates are inclusive.
//    - Assumed order of iteration where it matters is nw -> ne -> sw -> se

template <class T> class cquadtree;
template <class T> class quadtree_it_bodies;
template <class T> class quadtree_it_masscentres;
template <class T> class quadtree_it_nodes_postorder;
template <class T> class quadtree_it_nodes_breadthfirst;
    
template<class T>
class cquadnode : public std::enable_shared_from_this<cquadnode<T>>
{
   
   friend class cquadtree<T>;
   friend class quadtree_it_bodies<T>;
   friend class quadtree_it_masscentres<T>;
   friend class quadtree_it_nodes_postorder<T>;
   friend class quadtree_it_nodes_breadthfirst<T>;
        
public:

   cquadnode() {}
   cquadnode(const cquadnode&) = delete;
   cquadnode(cquadnode && ) = delete;
   cquadnode& operator=(const cquadnode&) = delete;
   cquadnode& operator=(cquadnode&&) = delete;
   virtual ~cquadnode() = default;

   // Creation needs to be done outside the constructor, because to be able to call shared_from_this(),
   // an object needs an owning shared_ptr, otherwise there is risk of two shared_ptrs owning same object.
   void create (
      const crectangle2d& rectangle, 
      const double smallest_node_width, 
      std::shared_ptr<cquadnode> parent = nullptr) 
   {
      m_parent = parent;
      m_rectangle = rectangle;
      m_diagonal_length = m_rectangle.get_diagonal_length();
      if (m_rectangle.get_width() > smallest_node_width) {
         const cvector2d centre_point = m_rectangle.calculate_centre_point();
         
         // Set mass centre in the centre of the node, even if 0. Philosophical, huh?
         m_mass_centre.location = centre_point;
         
         const crectangle2d nw_rect(m_rectangle.get_top_left(), centre_point);
         if (m_child_nw == nullptr) {
            m_child_nw = std::make_shared<cquadnode<T>>();
            m_child_nw->create(nw_rect, smallest_node_width, this->shared_from_this());
         }
         if (m_child_ne == nullptr) {
            m_child_ne = std::make_shared<cquadnode<T>>();
            const crectangle2d ne_rect = nw_rect.flip(edirection::e);
            m_child_ne->create(ne_rect, smallest_node_width, this->shared_from_this());
         }
         if (m_child_sw == nullptr) {
            m_child_sw = std::make_shared<cquadnode<T>>();
            const crectangle2d sw_rect = nw_rect.flip(edirection::s);
            m_child_sw->create(sw_rect, smallest_node_width, this->shared_from_this());
         }
         if (m_child_se == nullptr) {
            m_child_se = std::make_shared<cquadnode<T>>();
            const crectangle2d se_rect = nw_rect.flip(edirection::se);
            m_child_se->create(se_rect, smallest_node_width, this->shared_from_this());
         }
      }
   }

   void add (cbinded_mass_centre2d<T>* mass_centre) 
   {
      // It is important that the is_in check is here, because it is not in
      // the quadtree class when it calls this function. Something needs to
      // check it, and it is redundant to check twice, so here it is.
      if (is_in(mass_centre->location)) {
         // insert
         m_bodies.push_back(mass_centre);
         m_mass_centre.add_to_mass_centre(*mass_centre);
         if (is_leaf()) return; // nothing more to do
         // if has children, insert there as well
         if      (m_child_nw->is_in(mass_centre->location)) m_child_nw->add(mass_centre);
         else if (m_child_ne->is_in(mass_centre->location)) m_child_ne->add(mass_centre);
         else if (m_child_sw->is_in(mass_centre->location)) m_child_sw->add(mass_centre);
         else if (m_child_se->is_in(mass_centre->location)) m_child_se->add(mass_centre);
      }
   }
   
   eremoved remove (const T& data) 
   {
      // downside of the approach where every node contains all bodies under it: 
      // every subnode needs to find mass centre in it's own collection
      auto mass_centre_it = find_body(data);
      // if no such mass centre here, go away
      if (mass_centre_it == m_bodies.end()) return eremoved::no; 
      // if found, convert to mass centre ptr
      cbinded_mass_centre2d<T>* mass_centre_ptr = *mass_centre_it;
      // start removing
      // no need to check if it is in the node, because of course it is; checked earlier
      m_bodies.erase(mass_centre_it);
      m_mass_centre.remove_from_mass_centre(*mass_centre_ptr);
      // if leaf, this operation is done
      if (is_leaf()) return eremoved::yes;
      // if not leaf, delete in children too
      if      (m_child_nw->is_in(mass_centre_ptr->location)) return m_child_nw->remove(data);
      else if (m_child_ne->is_in(mass_centre_ptr->location)) return m_child_ne->remove(data);
      else if (m_child_sw->is_in(mass_centre_ptr->location)) return m_child_sw->remove(data);
      else if (m_child_se->is_in(mass_centre_ptr->location)) return m_child_se->remove(data);
      return eremoved::no;
   }
   
   typename std::vector<cbinded_mass_centre2d<T>*>::iterator find_body(const T& data)
   {
      typename std::vector<cbinded_mass_centre2d<T>*>::iterator mass_centre_it = 
         std::find_if (m_bodies.begin(), m_bodies.end(), 
            [&](cbinded_mass_centre2d<T>* mass_centre) { 
               return mass_centre->data == data; 
         });
      return mass_centre_it;
   }
   
   eexists move (const T& data, cvector2d new_location)
   {
      auto mass_centre_it = find_body(data);
      if (mass_centre_it == m_bodies.end()) return eexists::no;
      auto mass_centre_ptr = *mass_centre_it;
      if(mass_centre_ptr == nullptr) return eexists::no;
      if(mass_centre_ptr->location == new_location) return eexists::yes;
      // so, with corner cases handled, here's the thing:
      
      cvector2d old_location = mass_centre_ptr->location;

      bool crosses_node_border = false;
      if(!is_leaf()) {
         if     (m_child_nw->is_in(mass_centre_ptr->location) && m_child_nw->is_in(new_location)) m_child_nw->move(data, new_location);
         else if(m_child_ne->is_in(mass_centre_ptr->location) && m_child_ne->is_in(new_location)) m_child_ne->move(data, new_location);
         else if(m_child_sw->is_in(mass_centre_ptr->location) && m_child_sw->is_in(new_location)) m_child_sw->move(data, new_location);
         else if(m_child_se->is_in(mass_centre_ptr->location) && m_child_se->is_in(new_location)) m_child_se->move(data, new_location);
         else {
            crosses_node_border = true;
         }
      }
      
      if (crosses_node_border) {
         // in this case remove the body and insert it again in new position
         if (remove(data) == eremoved::yes) {
            mass_centre_ptr->location = new_location;
            add(mass_centre_ptr);         
         }
      }
      else {
         // in this case just update mass centres
         m_mass_centre.remove_from_mass_centre({old_location, mass_centre_ptr->mass});
         mass_centre_ptr->location = new_location;
         m_mass_centre.add_to_mass_centre(*mass_centre_ptr); 
      }
      
      return eexists::yes;
   }
   
   echanged change_mass (const T& data, double new_mass)
   {
      auto mass_centre_it = find_body(data);
      if (mass_centre_it == m_bodies.end()) return echanged::no;
      auto mass_centre_ptr = *mass_centre_it;
      if(mass_centre_ptr == nullptr) return echanged::no;
      if(mass_centre_ptr->mass == new_mass) return echanged::yes;
      // so, with corner cases handled, here's the thing:
      remove(data);
      mass_centre_ptr->mass = new_mass;
      add(mass_centre_ptr);
      return echanged::yes;
   }
   
   const cmass_centre2d& get_mass_centre () const
   {
      return m_mass_centre;
   }
   
   bool is_in(cvector2d location)
   {
      return m_rectangle.is_in (location);
   }
        
   bool is_leaf () const 
   {
      return m_child_nw == nullptr;
   }
        
   bool is_root () const 
   {
      return m_parent == nullptr;
   }
        
   cquadnode<T>* get_nw_leaf ()
   {
      cquadnode<T>* leaf = this;
      while (!leaf->is_leaf()) {
         // Danger, that is why it must be const.
         // Collecting smart ptr instead is wasteful with resources and not really needed here.
         leaf = leaf->m_child_nw.get();
      }
      return leaf;
   }
        
   bool has_children () const
   {
      // if it has one, it has all four
      return m_child_ne != nullptr;
   }
        
   bool is_nw_child () const 
   {
      if (m_parent != nullptr &&
          m_parent->m_child_nw != nullptr &&
          this == m_parent->m_child_nw.get() ) 
      {
         return true;
      }
      return false;
   }

   bool is_ne_child () const 
   {
      if (m_parent != nullptr &&
          m_parent->m_child_ne != nullptr &&
          this == m_parent->m_child_ne.get() ) 
      {
         return true;
      }
      return false;
   }

   bool is_sw_child () const 
   {
      if (m_parent != nullptr &&
         m_parent->m_child_sw != nullptr &&
         this == m_parent->m_child_sw.get() ) 
      {
         return true;
      }
      return false;
   }

   bool is_se_child () const 
   {
      if (m_parent != nullptr &&
          m_parent->m_child_se != nullptr &&
          this == m_parent->m_child_se.get() ) 
      {
         return true;
      }
      return false;
   }
        
   cquadnode<T>* get_next_sibling () const 
   {
      if (is_nw_child()) {
         return m_parent->m_child_ne.get();
      }
      else if (is_ne_child()) {
         return m_parent->m_child_sw.get();
      }
      else if (is_sw_child()) {
         return m_parent->m_child_se.get();
      }
      else {   // no more child nodes
         return nullptr;
      }
   }
        
   cquadnode<T>* get_first_leaf () const 
   {
      cquadnode<T>* candidate = this;
      while (!candidate->is_leaf()) {
         candidate = candidate->m_child_nw.get();
      }
      return candidate;
   }
   
   const cbinded_mass_centre2d<T>* find (const T& data) const
   {
      for (auto body : m_bodies) {
         if (body->data == data) {
            return body;
         }
      }
      return nullptr; // not found
   }
   
   const crectangle<cvector2d>& get_node_rectangle () const
   {
      return m_rectangle;
   }
        
private:

   void attach_child_node (edirection which_node, std::shared_ptr<cquadnode<T>> node)
   {
      switch(which_node) {
         case edirection::nw: m_child_nw = node; break;
         case edirection::ne: m_child_ne = node; break;
         case edirection::sw: m_child_sw = node; break;
         case edirection::se: m_child_se = node; break;
      };
      node->m_parent = this->shared_from_this(); 
   }
   
   std::shared_ptr<cquadnode<T>> m_child_nw = nullptr;
   std::shared_ptr<cquadnode<T>> m_child_ne = nullptr;
   std::shared_ptr<cquadnode<T>> m_child_sw = nullptr;
   std::shared_ptr<cquadnode<T>> m_child_se = nullptr;
   std::shared_ptr<cquadnode<T>> m_parent = nullptr;
        
   // All bodies that are in this node, and in all it's subnodes, are stored in
   // this vector of shared pointers. This is to enable quick traversal of all
   // bodies stored here, and with that an effective search solution too. If it
   // wasn't for the fact that what is stored in here are pointers, which will be
   // causing cache misses all the time, it should look like using std::vector.
   std::vector<cbinded_mass_centre2d<T>*> m_bodies;
   cmass_centre2d m_mass_centre;
        
   crectangle2d m_rectangle;
   double m_diagonal_length = -1;
};

} // namespace
    
#endif /* MZLIB_QUADTREE_NODE_H */

