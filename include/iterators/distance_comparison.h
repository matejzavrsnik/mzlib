//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_ITERATOR_DISTANCE_COMPARISON_H
#define MZLIB_ITERATOR_DISTANCE_COMPARISON_H

namespace mzlib {
    
// For when you only want to know if it is larger than some value, for instance
// if you are checking if there is at least one element in the container, or at
// least two, or whatever. You could use std::distance and compare, but that has
// linear complexity of N, because it iterates the whole container and if you are 
// just checking if at least two elements are present, that is a huge overhead. 
template<class Iterator>
bool is_distance_larger(Iterator it1, Iterator it2, size_t distance)
{
   do {
      if(it1==it2) 
         return false;
      it1 = std::next(it1);
   }
   while (distance--);
   return true;
}

template<class Iterator>
bool is_distance_smaller(Iterator it1, Iterator it2, size_t distance)
{
   distance--; // because the question is not if distance is equal
   do {
      if(it1==it2) 
         return true;
      it1 = std::next(it1);
   }
   while (distance--);
   return false;
}

// It did occur to me to have one function where you specify if you want to ask
// if larger, smaller, or equal, but the implementation included an if-branch
// too convoluted for a simple problem like this. Readability and robustness
// over cleverness, I say.
template<class Iterator>
bool is_distance_equal(Iterator it1, Iterator it2, size_t distance)
{
   std::advance(it1, distance);
   if(it1==it2) 
      return true;
   return false;
}

} // namespace

#endif // MZLIB_ITERATOR_DISTANCE_COMPARISON_H
