//
// Copyright (c) 2024 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#pragma once

#include "grid.h"
#include "drawing_operation.h"
#include "move_to_next_cell.h"

namespace mzlib
{

namespace grid
{

template <typename T>
bool
check_for_drawing (
   const mzlib::grid::type<T>& grid,
   const mzlib::grid::type<T>& drawing,
   const mzlib::grid::cell& c,
   T neutral_value = '.'
)
{
   mzlib::grid::cell drawing_pixel{0, 0};
   const mzlib::grid::cell drawing_size = mzlib::grid::size(drawing);
   do
   {
      auto canvas_pixel = drawing_pixel + c;
      const auto pixel_value = mzlib::grid::access(drawing, drawing_pixel);
      if (pixel_value == neutral_value)
         continue;
      const auto value_on_grid = mzlib::grid::access(grid, canvas_pixel);
      if (value_on_grid != pixel_value)
         return false;
   }
   while (mzlib::grid::move_to_next_cell(drawing_pixel, {0, 0}, drawing_size));

   return true;
}

}

}
