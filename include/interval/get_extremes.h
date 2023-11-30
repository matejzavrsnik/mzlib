//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#pragma once

#include "orient.h"
#include "../lang/stl_algo_shorthands.h"
#include "../lang/exceptions.h"
#include <utility>
#include <vector>
#include <algorithm>

namespace mzlib::interval
{

template <typename T>
std::pair<T, T>
get_extremes (
   std::vector<std::pair<T, T>> intervals
)
{
   if (intervals.empty())
      throw mzlib::exception::is_empty();

   transform(intervals, orient<T>);

   auto min = std::min_element(
      intervals.begin(), intervals.end(), [] (
         auto a,
         auto b
      )
      {
         return a.first < b.first;
      }
   );
   auto max = std::max_element(
      intervals.begin(), intervals.end(), [] (
         auto a,
         auto b
      )
      {
         return a.second < b.second;
      }
   );
   return {min->first, max->second};
}

}
