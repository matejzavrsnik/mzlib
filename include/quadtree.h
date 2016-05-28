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
       
   // because developers would expect cquadtree::iterators to exist
   typedef quadtree_it_bodies<T>             it_bodies;
   typedef quadtree_it_nodes_postorder<T>    it_nodes_postorder;
   typedef quadtree_it_nodes_breadthfirst<T> it_nodes_breadthfirst;
      
   cquadtree (
      const mzlib::math::cvector2d& top_left, 
      const mzlib::math::cvector2d& bottom_right, 
      const double smallest_node_width ) :
      m_root(std::make_shared<cquadnode<T>>())
   {
      m_root->create(top_left, bottom_right, smallest_node_width, nullptr);
   }
        
   cquadtree (const cquadtree&) = delete;
   cquadtree (cquadtree && ) = delete;
   cquadtree& operator= (const cquadtree&) = delete;
   cquadtree& operator= (cquadtree&&) = delete;
   virtual ~cquadtree () = default;
        
   bool add (cbinded_mass_centre<T> body) 
   { 
      return m_root->add(body); 
   }
   
   bool add (T data, math::cvector2d location, double mass = 0) 
   { 
      auto body = cbinded_mass_centre<T>(data, location, mass);
      return m_root->add(body); 
   }

   bool is_in (math::cvector2d location) const 
   { 
      return m_root->is_in(location); 
   }

   it_bodies begin () 
   { 
      return it_bodies(m_root.get()); 
   }
   
   it_bodies end () 
   { 
      return it_bodies(nullptr); 
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
    
} // namespace mzlib

#endif	/* QUADREEE_H */

