//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "../grid/grid.h" // definition of grid::cell
#include <vector>
#include "print_std_pair.h" // operator<< for std::pair
#include "print_iterables.h"
#include <gtest/gtest.h>

TEST(print_iterables, vector_integers)
{
   std::stringstream ss;
   mzlib::print(std::vector{1,2,3,4,5,6}, {.stream=ss});
   ASSERT_EQ("[1,2,3,4,5,6]\n", ss.view());
}

TEST(print_iterables, vector_grid_cells)
{
   std::stringstream ss;
   mzlib::print(std::vector<mzlib::grid::cell>({{1,2},{3,4},{5,6}}), {.stream=ss});
   ASSERT_EQ(
      "[[1,2]\n"
      ",[3,4]\n"
      ",[5,6]\n]\n", ss.view());
}

TEST(print_iterables, set_grid_cells)
{
   std::stringstream ss;
   mzlib::print(std::set<mzlib::grid::cell>({{1,2},{3,4},{5,6}}), {.stream=ss});
   ASSERT_EQ(
      "[[1,2]\n"
      ",[3,4]\n"
      ",[5,6]\n]\n", ss.view());
}

TEST(print_iterables, grid_cell)
{
   std::stringstream ss;
   mzlib::print(mzlib::grid::cell{1,2}, {.stream=ss});
   ASSERT_EQ("[1,2]\n", ss.view());
}

TEST(print_iterables, map_int_string)
{
   std::stringstream ss;
   mzlib::print(std::map<int, std::string>({{1,"one"},{2,"two"},{3,"three"}}), {.stream=ss});
   ASSERT_EQ(
      "[[1,one]\n"
      ",[2,two]\n"
      ",[3,three]\n]\n", ss.view());
}

TEST(print_iterables, grid_of_integers)
{
   std::stringstream ss;
   mzlib::grid::type<long> grid = {
      {1, 2, 3, 4, 5},
      {2, 3, 4, 5, 6},
      {3, 4, 5, 6, 7},
      {4, 5, 6, 7, 8},
      {5, 6, 7, 8, 9}
   };
   mzlib::print(grid, {.stream=ss});
   ASSERT_EQ(
      "[[1,2,3,4,5]\n"
      ",[2,3,4,5,6]\n"
      ",[3,4,5,6,7]\n"
      ",[4,5,6,7,8]\n"
      ",[5,6,7,8,9]\n]\n", ss.view());
}

TEST(print_iterables, grid_of_integers_can_set_align)
{
   std::stringstream ss;
   mzlib::grid::type<long> grid = {
      {1, 2, 3, 4, 5},
      {2, 3, 4, 5, 6},
      {3, 4, 5, 6, 7},
      {4, 5, 6, 7, 8},
      {5, 6, 7, 8, 9}
   };
   mzlib::print(grid, {.align=4, .stream=ss});

   ASSERT_EQ(
      "[[   1,   2,   3,   4,   5]\n"
      ",[   2,   3,   4,   5,   6]\n"
      ",[   3,   4,   5,   6,   7]\n"
      ",[   4,   5,   6,   7,   8]\n"
      ",[   5,   6,   7,   8,   9]\n]\n", ss.view());
}

TEST(print_iterables, grid_of_integers_can_set_substitutions)
{
   std::stringstream ss;
   mzlib::grid::type<long> grid = {
      {1, 2, 3, 4, 5},
      {2, 3, 4, 5, 6},
      {3, 4, 5, 6, 7},
      {4, 5, 6, 7, 8},
      {5, 6, 7, 8, 9}
   };
   mzlib::print(grid, {.stream=ss, .substitutions={{4, "X"}, {5, "Y"}}});

   ASSERT_EQ(
      "[[1,2,3,X,Y]\n"
      ",[2,3,X,Y,6]\n"
      ",[3,X,Y,6,7]\n"
      ",[X,Y,6,7,8]\n"
      ",[Y,6,7,8,9]\n]\n", ss.view());
}