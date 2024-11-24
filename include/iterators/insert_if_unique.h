//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_INSERT_IF_UNIQUE_H
#define MZLIB_INSERT_IF_UNIQUE_H

#include <algorithm> // std::find

namespace mzlib {
    
// adds to container, unless the element is already in
// returns iterator to element in the container
template<class Iterator, class T, class InsertIt> 
void insert_if_unique (Iterator begin, Iterator end, const T& element, InsertIt inserter) 
{
   auto sought_element = std::find(begin, end, element);
   if (sought_element == end) {
      *inserter++ = element;
   }
}
    
} // namespace

#endif /* MZLIB_INSERT_IF_UNIQUE_H */
