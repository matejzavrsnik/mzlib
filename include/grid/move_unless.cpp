//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "grid.h"
#include "move_unless.h"
#include "apply_drawing.h"
#include <gtest/gtest.h>

TEST(reusables, move_unless__by_one__right__can)
{
   mzlib::grid::type<long> grid = mzlib::grid::construct<long>(5, 8);
   mzlib::grid::type<long> grid_expected = mzlib::grid::construct<long>(5, 8);

   mzlib::grid::type<long> drawing = {
      {0,1,0},
      {1,1,1},
      {0,1,0},
   };

   mzlib::grid::apply_drawing(grid, drawing, {2,1});
   // 0 0 0 0 0 0 0 0
   // 0 0 0 1 0 0 0 0
   // 0 0 1 1 1 0 0 0
   // 0 0 0 1 0 0 0 0
   // 0 0 0 0 0 0 0 0

   mzlib::grid::apply_drawing(grid_expected, drawing, {3,1});
   // 0 0 0 0 0 0 0 0
   // 0 0 0 0 1 0 0 0
   // 0 0 0 1 1 1 0 0
   // 0 0 0 0 1 0 0 0
   // 0 0 0 0 0 0 0 0

   mzlib::grid::move_unless(grid, drawing, {2,1}, {3,1});

   ASSERT_EQ(grid, grid_expected);
}

TEST(reusables, move_unless__by_one__right__cannot)
{
   mzlib::grid::type<long> grid = mzlib::grid::construct<long>(5, 8);
   mzlib::grid::type<long> grid_expected = mzlib::grid::construct<long>(5, 8);

   mzlib::grid::type<long> drawing = {
      {0,1,0},
      {1,1,1},
      {0,1,0},
   };

   mzlib::grid::apply_drawing(grid, drawing, {2,1});
   // 0 0 0 0 0 0 0 0
   // 0 0 0 1 0 0 0 0
   // 0 0 1 1 1 0 0 0
   // 0 0 0 1 0 0 0 0
   // 0 0 0 0 0 0 0 0

   mzlib::grid::access(grid, {5,2}) = 1;
   // 0 0 0 0 0 0 0 0
   // 0 0 0 1 0 0 0 0
   // 0 0 1 1 1 1 0 0
   // 0 0 0 1 0 0 0 0
   // 0 0 0 0 0 0 0 0

   auto grid_before_move = grid;

   mzlib::grid::move_unless(grid, drawing, {2,1}, {3,1});

   ASSERT_EQ(grid, grid_before_move);
}