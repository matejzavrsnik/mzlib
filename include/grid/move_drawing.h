//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#pragma once

#include "grid.h"
#include "apply_drawing.h"
#include "drawing_operation.h"

namespace mzlib
{

namespace grid
{

template <typename T>
bool
move_drawing (
   mzlib::grid::type<T>& canvas,
   const mzlib::grid::type<T>& drawing,
   const mzlib::grid::cell& coor_from,
   const mzlib::grid::cell& coor_to
)
{
   return apply_drawing(canvas, drawing, coor_from, drawing_operation::subtract)
      && apply_drawing(canvas, drawing, coor_to, drawing_operation::add);
}

}

}
