//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_PARITY_H
#define MZLIB_PARITY_H

#include <type_traits>

namespace mzlib 
{

template<typename T>
bool is_even(const T& num)
{
   static_assert(
      std::is_integral<T>::value, 
      "Error: can only determine parity of integral types");
   
   return (num % 2 == 0);
}

template<typename T>
bool is_odd(const T& num)
{
   return !is_even(num);
}

} // namespace

#endif // MZLIB_PARITY_H

