// 
// Author: Matej Zavrsnik (matejzavrsnik.com)
//

#ifndef QUADREEE_H
#define QUADREEE_H

#include "quadtree_node.h"
#include "quadtree_it_bodies.h"
#include "quadtree_it_postorder.h"
#include "quadtree_it_breadthfirst.h"
#include "vector.h"
#include "body.h"

namespace mzlib {

template<class T>
class cquadtree
{
    
private:
    
   std::shared_ptr<cquadnode<T>> m_root;
    
public:
       
   // Following is just for easier coding and most developers will expect
   // something like cquadtree::iterator to exist
   typedef quadtree_it_bodies<T>       iterator;
   typedef quadtree_it_postorder<T>    it_postorder;
   typedef quadtree_it_breadthfirst<T> it_breadthfirst;
      
   cquadtree (
      const mzlib::math::cvector2d& top_left, 
      const mzlib::math::cvector2d& bottom_right, 
      const double smallest_node_width )
   {
      m_root = std::make_shared<cquadnode<T>>();
      m_root->create(top_left, bottom_right, smallest_node_width, nullptr);
   }
        
   cquadtree (const cquadtree&) = delete;
   cquadtree (cquadtree && ) = delete;
   cquadtree& operator= (const cquadtree&) = delete;
   cquadtree& operator= (cquadtree&&) = delete;
   virtual ~cquadtree () = default;
        
   bool add (T body, math::cvector2d location) 
   { 
      return m_root->add(body, location); 
   }

   bool is_in (math::cvector2d location) const 
   { 
      return m_root->is_in(location); 
   }

   iterator begin () 
   { 
      return iterator(m_root.get()); 
   }
   
   iterator end () 
   { 
      return iterator(nullptr); 
   }
        
   it_postorder begin_nodes_postorder ()
   { 
      return it_postorder(m_root.get()); 
   }

   it_postorder end_nodes_postorder ()
   {
      return it_postorder(nullptr); 
   }
        
   it_breadthfirst begin_nodes_breadthfirst ()
   { 
      return it_breadthfirst(m_root.get()); 
   }
   
   it_breadthfirst end_nodes_breadthfirst ()
   { 
      return it_breadthfirst(nullptr); 
   }
}; 
    
} // namespace mzlib

#endif	/* QUADREEE_H */

