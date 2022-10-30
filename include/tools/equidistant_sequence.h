//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_EQUIDISTANT_SEQUENCE_H
#define MZLIB_EQUIDISTANT_SEQUENCE_H

#include <optional>
#include "../iterators/fast_forward.h"

namespace mzlib {

template<class Container, class Letter, class Iterator>
std::optional<Container> create_equidistant_sequence(
   Iterator begin,
   Iterator end,
   unsigned int desired_sequence_length,
   const unsigned int elements_to_skip_between,
   // cppcheck-suppress passedByValue
   std::function<bool(const Letter&)> counts_as_letter)
{
   Container result_candidate;
   
   begin = fast_forward(begin, end, counts_as_letter);
   
   while (begin != end && desired_sequence_length > 0) {
      
      // add letter to final result
      result_candidate.push_back(*begin); 
      --desired_sequence_length;
      
      // prepare the next letter
      int iterator_increments_left = elements_to_skip_between + 1;
      while (begin != end && iterator_increments_left > 0) {

         begin = std::next(begin);
         begin = fast_forward(begin, end, counts_as_letter);
         --iterator_increments_left;
      }
   }
   
   if (begin == end && desired_sequence_length > 0)
      return std::optional<Container>();
   else
      return std::optional<Container>(result_candidate);
}

} // namespace

#endif // MZLIB_EQUIDISTANT_SEQUENCE_H
