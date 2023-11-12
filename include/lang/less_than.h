//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_LESS_THAN_H
#define MZLIB_LESS_THAN_H

#include <functional>

namespace mzlib
{

template <typename T>
auto
less_than (const T& value) -> decltype(std::bind(std::less<T>(), std::placeholders::_1, value))
{
   return std::bind(std::less<T>(), std::placeholders::_1, value);
}

}

#endif // MZLIB_LESS_THAN_H
