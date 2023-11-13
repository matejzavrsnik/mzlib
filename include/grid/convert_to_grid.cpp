//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "convert_to_grid.h"
#include <gtest/gtest.h>

TEST(convert_to_grid, basic)
{
   auto grid = mzlib::grid::convert_to_grid<int>({
      "aabqponm",
      "abcryxxl",
      "accszzxk",
      "acctuvwj",
      "abdefghi"
   });

   ASSERT_EQ(std::vector<int>({97, 97, 98,113,112,111,110,109}), grid[0]);
   ASSERT_EQ(std::vector<int>({97, 98, 99,114,121,120,120,108}), grid[1]);
   ASSERT_EQ(std::vector<int>({97, 99, 99,115,122,122,120,107}), grid[2]);
   ASSERT_EQ(std::vector<int>({97, 99, 99,116,117,118,119,106}), grid[3]);
   ASSERT_EQ(std::vector<int>({97, 98,100,101,102,103,104,105}), grid[4]);
}