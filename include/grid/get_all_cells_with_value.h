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
inline std::vector<mzlib::grid::cell>
get_all_cells_with_value (
   const mzlib::grid::type<T>& field,
   int value
)
{
   std::vector<mzlib::grid::cell> all_of_value;
   for (int y = 0; y < field.size(); ++y)
      for (int x = 0; x < field[0].size(); ++x)
         if (mzlib::grid::access(field, mzlib::grid::cell{x, y}) == value)
            all_of_value.push_back(mzlib::grid::cell{x, y});
   //cout << all_of_value.size() << endl;
   return all_of_value;
}

}
