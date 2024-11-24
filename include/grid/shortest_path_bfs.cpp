//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "shortest_path_bfs.h"
#include "convert_to_grid.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>


TEST(single_source_shortest_path_bfs, demo)
{
   auto grid = mzlib::grid::convert_to_grid<int>({
      "aabqponm",
      "abcryxxl",
      "accszzxk",
      "acctuvwj",
      "abdefghi"
   });
   mzlib::grid::cell start{0, 0};

   auto steps_to_get_there = mzlib::grid::single_source_shortest_path_bfs(
      grid, start, mzlib::grid::destination_at_most_one_larger
   );

   // shortest path to every cell in this grid
   mzlib::grid::type<long> expected_shortest_paths = {
      {0,  1,  2, 19, 18, 17, 16, 15},
      {1,  2,  3, 20, 29, 28, 27, 14},
      {2,  3,  4, 21, 30, 31, 26, 13},
      {3,  4,  5, 22, 23, 24, 25, 12},
      {4,  5,  6,  7,  8,  9, 10, 11},
   };
   ASSERT_EQ(expected_shortest_paths, steps_to_get_there);

   // this is how you would read shortest path to one cell
   ASSERT_EQ(31, mzlib::grid::access(steps_to_get_there, {5,2}));
}

TEST(single_source_shortest_path_bfs, demo_with_custom_criterium)
{
   // let's say I want to get from a to b, but can't cross into x.
   auto grid = mzlib::grid::convert_to_grid<int>({
      "a.......",
      ".x....x.",
      ".x.b..x.",
      ".xxxxxx.",
      "........"
   });
   mzlib::grid::cell start{0, 0};

   auto steps_to_get_there = mzlib::grid::single_source_shortest_path_bfs(
      grid, start,
      [](auto grid, auto from, auto to) {
         return mzlib::grid::access(grid, to) != 'x';
      }
   );

   //mzlib::print(steps_to_get_there, {.align=4, .substitutions={{9223372036854775807, "?"}}});

   // shortest path to every cell in this grid
   auto max = std::numeric_limits<long>::max();
   mzlib::grid::type<long> expected_shortest_paths = {
      {0,  1,  2,  3,  4,  5,  6,  7},
      {1,max,  3,  4,  5,  6,max,  8},
      {2,max,  4,  5,  6,  7,max,  9},
      {3,max,max,max,max,max,max, 10},
      {4,  5,  6,  7,  8,  9, 10, 11},
   };
   ASSERT_EQ(expected_shortest_paths, steps_to_get_there);
}
