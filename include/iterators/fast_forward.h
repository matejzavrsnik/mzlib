//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_FAST_FORWARD_ITERATOR_UNTIL_H
#define MZLIB_FAST_FORWARD_ITERATOR_UNTIL_H

#include <functional>

namespace mzlib {
    
// Iterate forward in a container until the condition is met.
template<class Element, class Iterator>
Iterator fast_forward(
   Iterator begin,
   Iterator end,
   std::function<bool(const Element&)> condition)
{
   while (begin != end && !condition(*begin)) {
      begin = std::next(begin);
   }
   return begin;
}

} // namespace

#endif // MZLIB_FAST_FORWARD_ITERATOR_UNTIL_H
