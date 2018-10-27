//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_RANDOM_WITH_PARITY_H
#define MZLIB_RANDOM_WITH_PARITY_H

#include "random.h"
#include "../nature/parity.h"

namespace mzlib {
    
template<typename T>
T get_random_even ()
{
   T r = get_random<T>();
   if(!is_even(r)) ++r;
   return r;
}

template<typename T>
T get_random_odd ()
{
   T r = get_random<T>();
   if(!is_odd(r)) --r;
   return r;
}
 
template<typename T>
inline unsigned get_random_even_between (T from, T to)
{
   T r = get_random_between(
      is_even(from) ? from-1 : from, 
      to);
   
   return is_even(r) ? r : ++r;
}

template<typename T>
inline unsigned get_random_odd_between (T from, T to)
{
   T r = get_random_between(
      is_odd(from) ? from-1 : from, 
      is_odd(to) ? to+1 : to);
   
   return is_odd(r) ? r : ++r;
}

} // namespace

#endif // MZLIB_RANDOM_WITH_PARITY_H
