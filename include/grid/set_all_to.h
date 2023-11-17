//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#pragma once

#include <grid/grid.h>

namespace mzlib::grid {

template <typename T>
void
set_all_to (
   type<T>& grid,
   T value
)
{
   for (int row = 0; row < grid.size(); ++row)
      for (int col = 0; col < grid[0].size(); ++col)
         grid[row][col] = value;
}

}
