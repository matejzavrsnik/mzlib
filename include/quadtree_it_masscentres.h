//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef QUADTREE_IT_MASSCENTRES_H
#define QUADTREE_IT_MASSCENTRES_H

#include <iterator>
#include <queue>
#include "quadtree.h"
#include "mass_centre.h"

namespace mzlib {

// Const iterator through all mass centres
template<class T>
class quadtree_it_masscentres : 
   public std::iterator<std::forward_iterator_tag, cbinded_mass_centre<T>>
{

private:

   std::queue<cmass_centre> m_mass_centres_queue;

   const cbinded_mass_centre<T>* m_body;
   
   std::queue<const cquadnode<T>*> m_nodes_queue;
   double m_quotient;
   cmass_centre m_next_mass_centre;
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
         m_next_mass_centre = m_mass_centres_queue.front();
         m_mass_centres_queue.pop(); // don't return same twice
         return; // nothing more to do for now
      }
      // By this point, queue of readily available mass centres is depleted. See the queued nodes.
      if (m_nodes_queue.size() == 0) {
         // No more nodes? This is the end. My only friend, the end.
         set_done();
         return; 
      }
      // By this point, queue of mass centres is depleted, but there are still nodes in need to be processed
      const cquadnode<T>* node = m_nodes_queue.front();
      m_nodes_queue.pop(); // don't use this node again
      // Calculate quotient that tells how far it is compared to its size
      double node_diagonal = node->get_bottom_right().distance_to(node->get_top_left());
      double node_distance = m_body->get_location().distance_to(node->get_mass_centre().get_location());
      double node_quotient = node_diagonal / node_distance;
      // Now depending how far it is, we need to consider either just mass centre of the node, or individual bodies
      if (node_quotient < m_quotient) {
         // too far; we care nothing about this node beyond it's mass centre
         if (node->get_mass_centre().get_mass() != 0) {
            // If it has any real mass at all, that is.
            m_next_mass_centre = node->get_mass_centre();
            return; // done; next mass centre prepared
         }
         // Recurse: will work on other queued nodes.
         prepare_next_mass_centre();
      }
      else {
         // not too far; need to consider it in details
         if (node->has_children()) {
            // Queue up the children nodes. Rinse. Repeat.
            m_nodes_queue.push(node->m_child_nw.get());
            m_nodes_queue.push(node->m_child_ne.get());
            m_nodes_queue.push(node->m_child_sw.get());
            m_nodes_queue.push(node->m_child_se.get());
            // Recurse: will work on queued nodes. Probably. You can never really tell with recursion, can you?
            prepare_next_mass_centre();
         }
         else if (node->m_bodies.size() > 0) {
            // So, by here, the node is not too far, is leaf, has bodies; line them up!
            for(auto body : node->m_bodies) {
               if (body->get_binded_data() == m_body->get_binded_data()) continue; // Skip original body
               m_mass_centres_queue.push(*body);
            }
            // Recurse: will pop first mass centre from queue
            prepare_next_mass_centre(); 
         }
      }
   }
   
public:

   explicit quadtree_it_masscentres (const cquadnode<T>* const node, const T& data, double quotient)
   { 
      m_body = node->find(data);
      if (m_body == nullptr) 
      {
         set_done();
         return;
      }
      m_quotient = quotient;
      m_nodes_queue.push(node);
      prepare_next_mass_centre();
   }
   
   quadtree_it_masscentres ()
   { 
      set_done();
   }

   quadtree_it_masscentres (quadtree_it_masscentres&&) = default;
   quadtree_it_masscentres (const quadtree_it_masscentres&) = default;

   quadtree_it_masscentres<T>* operator++ () 
   {
      prepare_next_mass_centre ();
      return this; 
   }
        
   quadtree_it_masscentres<T>* operator++ (int) 
   { 
      //todo: I know, I lie about postfix. Will fix some day, I promise.
      prepare_next_mass_centre ();
      return this; 
   }

   cmass_centre* operator-> ()
   {
      return &m_next_mass_centre;
   }

   cmass_centre& operator* ()
   {
      return m_next_mass_centre; 
   }
   
   bool operator== (const quadtree_it_masscentres<T>& other) const 
   {
      // Infinite recursion guard
      if (this == &other) return true;
      // Return equal only if they are both at the end. Other equalities are possible
      // but I don't see how they could be used for any meaningful purpose and the 
      // calculation would be expensive too.
      return (m_done == true && other.m_done == true);  
   }

   bool operator!= (const quadtree_it_masscentres<T>& other) const 
   { 
      return !(*this == other); 
   }
};

} // namespace mzlib

#endif // QUADTREE_IT_MASSCENTRES_H

