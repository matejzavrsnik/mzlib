//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef SET_INTERSECTION_H
#define SET_INTERSECTION_H

#include <set>
#include <type_traits>
#include <utility>
#include <iterator>

namespace mzlib {

// Motivation for custom operations on sets: std version works on sorted
// collections which is understandable, but because of that it doesn't
// work with custom equality comparisons when they don't agree with
// sorting method. Example, substrings: if a string is considered to be
// equal when one contains the other as substring. How do you sort them
// so that you could still apply std lib sets operations on them?

template<
   class InputIt, class OutputIt,
   class ValueType = std::remove_reference_t<decltype(std::declval<InputIt>().operator*())>
>
void set_intersection(
   InputIt a_begin, InputIt a_end,
   InputIt b_begin, InputIt b_end,
   OutputIt inserter,
   bool (*equal)(const ValueType&, const ValueType&) =
      [](const ValueType& el1, const ValueType& el2) 
         { return (el1 == el2); } )
{
   for(auto a_it = a_begin; a_it != a_end; ++a_it)
   for(auto b_it = b_begin; b_it != b_end; ++b_it)
      if(equal(*a_it, *b_it))
         *inserter = *b_it;
}
         
template<
   class InputIt,
   class ValueType = std::remove_reference_t<decltype(std::declval<InputIt>().operator*())>
>
std::set<ValueType> set_intersection(
   InputIt a_begin, InputIt a_end,
   InputIt b_begin, InputIt b_end,
   bool (*equal)(const ValueType&, const ValueType&) =
      [](const ValueType& el1, const ValueType& el2) 
         { return (el1 == el2); } )
{
   std::set<ValueType> result;
   set_intersection(
      a_begin, a_end, 
      b_begin, b_end, 
      std::inserter(result, result.end()),
      equal);
   return result;
}

}

#endif /* SET_INTERSECTION_H */

