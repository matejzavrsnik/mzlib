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
fits_on_grid (
   const mzlib::grid::type<T>& grid,
   const mzlib::grid::type<T>& drawing,
   const mzlib::grid::cell& c
)
{
   return c[0] >= 0 && c[1] >= 0 && mzlib::grid::width(grid) >= c[0] + mzlib::grid::width(drawing)
      && mzlib::grid::height(grid) >= c[1] + mzlib::grid::height(drawing);
}

}

}