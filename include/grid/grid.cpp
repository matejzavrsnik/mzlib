//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "grid.h"
#include "gtest/gtest.h"

using namespace ::testing;

TEST(grid, enlarge_works)
{
   std::vector<std::vector<int>> vec {
      {1,2},
      {1,2,3}
   };

   // o -> exists
   // . -> doesn't
   // x -> requested

   // o o      o o o o
   // o o o -> o o o o
   //          o o o o
   //          o o o o
   
   mzlib::grid::enlarge(vec, 4, 3);

   ASSERT_EQ(4, vec.size());
   ASSERT_EQ(3, vec[0].size());
   ASSERT_EQ(3, vec[1].size());
   ASSERT_EQ(3, vec[2].size());
   ASSERT_EQ(3, vec[3].size());
}

TEST(grid, enlarge_keeps_values)
{
   std::vector<std::vector<int>> vec {
      {1,2},
      {3,4,5}
   };
   
   // 1 2      1 2 o
   // 1 2 3 -> 1 2 3
   //          o o o
   //          o o o
   
   mzlib::grid::enlarge(vec, 3, 4);
   
   ASSERT_EQ(1, vec[0][0]);
   ASSERT_EQ(2, vec[0][1]);
   
   ASSERT_EQ(3, vec[1][0]);
   ASSERT_EQ(4, vec[1][1]);
   ASSERT_EQ(5, vec[1][2]);
}

TEST(grid, construct_works)
{
   std::vector<std::vector<int>> vec =
      mzlib::grid::construct(3, 4, 15);
   
   ASSERT_EQ(3, vec.size());
   ASSERT_EQ(4, vec[0].size());
   ASSERT_EQ(4, vec[1].size());
   ASSERT_EQ(4, vec[2].size());
   
   for(const auto& v : vec)
   for(const auto& value : v)
   {
      ASSERT_EQ(15, value);
   }
}

TEST(grid, access_can_get)
{
   std::vector<std::vector<int>> vec {
      {1,2},
      {3,4,5}
   };
   
   ASSERT_EQ(4, mzlib::grid::access(vec, 1, 1));
}

TEST(grid, access_can_set)
{
   std::vector<std::vector<int>> vec {
      {1,2},
      {3,4,5}
   };
   
   mzlib::grid::access(vec, 1, 1) = 15;
   
   ASSERT_EQ(15, mzlib::grid::access(vec, 1, 1));
}

TEST(grid, access_get_uses_correct_order_of_coordinates)
{
   std::vector<std::vector<int>> vec {
      {1,2},
      {3,4,5}
   };

   ASSERT_EQ(3, mzlib::grid::access(vec, 0, 1));
}

TEST(grid, access_will_resize_if_needed)
{
   std::vector<std::vector<int>> vec {
      {1,2},
      {1,2,3}
   };

   // o -> exists
   // . -> doesn't
   // x -> requested

   // o o .    o o o o
   // o o o -> o o o o
   // . . .    o o o o
   // . . x    o o o o

   mzlib::grid::access(vec, 2, 3);
   
   ASSERT_EQ(4, vec.size());
   ASSERT_EQ(3, vec[0].size());
   ASSERT_EQ(3, vec[1].size());
   ASSERT_EQ(3, vec[2].size());
   ASSERT_EQ(3, vec[3].size());
}
