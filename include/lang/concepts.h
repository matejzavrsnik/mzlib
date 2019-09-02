//
// Copyright (c) 2019 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_CONCEPTS_H
#define MZLIB_CONCEPTS_H

namespace mzlib {
   
template<class T> concept bool Incrementable =
   requires (T a) { 
      { ++a } -> T; 
};

template<typename T>
concept bool Assignable = 
   requires (T a, T b) { 
      { a = b } -> T; 
};
   
template<class T, class U>
concept bool Dereferencable = 
   requires (T a, U b) { 
      { *a } -> U; 
};

template<typename T>
concept bool IteratorConcept = 
   requires (T a) {
      Incrementable<T> && 
      Assignable<T> &&
      Dereferencable<T>;
};

} // namespace

#endif // MZLIB_IS_LAST_H
