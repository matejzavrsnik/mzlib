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
   mzlib::print(std::vector{1,2,3,4,5,6}, ss);
   ASSERT_EQ("[1,2,3,4,5,6]\n", ss.view());
}

TEST(print_iterables, vector_grid_cells)
{
   std::stringstream ss;
   mzlib::print(std::vector<mzlib::grid::cell>({{1,2},{3,4},{5,6}}), ss);
   ASSERT_EQ("[[1,2],[3,4],[5,6]]\n", ss.view());
}

TEST(print_iterables, map_int_string)
{
   std::stringstream ss;
   mzlib::print(std::map<int, std::string>({{1,"one"},{2,"two"},{3,"three"}}), ss);
   ASSERT_EQ("[[1,one]\n,[2,two]\n,[3,three]\n]\n", ss.view());
}
