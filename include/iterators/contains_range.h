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

#include <functional>

namespace mzlib {

template <class Iterator>
inline bool contains_range(
   Iterator whole_begin, Iterator whole_end, 
   Iterator range_begin, Iterator range_end,
   std::function<bool(Iterator, Iterator)> equal =
      [](Iterator it1, Iterator it2) { return (*it1 == *it2); } )
{
   if (range_begin == range_end) return true;
   
   // On some level I enjoy looking at this code :)
   
   for(auto full_it = whole_begin; full_it != whole_end; ++full_it)
   for(auto cmp_it = full_it, sub_it = range_begin; cmp_it != whole_end; ++cmp_it)
      if (!equal(cmp_it, sub_it)) break;
      else if (++sub_it == range_end) return true; // found
      
   return false; // didn't find
}

} // namespace

#endif // MZLIB_CONTAINS_RANGE_H
