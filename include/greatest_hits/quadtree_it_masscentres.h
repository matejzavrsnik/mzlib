//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_QUADTREE_IT_MASSCENTRES_H
#define MZLIB_QUADTREE_IT_MASSCENTRES_H

#include "../nature/body.h"
#include "../nature/mass_centre.h"
#include "quadtree_node.h"

#include <iterator>
#include <vector>

namespace mzlib {

// Const iterator through all mass centres
class quadtree_it_masscentres
{
public:

   using iterator_category = std::forward_iterator_tag;
   using value_type = body_core2d;
   // using difference_type = meaningless in this case
   using pointer = body_core2d*;
   using reference = body_core2d&;

private:

   std::vector<mass_centre2d> m_mass_centres_queue;

   const body_core2d* m_body = nullptr;
   
   std::vector<const quadnode*> m_nodes_queue;
   double m_quotient = 0.25;
   mass_centre2d m_next_mass_centre;
   bool m_done = false;
   
   void set_done ()
   {
      // Instead of complicated set of interconnected clues about whether we are done or not,
      // why not instead have a simple flag and that's it. So here it is:
      m_done = true;
   }
   
   void prepare_next_mass_centre ()
   {
      //todo: this complicated function can probably be simplified and broken down.
      // This function is a bit logic-heavy ... ready? Here we go:
      if (m_mass_centres_queue.size() > 0) {
         // are mass centres in queue to return? Return those first
         m_next_mass_centre = m_mass_centres_queue.back();
         m_mass_centres_queue.pop_back(); // don't return same twice
         return; // nothing more to do for now
      }
      // By this point, queue of readily available mass centres is depleted. See the queued nodes.
      if (m_nodes_queue.size() == 0) {
         // No more nodes? This is the end. My only friend, the end.
         set_done();
         return; 
      }
      // By this point, queue of mass centres is depleted, but there are still nodes in need to be processed
      const quadnode* node = m_nodes_queue.back();
      m_nodes_queue.pop_back(); // don't use this node again
      // Calculate quotient that tells how far it is compared to its size
      double node_distance = law::vector::distance(m_body->centre.location, node->get_mass_centre().location);
      double node_quotient = node->m_diagonal_length.value() / node_distance;
      // Now depending how far it is, we need to consider either just mass centre of the node, or individual bodies
      if (node_quotient < m_quotient) {
         // too far; we care nothing about this node beyond it's mass centre
         if (node->get_mass_centre().mass != 0) {
            // If it has any real mass at all, that is.
            m_next_mass_centre = node->get_mass_centre();
            return; // done; next mass centre prepared
         }
      }
      else {
         // not too far; need to consider it in details
         if (node->has_children()) {
            // Queue up the children nodes. Rinse. Repeat.
            if(node->m_child_nw->m_bodies.size()) m_nodes_queue.push_back(node->m_child_nw.get());
            if(node->m_child_ne->m_bodies.size()) m_nodes_queue.push_back(node->m_child_ne.get());
            if(node->m_child_sw->m_bodies.size()) m_nodes_queue.push_back(node->m_child_sw.get());
            if(node->m_child_se->m_bodies.size()) m_nodes_queue.push_back(node->m_child_se.get());
         }
         else if (node->m_bodies.size() > 0) {
            // So, by here, the node is not too far, is leaf, has bodies; line them up!
            for(auto body : node->m_bodies) {
               if (body->tag == m_body->tag) continue; // Skip original body
               m_mass_centres_queue.push_back(body->centre);
            }
         }
      }
      // Continue until you have the next m_next_mass_centre to show for it, or
      // there is no more nodes and iteration finished.
      prepare_next_mass_centre();
   }
   
public:

   explicit quadtree_it_masscentres (const quadnode* const node, const unique tag, double quotient)
   { 
      const body_core2d* found_body = node->find (tag);
      if (found_body == nullptr) 
      {
         set_done();
         return;
      }
      m_body = found_body;
      m_quotient = quotient;
      m_mass_centres_queue.reserve(100);
      m_nodes_queue.reserve(100);
      m_nodes_queue.push_back(node);
      prepare_next_mass_centre();
   }
   
   quadtree_it_masscentres ()
   { 
      set_done();
   }

   quadtree_it_masscentres (quadtree_it_masscentres&&) = default;
   quadtree_it_masscentres (const quadtree_it_masscentres&) = default;

   quadtree_it_masscentres* operator++ () 
   {
      prepare_next_mass_centre ();
      return this; 
   }
        
   quadtree_it_masscentres* operator++ (int) 
   { 
      //todo: I know, I lie about postfix. Will fix some day, I promise.
      prepare_next_mass_centre ();
      return this; 
   }

   mass_centre2d* operator-> ()
   {
      return &m_next_mass_centre;
   }

   mass_centre2d& operator* ()
   {
      return m_next_mass_centre; 
   }
   
   bool operator== (const quadtree_it_masscentres& other) const 
   {
      // Infinite recursion guard
      if (this == &other) return true;
      // Return equal only if they are both at the end. Other equalities are possible
      // but I don't see how they could be used for any meaningful purpose and the 
      // calculation would be expensive too.
      return (m_done == true && other.m_done == true);  
   }

   bool operator!= (const quadtree_it_masscentres& other) const 
   { 
      return !(*this == other); 
   }
};

} // namespace

#endif /* MZLIB_QUADTREE_IT_MASSCENTRES_H */
