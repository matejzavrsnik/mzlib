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

template <typename T, typename Predicate>
bool
exists_in (
   const mzlib::grid::type<T>& g,
   Predicate pred
)
{
   for (const auto& row: g)
      for (const auto& cell_value: row)
         if (pred(cell_value))
            return true;
   return false;
}

} // grid

} // mzlib