//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#pragma once

#include "grid.h"

namespace mzlib
{

namespace grid
{

// touching or not is same in cartesian and screen coordinates
inline bool
are_touching (
   const mzlib::grid::cell& a,
   const mzlib::grid::cell& b
)
{
   auto diff = a - b;
   return abs(diff[0]) <= 1 && abs(diff[1]) <= 1;
}

}

}
