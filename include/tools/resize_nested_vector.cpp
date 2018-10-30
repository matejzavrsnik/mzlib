//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "resize_nested_vector.h"

TEST(resize, demo_resized)
{
   std::vector<std::vector<int>> vec {
      {1,2},
      {1,2,3}
   };
   
   // o o      o o o o
   // o o o -> o o o o
   //          o o o o
   
   mzlib::resize_nested_vector(vec, 3, 4);
   
   ASSERT_EQ(3, vec.size());
   ASSERT_EQ(4, vec[0].size());
   ASSERT_EQ(4, vec[1].size());
   ASSERT_EQ(4, vec[2].size());
}

TEST(resize, demo_keeps_value)
{
   std::vector<std::vector<int>> vec {
      {1,2},
      {3,4,5}
   };
   
   // 1 2      1 2 o o
   // 1 2 3 -> 1 2 3 o
   //          o o o o
   
   mzlib::resize_nested_vector(vec, 3, 4);
   
   ASSERT_EQ(1, vec[0][0]);
   ASSERT_EQ(2, vec[0][1]);
   
   ASSERT_EQ(3, vec[1][0]);
   ASSERT_EQ(4, vec[1][1]);
   ASSERT_EQ(5, vec[1][2]);
}