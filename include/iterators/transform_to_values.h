//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include <algorithm>

#ifndef MZLIB_TRANSFORM_TO_VALUES_H
#define MZLIB_TRANSFORM_TO_VALUES_H

namespace mzlib {

// converts collection of iterators into collection of values
template<typename IteratorIterator, typename ValueIterator>
void transform_to_values(
   IteratorIterator iterator_begin, 
   IteratorIterator iterator_end, 
   ValueIterator values_begin)
{
   std::transform(
      iterator_begin, iterator_end, 
      values_begin,
      [](auto iterator){ return *iterator; });
}

} // namespace

#endif // MZLIB_TRANSFORM_TO_VALUES_H
