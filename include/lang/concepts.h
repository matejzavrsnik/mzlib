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
concept incrementable =
   requires (T a) {
      { ++a } -> std::same_as<T&>;
      { a++ } -> std::same_as<T>;
      { a+1 } -> std::same_as<T>;
      { a+=1 } -> std::same_as<T&>;
};

template<typename T>
concept assignable =
   requires (T a, T b) {
      { a = b } -> std::same_as<T>;
};
   
template<class T>
concept dereferencable =
   requires (T a) { *a; };

// TODO: specialise iterable 
template<typename T>
concept iterable =
   requires (T a) {
         requires incrementable<T>;
         requires dereferencable<T>;
         requires assignable<decltype(*a)>;
      };

template<typename String>
concept readable_string =
   requires (String s)
   {   
      s[0];
      { s.length() } -> std::integral;
   };
   
template<typename String>
concept writable_string =
   readable_string<String> &&
   requires (String s1, String s2)
   {   
      s1 = s2;
      s1 += s2;
   };
   
} // namespace

#endif // MZLIB_IS_LAST_H
