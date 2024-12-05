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
apply_drawing (
   mzlib::grid::type<T>& grid,
   const mzlib::grid::type<T>& drawing,
   const mzlib::grid::cell& c,
   const drawing_operation operation = drawing_operation::add
)
{
   // todo: if drawing too big, draw what fits and ignore the rest. currently I crash instead.
   mzlib::grid::cell drawing_pixel{0, 0};
   const mzlib::grid::cell drawing_size = mzlib::grid::size(drawing);
   do
   {
      auto canvas_pixel = drawing_pixel + c;
      const auto pixel_value = mzlib::grid::access(drawing, drawing_pixel);
      if (operation == drawing_operation::add)
         mzlib::grid::access(grid, canvas_pixel) += pixel_value;
      else if (operation == drawing_operation::subtract)
         mzlib::grid::access(grid, canvas_pixel) -= pixel_value;
   }
   while (move_to_next_cell(drawing_pixel, {0, 0}, drawing_size));

   return true;
}

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
