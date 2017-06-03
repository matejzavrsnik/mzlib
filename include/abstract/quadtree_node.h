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
#include "../nature/vector.h"
#include "../nature/mass_centre.h"
#include "../tools/missing_std.h"
#include "../nature/body.h"
#include "../screen_rectangle.h"
#include "../laws/screen_rectangles.h"
#include "../lang/binary_options.h"
#include "../lang/exceptions.h"

namespace mzlib {

// Assumptions to be aware of: 
//    - The coordinate system is such that values increase down (south) and right (east).
//    - Leftmost (E) and topmost (N) coordinates are exclusive.
//    - Rightmost (W) and downmost (S) coordinates are inclusive.
//    - Assumed order of iteration where it matters is nw -> ne -> sw -> se

class quadtree;
class quadtree_it_bodies;
class quadtree_it_masscentres;
    
class quadnode : public std::enable_shared_from_this<quadnode>
{
   
   friend class quadtree;
   friend class quadtree_it_bodies;
   friend class quadtree_it_masscentres;
        
public:

   quadnode() {}
   quadnode(const quadnode&) = delete;
   quadnode(quadnode && ) = delete;
   quadnode& operator=(const quadnode&) = delete;
   quadnode& operator=(quadnode&&) = delete;
   virtual ~quadnode() = default;

   // Creation needs to be done outside the constructor, because to be able to call shared_from_this(),
   // an object needs an owning shared_ptr, otherwise there is risk of two shared_ptrs owning same object.
   void create (
      const screen_rectangle2d& rectangle, 
      const double smallest_node_width, 
      const direction which_quadrant = direction::centre, // root by default: no direction
      std::shared_ptr<quadnode> parent = nullptr)          // root by default: no parent
   {
      m_parent = parent;
      m_rectangle = rectangle;
      m_which_quadrant = which_quadrant;
      
      law::screen_rectangles2d rect_law;
      rect_law.consider(m_rectangle);
      if (!m_diagonal_length.is_set()) {
         m_diagonal_length = rect_law.solve_for_diagonal_length();
      }
      if (rect_law.solve_for_width() > smallest_node_width) {
         const vector2d centre_point = rect_law.solve_for_centre_point();
         
         // Set mass centre in the centre of the node, even if 0. Philosophical, huh?
         m_mass_centre.location = centre_point;
         
         const screen_rectangle2d nw_rect(m_rectangle.get_top_left(), centre_point);
         law::screen_rectangles2d nw_rect_law;
         nw_rect_law.consider(nw_rect);
         
         if (m_child_nw == nullptr) {
            m_child_nw = std::make_shared<quadnode>();
            m_child_nw->create(nw_rect, smallest_node_width, direction::nw, this->shared_from_this());
         }
         if (m_child_ne == nullptr) {
            m_child_ne = std::make_shared<quadnode>();

            const screen_rectangle2d ne_rect = nw_rect_law.flip(direction::e);
            m_child_ne->create(ne_rect, smallest_node_width, direction::ne, this->shared_from_this());
         }
         if (m_child_sw == nullptr) {
            m_child_sw = std::make_shared<quadnode>();
            const screen_rectangle2d sw_rect = nw_rect_law.flip(direction::s);
            m_child_sw->create(sw_rect, smallest_node_width, direction::sw, this->shared_from_this());
         }
         if (m_child_se == nullptr) {
            m_child_se = std::make_shared<quadnode>();
            const screen_rectangle2d se_rect = nw_rect_law.flip(direction::se);
            m_child_se->create(se_rect, smallest_node_width, direction::se, this->shared_from_this());
         }
      }
   }

   void add (body_core2d* body) 
   {
      // It is important that the is_in check is here, because it is not in
      // the quadtree class when it calls this function. Something needs to
      // check it, and it is redundant to check twice, so here it is.
      if (is_in(body->centre.location)) {
         // insert
         m_bodies.push_back(body);
         add_to_mass_centre(m_mass_centre, body->centre);
         if (is_leaf()) return; // nothing more to do
         // if has children, insert there as well
         if      (m_child_nw->is_in(body->centre.location)) m_child_nw->add(body);
         else if (m_child_ne->is_in(body->centre.location)) m_child_ne->add(body);
         else if (m_child_sw->is_in(body->centre.location)) m_child_sw->add(body);
         else if (m_child_se->is_in(body->centre.location)) m_child_se->add(body);
      }
   }
   
   option::removed remove (const unique tag) 
   {
      // downside of the approach where every node contains all bodies under it: 
      // every subnode needs to find mass centre in it's own collection
      auto mass_centre_it = find_body(tag);
      // if no such mass centre here, go away
      if (mass_centre_it == m_bodies.end()) return option::removed::no; 
      // if found, convert to mass centre ptr
      body_core2d* mass_centre_ptr = *mass_centre_it;
      // start removing
      // no need to check if it is in the node, because of course it is; checked earlier
      m_bodies.erase(mass_centre_it);
      remove_from_mass_centre(m_mass_centre, mass_centre_ptr->centre);
      // if leaf, this operation is done
      if (is_leaf()) return option::removed::yes;
      // if not leaf, delete in children too
      if      (m_child_nw->is_in(mass_centre_ptr->centre.location)) return m_child_nw->remove(tag);
      else if (m_child_ne->is_in(mass_centre_ptr->centre.location)) return m_child_ne->remove(tag);
      else if (m_child_sw->is_in(mass_centre_ptr->centre.location)) return m_child_sw->remove(tag);
      else if (m_child_se->is_in(mass_centre_ptr->centre.location)) return m_child_se->remove(tag);
      return option::removed::no;
   }
   
   typename std::vector<body_core2d*>::iterator find_body(const unique tag)
   {
      typename std::vector<body_core2d*>::iterator mass_centre_it = 
         std::find_if (m_bodies.begin(), m_bodies.end(), 
            [&](body_core2d* mass_centre) { 
               return mass_centre->tag == tag; 
         });
      return mass_centre_it;
   }
   
   option::exists move (const unique tag, vector2d new_location)
   {
      auto body_it = find_body(tag);
      if (body_it == m_bodies.end()) return option::exists::no;
      auto body_ptr = *body_it;
      if(body_ptr == nullptr) return option::exists::no;
      if(body_ptr->centre.location == new_location) return option::exists::yes;
      // so, with corner cases handled, here's the thing:
      
      vector2d old_location = body_ptr->centre.location;

      bool crosses_node_border = false;
      if(!is_leaf()) {
         if     (m_child_nw->is_in(body_ptr->centre.location) && m_child_nw->is_in(new_location)) m_child_nw->move(tag, new_location);
         else if(m_child_ne->is_in(body_ptr->centre.location) && m_child_ne->is_in(new_location)) m_child_ne->move(tag, new_location);
         else if(m_child_sw->is_in(body_ptr->centre.location) && m_child_sw->is_in(new_location)) m_child_sw->move(tag, new_location);
         else if(m_child_se->is_in(body_ptr->centre.location) && m_child_se->is_in(new_location)) m_child_se->move(tag, new_location);
         else {
            crosses_node_border = true;
         }
      }
      
      if (crosses_node_border) {
         // in this case remove the body and insert it again in new position
         if (remove(tag) == option::removed::yes) {
            body_ptr->centre.location = new_location;
            add(body_ptr);         
         }
      }
      else {
         // in this case just update mass centres
         remove_from_mass_centre(m_mass_centre, {old_location, body_ptr->centre.mass});
         body_ptr->centre.location = new_location;
         add_to_mass_centre(m_mass_centre, body_ptr->centre); 
      }
      
      return option::exists::yes;
   }
   
   option::changed change_mass (const unique tag, double new_mass)
   {
      auto body_it = find_body (tag);
      if (body_it == m_bodies.end()) return option::changed::no;
      auto body_ptr = *body_it;
      if(body_ptr == nullptr) return option::changed::no;
      if(body_ptr->centre.mass == new_mass) return option::changed::yes;
      // so, with corner cases handled, here's the thing:
      remove (tag);
      body_ptr->centre.mass = new_mass;
      add(body_ptr);
      return option::changed::yes;
   }
   
   const mass_centre2d& get_mass_centre () const
   {
      return m_mass_centre;
   }
   
   bool is_in(vector2d location)
   {
      if (!m_rectangle.is_defined()) {
         return false;
      }
      law::screen_rectangles2d law;
      law.consider(m_rectangle);
      return law.is_in(location);
   }
        
   bool is_leaf () const 
   {
      return m_child_nw == nullptr;
   }
        
   bool is_root () const 
   {
      return m_parent == nullptr;
   }
        
   quadnode* get_nw_leaf ()
   {
      quadnode* leaf = this;
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
      return m_which_quadrant == direction::nw;
   }

   bool is_ne_child () const 
   {
      return m_which_quadrant == direction::ne;
   }

   bool is_sw_child () const 
   {
      return m_which_quadrant == direction::sw;
   }

   bool is_se_child () const 
   {
      return m_which_quadrant == direction::se;
   }
        
   quadnode* get_next_sibling () const 
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
        
   quadnode* get_first_leaf ()
   {
      quadnode* candidate = this;
      while (!candidate->is_leaf()) {
         candidate = candidate->m_child_nw.get();
      }
      return candidate;
   }
   
   const body_core2d* find (const unique tag) const
   {
      for (auto body : m_bodies) {
         if (body->tag == tag) {
            return body;
         }
      }
      return nullptr; // not found
   }
   
   const screen_rectangle<vector2d>& get_node_rectangle () const
   {
      return m_rectangle;
   }
        
private:

   void attach_child_node (direction which_node, std::shared_ptr<quadnode> node)
   {
      switch(which_node) {
         case direction::nw: m_child_nw = node; break;
         case direction::ne: m_child_ne = node; break;
         case direction::sw: m_child_sw = node; break;
         case direction::se: m_child_se = node; break;
         default: throw exception::meaningless(); break;
      };
      node->m_parent = this->shared_from_this(); 
   }
   
   std::shared_ptr<quadnode> m_child_nw = nullptr;
   std::shared_ptr<quadnode> m_child_ne = nullptr;
   std::shared_ptr<quadnode> m_child_sw = nullptr;
   std::shared_ptr<quadnode> m_child_se = nullptr;
   std::shared_ptr<quadnode> m_parent = nullptr;
        
   // All bodies that are in this node, and in all it's subnodes, are stored in
   // this vector of pointers. This is to enable quick traversal of all
   // bodies stored here, and with that an effective search solution too.
   // Without it I would need to traverse all children nodes instead.
   std::vector<body_core2d*> m_bodies;
   mass_centre2d m_mass_centre;
        
   screen_rectangle2d m_rectangle;
   optional<double> m_diagonal_length;
   direction m_which_quadrant;
};

} // namespace
    
#endif /* MZLIB_QUADTREE_NODE_H */

