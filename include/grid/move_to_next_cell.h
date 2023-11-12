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

// return: did it advance the coordinate? To be able to tell when to stop.
inline bool
move_to_next_cell (
   mzlib::grid::cell& c,
   const mzlib::grid::cell& from,
   const mzlib::grid::cell& to
)
{
   if (c[1] == to[1] - 1 && c[0] == to[0] - 1)
      return false;

   if (++c[0] >= to[0])
   {
      c[0] = from[0];
      ++c[1];
   }

   return true;
}

}

}
