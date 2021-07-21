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
#include "../nature/body.h"

namespace mzlib {

// Const iterator through all bodies
// The purpouse if this custom iterator is to peel object reference out of 
// unique_ptr structure that is actually stored in vector
class quadtree_it_bodies : public std::iterator<std::forward_iterator_tag, body_core2d>
{

private:

   using iterator_type = typename std::vector<std::unique_ptr<body_core2d>>::const_iterator;
   iterator_type m_body_it;

public:

   explicit quadtree_it_bodies (iterator_type it) : 
      m_body_it(it) 
   {
   }

   quadtree_it_bodies (quadtree_it_bodies&&) = default;
   quadtree_it_bodies (const quadtree_it_bodies&) = default;

   quadtree_it_bodies* operator++ () 
   { 
      ++m_body_it;
      return this; 
   }
        
   quadtree_it_bodies* operator++ (int) 
   {
      ++m_body_it; //todo: lies, damned lies!!
      return this; 
   }

   body_core2d const * operator-> () const
   { 
      return (*m_body_it).get();
   }

   const body_core2d& operator* () const
   { 
      return *(*m_body_it); 
   }
   
   bool operator== (const quadtree_it_bodies& other) const 
   { 
      // Infinite recursion guard
      if(this == &other) return true;
      // forward equality to actual iterator
      return (this->m_body_it == other.m_body_it);  
   }

   bool operator!= (const quadtree_it_bodies& other) const 
   { 
      return !(*this == other); 
   }
};

} // namespace

#endif /* MZLIB_QUADTREE_IT_BODIES_H */
