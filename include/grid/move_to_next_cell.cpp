//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "move_to_next_cell.h"
#include <gtest/gtest.h>

TEST(move_to_next_cell, cases)
{
   mzlib::grid::cell c{5,7};

   ASSERT_TRUE(mzlib::grid::move_to_next_cell(c, {5, 7}, {8, 9}));
   ASSERT_EQ(mzlib::grid::cell({6,7}), c);

   ASSERT_TRUE(mzlib::grid::move_to_next_cell(c, {5, 7}, {8, 9}));
   ASSERT_EQ(mzlib::grid::cell({7,7}), c);

   ASSERT_TRUE(mzlib::grid::move_to_next_cell(c, {5, 7}, {8, 9}));
   ASSERT_EQ(mzlib::grid::cell({5,8}), c);

   ASSERT_TRUE(mzlib::grid::move_to_next_cell(c, {5, 7}, {8, 9}));
   ASSERT_EQ(mzlib::grid::cell({6,8}), c);

   ASSERT_TRUE(mzlib::grid::move_to_next_cell(c, {5, 7}, {8, 9}));
   ASSERT_EQ(mzlib::grid::cell({7,8}), c);

   ASSERT_FALSE(mzlib::grid::move_to_next_cell(c, {5, 7}, {8, 9}));
   ASSERT_EQ(mzlib::grid::cell({7,8}), c);
}

