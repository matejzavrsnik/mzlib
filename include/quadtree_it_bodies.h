//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_QUADTREE_IT_BODIES_H
#define MZLIB_QUADTREE_IT_BODIES_H

#include <iterator>
#include <memory>
#include <vector>
#include "quadtree.h"

namespace mzlib {

// Const iterator through all bodies
// The purpouse if this custom iterator is to peel object reference out of 
// unique_ptr structure that is actually stored in vector
template<class T>
class quadtree_it_bodies : 
   public std::iterator<std::forward_iterator_tag, cbinded_mass_centre2d<T>>
{

private:

   using iterator_type = typename std::vector<std::unique_ptr<cbinded_mass_centre2d<T>>>::const_iterator;
   iterator_type m_body_it;

public:

   explicit quadtree_it_bodies (iterator_type it) : 
      m_body_it(it) 
   { 
   }

   quadtree_it_bodies (quadtree_it_bodies&&) = default;
   quadtree_it_bodies (const quadtree_it_bodies&) = default;

   quadtree_it_bodies<T>* operator++ () 
   { 
      ++m_body_it;
      return this; 
   }
        
   quadtree_it_bodies<T>* operator++ (int) 
   {
      ++m_body_it; //todo: lies, damned lies!!
      return this; 
   }

   //todo: needs to be const
   cbinded_mass_centre2d<T> const * operator-> () const
   { 
      return (*m_body_it).get();
   }

   const cbinded_mass_centre2d<T>& operator* () const
   { 
      return *(*m_body_it); 
   }
   
   bool operator== (const quadtree_it_bodies<T>& other) const 
   { 
      // Infinite recursion guard
      if(this == &other) return true;
      // forward equality to actual iterator
      return (this->m_body_it == other.m_body_it);  
   }

   bool operator!= (const quadtree_it_bodies<T>& other) const 
   { 
      return !(*this == other); 
   }
};

} // namespace

#endif /* MZLIB_QUADTREE_IT_BODIES_H */
