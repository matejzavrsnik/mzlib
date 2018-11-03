//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "nested_vector.h"

#include "gtest/gtest.h"

using namespace ::testing;

TEST(nested_vector, enlarge_works)
{
   std::vector<std::vector<int>> vec {
      {1,2},
      {1,2,3}
   };
   
   // o o      o o o o
   // o o o -> o o o o
   //          o o o o
   
   mzlib::nested_vector::enlarge(vec, 3, 4);
   
   ASSERT_EQ(3, vec.size());
   ASSERT_EQ(4, vec[0].size());
   ASSERT_EQ(4, vec[1].size());
   ASSERT_EQ(4, vec[2].size());
}

TEST(nested_vector, enlarge_keeps_values)
{
   std::vector<std::vector<int>> vec {
      {1,2},
      {3,4,5}
   };
   
   // 1 2      1 2 o o
   // 1 2 3 -> 1 2 3 o
   //          o o o o
   
   mzlib::nested_vector::enlarge(vec, 3, 4);
   
   ASSERT_EQ(1, vec[0][0]);
   ASSERT_EQ(2, vec[0][1]);
   
   ASSERT_EQ(3, vec[1][0]);
   ASSERT_EQ(4, vec[1][1]);
   ASSERT_EQ(5, vec[1][2]);
}

TEST(nested_vector, construct_works)
{
   std::vector<std::vector<int>> vec =
      mzlib::nested_vector::construct(3, 4, 15);
   
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

TEST(nested_vector, access_can_get)
{
   std::vector<std::vector<int>> vec {
      {1,2},
      {3,4,5}
   };
   
   ASSERT_EQ(4, mzlib::nested_vector::access(vec, 1, 1));
}

TEST(nested_vector, access_can_set)
{
   std::vector<std::vector<int>> vec {
      {1,2},
      {3,4,5}
   };
   
   mzlib::nested_vector::access(vec, 1, 1) = 15;
   
   ASSERT_EQ(15, mzlib::nested_vector::access(vec, 1, 1));
}

TEST(nested_vector, access_will_resize_if_needed)
{
   std::vector<std::vector<int>> vec {
      {1,2},
      {1,2,3}
   };
   
   // o o      o o o o
   // o o o -> o o o o
   //          o o o o
   
   mzlib::nested_vector::access(vec, 2, 3);
   
   ASSERT_EQ(3, vec.size());
   ASSERT_EQ(4, vec[0].size());
   ASSERT_EQ(4, vec[1].size());
   ASSERT_EQ(4, vec[2].size());
}
