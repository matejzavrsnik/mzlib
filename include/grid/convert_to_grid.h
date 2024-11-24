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
mzlib::grid::type<T>
convert_to_grid (
   std::vector<std::string> vector_of_strings
)
{
   mzlib::grid::type<T> grid;
   for (auto line: vector_of_strings)
   {
      std::vector<T> row;
      for (auto cell: line)
         row.push_back(cell);
      grid.push_back(row);
   }
   return grid;
}

}

}
