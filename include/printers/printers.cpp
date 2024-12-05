//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "all.h"

#include "../grid/grid.h" // definition of grid::cell

#include <vector>
#include <ranges>

#include <gtest/gtest.h>

TEST(print_iterables, vector_integers)
{
   std::stringstream ss;
   mzlib::print(std::vector{1,2,3,4,5,6}, {.stream=ss});
   ASSERT_EQ("[1,2,3,4,5,6]\n", ss.view());
}

TEST(print_iterables, vector_strings)
{
   std::stringstream ss;
   mzlib::print(std::vector<std::string>{"123","456"}, {.stream=ss});
   ASSERT_EQ("[123,456]\n", ss.view());
}

TEST(print_iterables, vector_string_views)
{
   std::stringstream ss;
   mzlib::print(std::vector<std::string_view>{"123","456"}, {.stream=ss});
   ASSERT_EQ("[123,456]\n", ss.view());
}

TEST(print_iterables, not_necessary_to_provide_parameters)
{
   mzlib::print(std::vector<int>());
   mzlib::print("text");
   mzlib::print(1);
   mzlib::print(std::make_pair<int,int>(1,2));
   ASSERT_TRUE(true); //compiles
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

TEST(print_iterables, pair_of_int_string)
{
   std::stringstream ss;
   mzlib::print(std::make_pair<int,std::string>(1,"a string"), {.stream=ss});
   ASSERT_EQ("[1,a string]\n", ss.view());
}

TEST(print_iterables, vector_pairs_of_int_string)
{
   std::stringstream ss;
   mzlib::print(std::vector<std::pair<int,std::string>>({{1,"Aa"}, {2, "Bb"}, {3, "Cc"}}), {.stream=ss});
   ASSERT_EQ(
      "[[1,Aa]\n"
      ",[2,Bb]\n"
      ",[3,Cc]\n"
      "]\n", ss.view());
}

TEST(print_iterables, pair_of_vector_string)
{
   std::stringstream ss;
   mzlib::print(std::make_pair<std::vector<int>,std::string>({1, 2, 3},"Abc"), {.stream=ss});
   ASSERT_EQ(
      "[[1,2,3]\n"
      ",Abc]\n", ss.view());
}

TEST(print_iterables, vector_of_pairs_of_vector_string)
{
   std::stringstream ss;
   std::vector<std::pair<std::vector<int>, std::string>> the_abomination = {
      {{1, 2, 3},"ABC"},
      {{4, 5, 6},"DEF"},
      {{7, 8, 9},"GHI"}
   };
   mzlib::print(the_abomination, {.stream=ss});
   //mzlib::print(the_abomination, {.stream=std::cout});
   ASSERT_EQ(
      "[[[1,2,3]\n"
      ",ABC]\n"
      ",[[4,5,6]\n"
      ",DEF]\n"
      ",[[7,8,9]\n"
      ",GHI]\n"
      "]\n", ss.view());
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
   mzlib::print(grid, {.stream=ss, .substitutions={{"4", "X"}, {"5", "Y"}}});

   ASSERT_EQ(
      "[[1,2,3,X,Y]\n"
      ",[2,3,X,Y,6]\n"
      ",[3,X,Y,6,7]\n"
      ",[X,Y,6,7,8]\n"
      ",[Y,6,7,8,9]\n]\n", ss.view());
}

TEST(print_iterables, iota_view)
{
   std::stringstream ss;
   auto view = std::ranges::views::iota(1,5);
   mzlib::print(view, {.stream=ss});
   ASSERT_EQ("[1,2,3,4]\n", ss.view());
}

TEST(print_iterables, transform_view)
{
   std::stringstream ss;
   auto view = std::ranges::views::iota(1,5) | std::views::transform([](auto it){ return it*2; });
   mzlib::print(view, {.stream=ss});
   ASSERT_EQ("[2,4,6,8]\n", ss.view());
}

// Can't. Not a feature of filter_view. See comment in code for more details.
// Need to convert to vector first if you want to do that.
TEST(print_iterables, filter_view)
{
   std::stringstream ss;
   auto view = std::ranges::views::iota(1,5) | std::views::filter([](const int it){ return it % 2 == 0; });
   mzlib::print(view | std::ranges::to<std::vector<int>>(), {.stream=ss});
   ASSERT_EQ("[2,4]\n", ss.view());
}

TEST(print_iterables, std_tuple_int_string)
{
   std::stringstream ss;
   mzlib::print(std::make_tuple(12, std::string{"santa"}), {.stream=ss});
   ASSERT_EQ("[12,santa]\n", ss.view());
}

TEST(print_iterables, std_tuple_int_vector_string)
{
   std::stringstream ss;
   mzlib::print(std::make_tuple(12, std::vector<std::string>{"santa", "klaus"}), {.stream=ss});
   ASSERT_EQ("[12,[santa,klaus]\n"
             "]\n", ss.view());
}

TEST(print_iterables, yeah_but_can_you_print_simple_text)
{
   std::stringstream ss;

   mzlib::print("Scientific truth is beyond loyalty and disloyalty.", {.stream=ss});

   ASSERT_EQ("Scientific truth is beyond loyalty and disloyalty.", ss.view());
}


TEST(print_iterables, yeah_but_can_you_print_simple_number)
{
   std::stringstream ss;

   mzlib::print(1, {.stream=ss});

   ASSERT_EQ("1", ss.view());
}