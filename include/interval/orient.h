//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#pragma once

#include <utility>

namespace mzlib::interval
{

// Expected first <= second in this lib. what if it isn't? orient it!
template <typename T>
std::pair<T, T>
orient (
   std::pair<T, T> interval
)
{
   if (interval.first <= interval.second)
      return interval;

   std::swap(interval.second, interval.first);
   return interval;
}

}
