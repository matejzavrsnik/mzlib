//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "conditional_find.h"

TEST(last_where_value_larger_then_given, basic)
{
   std::vector<int> v = {1,2,3,4,5};
   
   auto res = mzlib::last_where_value_larger_then_given(v.begin(), v.end(), 3);
   ASSERT_EQ(*res, 5);
}

TEST(last_where_value_larger_then_given, empty)
{
   std::vector<int> v = {};
   
   auto res = mzlib::last_where_value_larger_then_given(v.begin(), v.end(), 3);
   ASSERT_EQ(res, v.end());
}

TEST(last_where_value_larger_then_given, one_is_larger)
{
   std::vector<int> v = {5};
   
   auto res = mzlib::last_where_value_larger_then_given(v.begin(), v.end(), 3);
   ASSERT_EQ(*res, 5);
}

TEST(last_where_value_larger_then_given, one_is_smaller)
{
   std::vector<int> v = {2};
   
   auto res = mzlib::last_where_value_larger_then_given(v.begin(), v.end(), 3);
   ASSERT_EQ(res, v.end());
}

TEST(last_where_value_smaller_then_next, basic)
{
   std::vector<int> v = {1,4,6,1,2,3};
   // Smaller then nexts ^ ^   ^ ^ 
   
   auto res = mzlib::last_where_value_smaller_then_next(v.begin(), v.end());
   ASSERT_EQ(*res, 2);
}

TEST(last_where_value_smaller_then_next, empty)
{
   std::vector<int> v = {};
   
   auto res = mzlib::last_where_value_smaller_then_next(v.begin(), v.end());
   ASSERT_EQ(res, v.end());
}

TEST(last_where_value_smaller_then_next, one)
{
   std::vector<int> v = {1};
   
   auto res = mzlib::last_where_value_smaller_then_next(v.begin(), v.end());
   ASSERT_EQ(res, v.end());
}

TEST(last_where_value_smaller_then_next, two_equals)
{
   std::vector<int> v = {1,1};
   
   auto res = mzlib::last_where_value_smaller_then_next(v.begin(), v.end());
   ASSERT_EQ(res, v.end());
}

TEST(last_where_value_smaller_then_next, two)
{
   std::vector<int> v = {1,2};
   
   auto res = mzlib::last_where_value_smaller_then_next(v.begin(), v.end());
   ASSERT_EQ(*res, 1);
}