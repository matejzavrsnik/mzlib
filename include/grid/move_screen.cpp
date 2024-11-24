//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "move_screen.h"

TEST(reusables, move_screen)
{
   //   0 1 2
   // 0 . . .
   // 1 . o .
   // 2 . . .
   const mzlib::grid::cell pos{1,1};

   //   0 1 2
   // 0 . . .
   // 1 . o m
   // 2 . . .
   ASSERT_EQ(mzlib::grid::cell({2,1}), mzlib::grid::move_screen(pos, mzlib::direction::e));

   //   0 1 2
   // 0 . . .
   // 1 m o .
   // 2 . . .
   ASSERT_EQ(mzlib::grid::cell({0,1}), mzlib::grid::move_screen(pos, mzlib::direction::w));

   //   0 1 2
   // 0 . m .
   // 1 . o .
   // 2 . . .
   ASSERT_EQ(mzlib::grid::cell({1,0}), mzlib::grid::move_screen(pos, mzlib::direction::n));

   //   0 1 2
   // 0 . . .
   // 1 . o .
   // 2 . m .
   ASSERT_EQ(mzlib::grid::cell({1,2}), mzlib::grid::move_screen(pos, mzlib::direction::s));

   //   0 1 2
   // 0 . . m
   // 1 . o .
   // 2 . . .
   ASSERT_EQ(mzlib::grid::cell({2,0}), mzlib::grid::move_screen(pos, mzlib::direction::ne));

   //   0 1 2
   // 0 m . .
   // 1 . o .
   // 2 . . .
   ASSERT_EQ(mzlib::grid::cell({0,0}), mzlib::grid::move_screen(pos, mzlib::direction::nw));

   //   0 1 2
   // 0 . . .
   // 1 . o .
   // 2 . . m
   ASSERT_EQ(mzlib::grid::cell({2,2}), mzlib::grid::move_screen(pos, mzlib::direction::se));

   //   0 1 2
   // 0 . . .
   // 1 . o .
   // 2 m . .
   ASSERT_EQ(mzlib::grid::cell({0,2}), mzlib::grid::move_screen(pos, mzlib::direction::sw));

   //   0 1 2
   // 0 . . .
   // 1 . m .
   // 2 . . .
   ASSERT_EQ(pos, mzlib::grid::move_screen(pos, mzlib::direction::centre));
}