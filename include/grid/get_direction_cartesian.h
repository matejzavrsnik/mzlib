//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#pragma once

#include "grid.h"
#include "../abstract/direction.h"

namespace mzlib::grid {

inline
direction
get_direction_cartesian(
   const cell& from,
   const cell& to)
{
   auto dir_v = to-from;

   if(dir_v[0] == 0 && dir_v[1] > 0) return direction::n;
   if(dir_v[0] == 0 && dir_v[1] < 0) return direction::s;
   if(dir_v[0] > 0 && dir_v[1] == 0) return direction::e;
   if(dir_v[0] < 0 && dir_v[1] == 0) return direction::w;

   if(dir_v[0] > 0 && dir_v[1] > 0) return direction::ne;
   if(dir_v[0] < 0 && dir_v[1] > 0) return direction::nw;
   if(dir_v[0] > 0 && dir_v[1] < 0) return direction::se;
   if(dir_v[0] < 0 && dir_v[1] < 0) return direction::sw;

   return direction::centre;
}

}
