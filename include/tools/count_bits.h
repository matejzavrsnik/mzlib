//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_COUNT_BITS_H
#define MZLIB_COUNT_BITS_H

#include <limits>
#include <type_traits>

namespace mzlib {

template <class T>
unsigned int count_bits(T n, short bit,
   typename std::enable_if_t<std::is_integral<T>::value>* = 0)
{
   // corner case
   if(bit==0 && n==0)
      return std::numeric_limits<T>::digits;
   
   unsigned int count = 0;
   while (n)
   {
      count += (n & bit);
      n >>= 1;
   }
   return count;
}

} // namespace

#endif // MZLIB_COUNT_BITS_H
