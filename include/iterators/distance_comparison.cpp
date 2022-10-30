//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "distance_comparison.h"

TEST(is_distance_larger, basic)
{
   std::vector<int> v = {1,2,3,4,5};
   
   ASSERT_FALSE(mzlib::is_distance_larger(v.begin(), v.begin(), 2));
   ASSERT_FALSE(mzlib::is_distance_larger(v.begin(), v.begin()+1, 2));
   ASSERT_FALSE(mzlib::is_distance_larger(v.begin(), v.begin()+2, 2));
   ASSERT_TRUE (mzlib::is_distance_larger(v.begin(), v.begin()+3, 2));
}

TEST(is_distance_smaller, basic)
{
   std::vector<int> v = {1,2,3,4,5};
   
   ASSERT_TRUE (mzlib::is_distance_smaller(v.begin(), v.begin(), 2));
   ASSERT_TRUE (mzlib::is_distance_smaller(v.begin(), v.begin()+1, 2));
   ASSERT_FALSE(mzlib::is_distance_smaller(v.begin(), v.begin()+2, 2));
   ASSERT_FALSE(mzlib::is_distance_smaller(v.begin(), v.begin()+3, 2));
}

TEST(is_distance_equal, basic)
{
   std::vector<int> v = {1,2,3,4,5};
   
   ASSERT_FALSE(mzlib::is_distance_equal(v.begin(), v.begin(), 2));
   ASSERT_FALSE(mzlib::is_distance_equal(v.begin(), v.begin()+1, 2));
   ASSERT_TRUE (mzlib::is_distance_equal(v.begin(), v.begin()+2, 2));
   ASSERT_FALSE(mzlib::is_distance_equal(v.begin(), v.begin()+3, 2));
}