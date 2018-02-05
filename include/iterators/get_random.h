//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_GET_RANDOM_H
#define MZLIB_GET_RANDOM_H

#include "../tools/random.h"

namespace mzlib {

template<class Iterator> 
Iterator get_random_element (const Iterator& start, const Iterator& end) 
{
   const size_t& size = std::distance(start, end);
   unsigned random = get_random_integer_between(0, size);
   Iterator result = start;
   std::advance(result, random);
   return result;
}

} // namespace

#endif // MZLIB_GET_RANDOM_H
