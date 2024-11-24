//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#pragma once

#include "orient.h"
#include <utility>
#include <vector>

namespace mzlib::interval
{

template <typename T>
bool
is_in (
   std::pair<T, T> interval,
   const T& value
)
{
   interval = orient(interval);
   return (value >= interval.first && value <= interval.second);
}

template <typename T>
bool
is_in (
   const std::vector<std::pair<T, T>>& intervals,
   const T& value
)
{
   // didn't go for std::any_of with std::bind because specifying function
   // overload made it look more awkward than for-loop
   for(const auto& interval : intervals)
      if(is_in(interval, value))
         return true;

   return false;
}

template <typename T>
bool
is_in (
   std::pair<T, T> inner,
   std::pair<T, T> outer
)
{
   return is_in(outer, inner.first)
      && is_in(outer, inner.second);
}

}
