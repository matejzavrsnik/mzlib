//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#pragma once

#include "../lang/greater_than.h"
#include "grid.h"
#include "exists_in.h"
#include "fits_on_grid.h"
#include "move_drawing.h"

namespace mzlib
{

namespace grid
{

template <typename T, typename Predicate = decltype(mzlib::greater_than(1))>
mzlib::grid::cell
move_unless (
   mzlib::grid::type<T>& grid,
   const mzlib::grid::type<T>& drawing,
   const mzlib::grid::cell& from,
   const mzlib::grid::cell& to,
   Predicate pred = mzlib::greater_than(1)
)
{
   if (fits_on_grid(grid, drawing, to))
   {
      // try to move first
      move_drawing(grid, drawing, from, to);
      // then check if it overlaps
      if (mzlib::grid::exists_in(grid, pred))
         // if it does, move back
         move_drawing(grid, drawing, to, from);
      else
         // if it doesn't, this is new coordinates
         return to;
   }
   // couldn't move
   return from;
}

}

}
