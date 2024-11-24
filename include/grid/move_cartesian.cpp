//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "move_cartesian.h"
#include <gtest/gtest.h>
#include "grid.h"

TEST(move_cartesian, all_cases)
{
   // 2 . . .
   // 1 . o .
   // 0 . . .
   //   0 1 2
   mzlib::grid::cell pos{1,1};

   // 2 . . .
   // 1 . o m
   // 0 . . .
   //   0 1 2
   ASSERT_EQ(mzlib::grid::cell({2,1}), mzlib::grid::move_cartesian(pos, mzlib::direction::e));

   // 2 . . .
   // 1 m o .
   // 0 . . .
   //   0 1 2
   ASSERT_EQ(mzlib::grid::cell({0,1}), mzlib::grid::move_cartesian(pos, mzlib::direction::w));

   // 2 . m .
   // 1 . o .
   // 0 . . .
   //   0 1 2
   ASSERT_EQ(mzlib::grid::cell({1,2}), mzlib::grid::move_cartesian(pos, mzlib::direction::n));

   // 2 . . .
   // 1 . o .
   // 0 . m .
   //   0 1 2
   ASSERT_EQ(mzlib::grid::cell({1,0}), mzlib::grid::move_cartesian(pos, mzlib::direction::s));

   // 2 . . m
   // 1 . o .
   // 0 . . .
   //   0 1 2
   ASSERT_EQ(mzlib::grid::cell({2,2}), mzlib::grid::move_cartesian(pos, mzlib::direction::ne));

   // 2 m . .
   // 1 . o .
   // 0 . . .
   //   0 1 2
   ASSERT_EQ(mzlib::grid::cell({0,2}), mzlib::grid::move_cartesian(pos, mzlib::direction::nw));

   // 2 . . .
   // 1 . o .
   // 0 . . m
   //   0 1 2
   ASSERT_EQ(mzlib::grid::cell({2,0}), mzlib::grid::move_cartesian(pos, mzlib::direction::se));

   // 2 . . .
   // 1 . o .
   // 0 m . .
   //   0 1 2
   ASSERT_EQ(mzlib::grid::cell({0,0}), mzlib::grid::move_cartesian(pos, mzlib::direction::sw));

   // 2 . . .
   // 1 . m .
   // 0 . . .
   //   0 1 2
   ASSERT_EQ(pos, mzlib::grid::move_cartesian(pos, mzlib::direction::centre));
}