//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#pragma once

#include "grid.h"

namespace mzlib::grid {

inline long
manhattan_distance (
   const cell& a,
   const cell& b
)
{
   return abs(a[0] - b[0]) + abs(a[1] - b[1]);
}

}
