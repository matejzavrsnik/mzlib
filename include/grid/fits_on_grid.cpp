//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "fits_on_grid.h"
#include <gtest/gtest.h>

TEST(fits_on_grid, does)
{
   mzlib::grid::type<long> grid = mzlib::grid::construct<long>(5, 8);

   mzlib::grid::type<long> drawing = {
      {0,1,0},
      {1,1,1},
      {0,1,0},
   };

   ASSERT_TRUE(mzlib::grid::fits_on_grid(grid, drawing, {5,2}));
   // 0 0 0 0 0 0 0 0
   // 0 0 0 0 0 0 0 0
   // 0 0 0 0 0 0 1 0
   // 0 0 0 0 0 1 1 1
   // 0 0 0 0 0 0 1 0
}

TEST(fits_on_grid, does_not)
{
   mzlib::grid::type<long> grid = mzlib::grid::construct<long>(5, 8);

   mzlib::grid::type<long> drawing = {
      {0,1,0},
      {1,1,1},
      {0,1,0},
   };

   ASSERT_FALSE(mzlib::grid::fits_on_grid(grid, drawing, {6,2}));
   // 0 0 0 0 0 0 0 0
   // 0 0 0 0 0 0 0 0
   // 0 0 0 0 0 0 0 1
   // 0 0 0 0 0 0 1 1 1
   // 0 0 0 0 0 0 0 1
}