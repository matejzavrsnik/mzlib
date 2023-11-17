//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include <gtest/gtest.h>

#include "get_direction_cartesian.h"
#include "grid.h"

TEST(reusables, get_direction_cartesian)
{
   // 2 . . .
   // 1 . o .
   // 0 . . .
   //   0 1 2
   mzlib::grid::cell pos{1,1};

   // 2 . . .
   // 1 m o .
   // 0 . . .
   //   0 1 2
   ASSERT_EQ(mzlib::direction::w, mzlib::grid::get_direction_cartesian(pos, {0, 1}));

   // 2 . . .
   // 1 . o m
   // 0 . . .
   //   0 1 2
   ASSERT_EQ(mzlib::direction::e, mzlib::grid::get_direction_cartesian(pos, {2, 1}));

   // 2 . m .
   // 1 . o .
   // 0 . . .
   //   0 1 2
   ASSERT_EQ(mzlib::direction::n, mzlib::grid::get_direction_cartesian(pos, {1, 2}));

   // 2 . . .
   // 1 . o .
   // 0 . m .
   //   0 1 2
   ASSERT_EQ(mzlib::direction::s, mzlib::grid::get_direction_cartesian(pos, {1, 0}));

   // 2 . . .
   // 1 . o .
   // 0 m . .
   //   0 1 2
   ASSERT_EQ(mzlib::direction::sw, mzlib::grid::get_direction_cartesian(pos, {0, 0}));

   // 2 m . .
   // 1 . o .
   // 0 . . .
   //   0 1 2
   ASSERT_EQ(mzlib::direction::nw, mzlib::grid::get_direction_cartesian(pos, {0, 2}));

   // 2 . . .
   // 1 . o .
   // 0 . . m
   //   0 1 2
   ASSERT_EQ(mzlib::direction::se, mzlib::grid::get_direction_cartesian(pos, {2, 0}));

   // 2 . . m
   // 1 . o .
   // 0 . . .
   //   0 1 2
   ASSERT_EQ(mzlib::direction::ne, mzlib::grid::get_direction_cartesian(pos, {2, 2}));

   // 2 . . .
   // 1 . m .
   // 0 . . .
   //   0 1 2
   ASSERT_EQ(mzlib::direction::centre, mzlib::grid::get_direction_cartesian(pos, {1, 1}));
}