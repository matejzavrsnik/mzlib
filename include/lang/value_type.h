//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_VALUE_TYPE_H
#define MZLIB_VALUE_TYPE_H

#include <type_traits>

namespace mzlib {
   
template<class T> 
using value_type = 
   std::remove_reference_t<
      decltype(*std::declval<T>())
   >;

} // namespace

#endif // MZLIB_IS_LAST_H
