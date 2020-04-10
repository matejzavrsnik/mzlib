//
// Copyright (c) 2019 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_CONCEPTS_H
#define MZLIB_CONCEPTS_H

#include "../tools/missing_std.h"

namespace mzlib {
   
// Intuitively I feel like I should put concepts in own namespace, but let's try
// working with them as if they were any other types, just like they were meant 
// to be used

template<class T> 
concept bool incrementable =
   requires (T a) { 
      { ++a } -> T;
      { a++ } -> T;
      { a+1 } -> T;
      { a+=1 };
};

template<typename T>
concept bool assignable = 
   requires (T a, T b) { 
      { a = b } -> T; 
};
   
template<class T, class U>
concept bool dereferencable = 
   requires (T a, U b) { 
      { *a } -> U; 
};

// TODO: specialise iterable 
template<typename T>
concept bool iterable = 
   requires (T a) {
      incrementable<T> && 
      assignable<T> &&
      dereferencable<T>;
};

template<typename String>
concept bool readable_string =
   requires (String s)
   {   
      s[0];
   };
   
template<typename String>
concept bool writable_string =
   readable_string<String> &&
   requires (String s1, String s2)
   {   
      s1 = s2;
      s1 += s2;
   };
   
} // namespace

#endif // MZLIB_IS_LAST_H
