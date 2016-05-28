// 
// Author: Matej Zavrsnik (matejzavrsnik.com)
//

#ifndef QUADTREE_NODE_H
#define	QUADTREE_NODE_H

#include "vector.h"
#include "mass_centre.h"

namespace mzlib {

// Assumptions to be aware of: 
//    - The coordinate system is such that values increase down (south) and right (east).
//    - Leftmost (E) and topmost (N) coordinates are exclusive.
//    - Rightmost (W) and downmost (S) coordinates are inclusive.
//    - Assumed order of iteration where it matters is nw -> ne -> sw -> se
    
template <class T> class quadtree_it_bodies;
template <class T> class quadtree_it_postorder;
template <class T> class quadtree_it_breadthfirst;
    
template<class T>
class cquadnode : public std::enable_shared_from_this<cquadnode<T>>
{
        
   friend class quadtree_it_bodies<T>;
   friend class quadtree_it_postorder<T>;
   friend class quadtree_it_breadthfirst<T>;
        
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
      }
   }

   bool add (cbinded_mass_centre<T> body) 
   {
      if (is_leaf() && is_in(body.get_location())) { 
         // at this point is leaf and body is within node bounds
         m_bodies.push_back(body);
         return true;
      }
      else if (m_child_nw->is_in(body.get_location())) return m_child_nw->add(body);
      else if (m_child_ne->is_in(body.get_location())) return m_child_ne->add(body);
      else if (m_child_sw->is_in(body.get_location())) return m_child_sw->add(body);
      else if (m_child_se->is_in(body.get_location())) return m_child_se->add(body);
      return false;
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
        
private:

   std::shared_ptr<cquadnode<T>> m_child_nw;
   std::shared_ptr<cquadnode<T>> m_child_ne;
   std::shared_ptr<cquadnode<T>> m_child_sw;
   std::shared_ptr<cquadnode<T>> m_child_se;
   std::shared_ptr<cquadnode<T>> m_parent;
        
   std::vector<cbinded_mass_centre<T>> m_bodies;
   cbinded_mass_centre<T> m_mass_centre;
        
   math::cvector2d m_top_left;
   math::cvector2d m_bottom_right;
};

} // namespace mzlib
    
#endif // QUADTREE_NODE_H

