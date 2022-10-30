//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

// Generic version of contains substring.
// Since I've had to write an iterator based solution for strings,
// why not make it totally generic.

#ifndef MZLIB_CONTAINS_RANGE_H
#define MZLIB_CONTAINS_RANGE_H

#include "../lang/value_type.h"
#include <functional>
#include <utility>

namespace mzlib {

// finds a range in a collection
// if found, returns an iterator to the collection where the range starts
// if not found, returns end iterator of the collection
   
template <
   typename Iterator,
   typename ValueType = mzlib::value_type<Iterator>
>
inline Iterator contains_range(
   Iterator whole_begin, Iterator whole_end, 
   Iterator range_begin, Iterator range_end,
   // custom comparison functor comes handy in cases like
   // case insensitive char equality comparator
   bool (*equal)(const ValueType&, const ValueType&) =
      [](const ValueType& el1, const ValueType& el2) 
         { return (el1 == el2); } )
{
   if (range_begin == range_end) return whole_begin;
   
   // On some level I enjoy looking at this code :)
   
   for(auto full_it = whole_begin; full_it != whole_end; ++full_it)
   for(auto cmp_it = full_it, sub_it = range_begin; cmp_it != whole_end; ++cmp_it)
      if (!equal(*cmp_it, *sub_it)) break;
      else if (++sub_it == range_end) return full_it; // found
      
   return whole_end; // didn't find
}

} // namespace

#endif // MZLIB_CONTAINS_RANGE_H
