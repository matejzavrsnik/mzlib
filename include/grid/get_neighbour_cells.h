//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#pragma once

#include "is_in.h"
#include <vector>

namespace mzlib
{

namespace grid
{

template <typename T>
std::vector<cell>
get_neighbouring_cells (
   const type<T>& grid,
   const cell& c
)
{
   std::vector<cell> v{
      cell{c[0] + 1, c[1]},
      cell{c[0] - 1, c[1]},
      cell{c[0], c[1] + 1},
      cell{c[0], c[1] - 1}};

   std::vector<cell> results;
   for (auto it = v.begin(); it != v.end(); ++it)
      if (is_in(grid, *it))
         results.push_back(*it);
   return results;
}

}

}
