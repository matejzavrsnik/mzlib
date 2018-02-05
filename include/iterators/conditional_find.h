//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_CONDITIONAL_FIND_ITERATOR_H
#define MZLIB_CONDITIONAL_FIND_ITERATOR_H

#include "distance_comparison.h"

namespace mzlib {
    
template<class Iterator>
Iterator last_where_value_smaller_then_next(Iterator begin, Iterator end)
{
   if (mzlib::is_distance_smaller(begin, end, 2)) 
      return end; // nothing to find
   
   auto next = end;
   auto prev = next-1;
   
   while(prev != begin) 
      if (*(--prev) < *(--next)) 
         return prev;
   
   return end; // not found
}

template<class Iterator, class T>
Iterator last_where_value_larger_then_given(Iterator begin, Iterator end, T value_given)
{
   auto last = end;
   
   while(last != begin) 
      if (*(--last) > value_given) 
         return last;
   
   return end; // not found
}

} // namespace

#endif // MZLIB_CONDITIONAL_FIND_ITERATOR_H
