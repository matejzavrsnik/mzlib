//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#pragma once

#include "orient.h"
#include "is_in.h"
#include <utility>

namespace mzlib::interval
{

template <typename T>
bool
overlap (
   const std::pair<T, T>& one,
   const std::pair<T, T>& other
)
{
   return is_in<T>(other, one.first) || is_in<T>(other, one.second)
      || is_in<T>(one, other.first) || is_in<T>(one, other.second);
}

}
