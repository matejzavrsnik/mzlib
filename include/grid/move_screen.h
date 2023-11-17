//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//
#pragma once

#include "../abstract/direction.h"
#include "grid.h"

namespace mzlib::grid
{

// screen: like pixels on screen
//
// 0 → 1
// ↓
// 1
//
// cell = {x, y}
// east = x -> increase
// north = y -> decrease

inline cell
move_screen (
   cell c,
   const direction d
)
{
   switch (d)
   {
   case direction::n: c += {0, -1};
      break;
   case direction::s: c += {0, 1};
      break;
   case direction::e: c += {1, 0};
      break;
   case direction::w: c += {-1, 0};
      break;

   case direction::ne: c += {1, -1};
      break;
   case direction::nw: c += {-1, -1};
      break;
   case direction::se: c += {1, 1};
      break;
   case direction::sw: c += {-1, 1};
      break;
   case direction::centre: break;
   }
   return c;
}

}
