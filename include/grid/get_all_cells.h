//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#pragma once

#include "grid.h"
#include <vector>

namespace mzlib::grid
{

template <typename T>
std::vector<mzlib::grid::cell>
get_all_cells (
   const mzlib::grid::type<T>& field
)
{
   std::vector<mzlib::grid::cell> all;
   for (int y = 0; y < field.size(); ++y)
      for (int x = 0; x < field[0].size(); ++x)
         all.push_back(mzlib::grid::cell{x, y});
   return all;
}

}
