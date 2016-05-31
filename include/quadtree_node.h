//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef QUADTREE_NODE_H
#define	QUADTREE_NODE_H

#include <memory>
#include "vector.h"
#include "mass_centre.h"

namespace mzlib {

// Assumptions to be aware of: 
//    - The coordinate system is such that values increase down (south) and right (east).
//    - Leftmost (E) and topmost (N) coordinates are exclusive.
//    - Rightmost (W) and downmost (S) coordinates are inclusive.
//    - Assumed order of iteration where it matters is nw -> ne -> sw -> se
    
template <class T> class quadtree_it_bodies;
template <class T> class quadtree_it_masscentres;
template <class T> class quadtree_it_nodes_postorder;
template <class T> class quadtree_it_nodes_breadthfirst;
    
template<class T>
class cquadnode : public std::enable_shared_from_this<cquadnode<T>>
{
        
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
      const mzlib::math::cvector2d& top_left, 
      const mzlib::math::cvector2d& bottom_right, 
      const double smallest_node_width, 
      std::shared_ptr<cquadnode> parent = nullptr) 
   {
      m_parent = parent;
      m_top_left = top_left;
      m_bottom_right = bottom_right;
      double node_width = m_bottom_right[0] - top_left[0];
      if (node_width > smallest_node_width) {
         // For breaking a square node into four adjacent              1-2-3 
         // square subnodes by defining them with top-left and    ->   4-5-6
         // bottom-right vectors, we need 9 separate vectors           7-8-9
         double subnode_width = node_width / 2; // each of four subnodes is half as wide
         mzlib::math::cvector2d v1 = top_left;
         mzlib::math::cvector2d v2 = v1.move_by({subnode_width, 0.0}); // 1 -> 2 -> 3
         mzlib::math::cvector2d v3 = v2.move_by({subnode_width, 0.0}); // v nw v ne v
         mzlib::math::cvector2d v4 = v1.move_by({0.0, subnode_width}); // 4    5    6
         mzlib::math::cvector2d v5 = v2.move_by({0.0, subnode_width}); // v sw v se v
         mzlib::math::cvector2d v6 = v3.move_by({0.0, subnode_width}); // 7    8    9
         //mzlib::math::cvector2d v7 = v4.move_by({0.0, subnode_width}); 
         mzlib::math::cvector2d v8 = v5.move_by({0.0, subnode_width}); 
         mzlib::math::cvector2d v9 = v6.move_by({0.0, subnode_width}); 
         m_child_nw = std::make_shared<cquadnode<T>>();
         m_child_nw->create(v1, v5, smallest_node_width, this->shared_from_this());
         m_child_ne = std::make_shared<cquadnode<T>>();
         m_child_ne->create(v2, v6, smallest_node_width, this->shared_from_this());
         m_child_sw = std::make_shared<cquadnode<T>>();
         m_child_sw->create(v4, v8, smallest_node_width, this->shared_from_this());
         m_child_se = std::make_shared<cquadnode<T>>();
         m_child_se->create(v5, v9, smallest_node_width, this->shared_from_this());
         // Set mass centre in the centre of the node, even if 0. Philosophical, huh?
         m_mass_centre.location = v5; 
      }
   }

   void add (std::shared_ptr<cbinded_mass_centre<T>> mass_centre) 
   {
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
   
   bool remove (const T& data) 
   {
      // downside of this approach: every subnode needs to find mass centre in it's own collection
      // try to find the body in collection of bodies in this node
      auto mass_centre_it = std::find_if (m_bodies.begin(), m_bodies.end(), 
         [&](std::shared_ptr<cbinded_mass_centre<T>> mass_centre) { 
            return mass_centre->data == data; 
      });
      // if no such mass centre here, go away
      if (mass_centre_it == m_bodies.end()) return false; 
      // if found, convert to mass centre ptr
      std::shared_ptr<cbinded_mass_centre<T>> mass_centre_ptr = *mass_centre_it;
      // start removing
      // no need to check if it is in the node, because of course it is; checked earlier
      m_bodies.erase(mass_centre_it);
      m_mass_centre.remove_from_mass_centre(*mass_centre_ptr);
      // if leaf, this operation is done
      if (is_leaf()) return true;
      // if not leaf, delete in children too
      if      (m_child_nw->is_in(mass_centre_ptr->location)) return m_child_nw->remove(data);
      else if (m_child_ne->is_in(mass_centre_ptr->location)) return m_child_ne->remove(data);
      else if (m_child_sw->is_in(mass_centre_ptr->location)) return m_child_sw->remove(data);
      else if (m_child_se->is_in(mass_centre_ptr->location)) return m_child_se->remove(data);
      return false;
   }
   
   const cmass_centre& get_mass_centre() const
   {
      return m_mass_centre;
   }
   
   bool is_in(math::cvector2d location)
   {
      if (location[0] >  m_top_left[0] && 
          location[1] >  m_top_left[1] &&   // left and top are exclusive
          location[0] <= m_bottom_right[0] && 
          location[1] <= m_bottom_right[1]) // right and bottom are inclusive 
      { 
         return true;
      }
      return false;
   }
        
   mzlib::math::cvector2d get_top_left () const
   {
      return m_top_left;
   }
        
   mzlib::math::cvector2d get_bottom_right () const
   {
      return m_bottom_right;
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
   
   const cbinded_mass_centre<T>* find (const T& data) const
   {
      for (auto& body : m_bodies) {
         if (body->data == data) {
            return body.get();
         }
      }
      return nullptr; // not found
   }
        
private:

   std::shared_ptr<cquadnode<T>> m_child_nw;
   std::shared_ptr<cquadnode<T>> m_child_ne;
   std::shared_ptr<cquadnode<T>> m_child_sw;
   std::shared_ptr<cquadnode<T>> m_child_se;
   std::shared_ptr<cquadnode<T>> m_parent;
        
   std::vector<std::shared_ptr<cbinded_mass_centre<T>>> m_bodies;
   cmass_centre m_mass_centre;
        
   math::cvector2d m_top_left;
   math::cvector2d m_bottom_right;
};

} // namespace mzlib
    
#endif // QUADTREE_NODE_H

