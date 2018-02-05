//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_FAST_MIN_H
#define MZLIB_FAST_MIN_H

namespace mzlib {
   
// Returns the smallest of three numbers 2x-3x faster than std::min({i,j,k})
template <class T> T& fast_min_ref (T& min1, T& min2, T& min3)
{
   // Beware, min-field ahead!
   return 
      min1 < min2 ?
         (min1 < min3 ? min1 : min3) :
         (min2 < min3 ? min2 : min3);
}

template <class T> T&& fast_min (T&& min1, T&& min2, T&& min3)
{
   // Beware, min-field ahead!
   return std::move(
      min1 < min2 ?
         (min1 < min3 ? min1 : min3) :
         (min2 < min3 ? min2 : min3));
}

} // namespace

#endif // MZLIB_FAST_MIN_H
