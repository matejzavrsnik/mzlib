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

// Checked this again some time later on http://quick-bench.com and was
// disappointed. My version is only faster if you can't afford optimisation
// level O2 on gcc and clang :( It literally compiles to the exact same 
// assembly most of the time, unbelievable!
   
// I am keeping it; I like my sad little function!
   
template <class T> T&& fast_min (T&& min1, T&& min2, T&& min3)
{
   // Beware, min-field ahead!
   return std::forward<T>(
      min1 < min2 ?
         (min1 < min3 ? min1 : min3) :
         (min2 < min3 ? min2 : min3));
}

} // namespace

#endif // MZLIB_FAST_MIN_H
