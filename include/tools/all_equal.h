//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_ALL_EQUAL_H
#define MZLIB_ALL_EQUAL_H

#include <algorithm>
#include <functional>

namespace mzlib {

// shorthand to check if all container elements equal to value
template<typename Container, typename T>
bool all_equal(const Container& container, T value)
{
   return std::all_of(
      container.cbegin(), 
      container.cend(), 
      std::equal_to(value));
}

} // namespace

#endif // MZLIB_ALL_EQUAL_H

