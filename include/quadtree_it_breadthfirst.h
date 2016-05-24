// 
// Author: Matej Zavrsnik (matejzavrsnik.com)
//

#ifndef QUADTREE_IT_BREADTHFIRST_H
#define	QUADTREE_IT_BREADTHFIRST_H

#include <iterator>
#include <memory> // shared_ptr
#include <queue>
#include "quadtree.h"

namespace mzlib {

// Post-order iterator through all nodes
template<class T>
class quadtree_it_breadthfirst : public std::iterator<std::forward_iterator_tag, T>
{

private:
   
   std::queue<cquadnode<T>*> m_queue;

   void next_node()
   {
      if (!m_queue.empty()) {
         auto node = m_queue.front();
         m_queue.pop(); // don't use again
         if (node->has_children()) {
            m_queue.push(node->m_child_nw.get());
            m_queue.push(node->m_child_ne.get());
            m_queue.push(node->m_child_sw.get());
            m_queue.push(node->m_child_se.get());
         }
      }
   }
        
public:

   explicit quadtree_it_breadthfirst(cquadnode<T>* node)
   { 
      if (node!=nullptr) {
         m_queue.push(node);
      }
   }

   quadtree_it_breadthfirst (quadtree_it_breadthfirst&&) = default;
   quadtree_it_breadthfirst (const quadtree_it_breadthfirst&) = default;

   quadtree_it_breadthfirst* operator++ () 
   { 
      next_node();
      return this;
   }
        
   quadtree_it_breadthfirst* operator++ (int) 
   { 
      next_node();
      return this;
   }

   cquadnode<T>* operator-> () const
   { 
      return m_queue.front();
   }

   cquadnode<T>& operator* () const
   { 
      return *m_queue.front(); 
   }

   bool operator== (const quadtree_it_breadthfirst& other) const 
   { 
      // Infinite recursion guard
      if (this == &other) return true;
      // After this, compare all fields
      return (this->m_queue.size() == other.m_queue.size());  
   }

   bool operator!= (const quadtree_it_breadthfirst& other) const 
   { 
      return !(*this == other); 
   }
};

} // namespace mzlib

#endif // QUADTREE_IT_BREADTHFIRST_H

