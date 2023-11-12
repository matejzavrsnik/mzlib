//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_EQUAL_TO_H
#define MZLIB_EQUAL_TO_H

#include <functional>

namespace mzlib
{

template <typename T>
auto
equal_to (const T& value) -> decltype(std::bind(std::equal_to<T>(), std::placeholders::_1, value))
{
   return std::bind(std::equal_to<T>(), std::placeholders::_1, value);
}

}

#endif // MZLIB_EQUAL_TO_H
