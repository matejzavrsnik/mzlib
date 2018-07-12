//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_ITERATOR_VALUE_TYPE_H
#define MZLIB_ITERATOR_VALUE_TYPE_H

#include <type_traits>

namespace mzlib {

template<class Iterator> 
   using ItValueType = 
      std::remove_reference_t<
         decltype(
            std::declval<Iterator>().operator*()
         )
      >;

} // namespace

#endif // MZLIB_IS_LAST_H
