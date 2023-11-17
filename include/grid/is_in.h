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

template <typename T>
bool
is_in (
   const type<T>& field,
   const cell& c
)
{
   if (c[0] < 0 || c[0] > field[0].size() - 1)
      return false;
   if (c[1] < 0 || c[1] > field.size() - 1)
      return false;
   return true;
}

}

}
