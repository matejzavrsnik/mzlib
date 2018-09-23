//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_FIND_H
#define MZLIB_FIND_H

#include <algorithm>
#include <set>

namespace mzlib {
   
// convenience function that finds in whole container instead
// of between two iterators
   
template<typename Container, typename T>
auto find(const Container& container, const T& value)
   -> decltype(container.cbegin())
{
   return std::find(container.cbegin(), container.cend(), value);
}

} // namespace

#endif // MZLIB_FIND_H
