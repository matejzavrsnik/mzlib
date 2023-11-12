//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_GREATER_THAN_H
#define MZLIB_GREATER_THAN_H

#include <functional>

namespace mzlib
{

template <typename T>
auto
greater_than (const T& value) -> decltype(std::bind(std::greater<T>(), std::placeholders::_1, value))
{
   return std::bind(std::greater<T>(), std::placeholders::_1, value);
}

}

#endif // MZLIB_GREATER_THAN_H
