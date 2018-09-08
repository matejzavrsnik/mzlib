//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_COPY_TO_NESTED_ITERATORS_H
#define MZLIB_COPY_TO_NESTED_ITERATORS_H

#include "copy.h"
#include "../lang/value_type.h"
#include <iterator>

namespace mzlib {

// when copying into container of containers
   
template<class OutputIt, class InputIt>
constexpr auto copy_to_nested(
   InputIt  in_first,  const InputIt  in_last,
   OutputIt out_first, const OutputIt out_last)
      // return whatever type mzlib::copy returns
      -> decltype(copy(
         in_first, in_last, 
         out_first->begin(), out_first->end()))
{
   using copy_return_type = decltype(copy(
      in_first, in_last, 
      out_first->begin(), out_first->end()));
   copy_return_type copied;
           
   for(auto& nested = out_first; out_first != out_last; ++out_first) {
      copied = copy(
         in_first, in_last, 
         nested->begin(), nested->end());

      if(copied.input_it != in_last) {
         in_first = copied.input_it;
      }
      else {
         break;
      }
   }
   return copied;
}

} // namespace

#endif // MZLIB_COPY_TO_NESTED_ITERATORS_H
