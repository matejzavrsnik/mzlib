//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "get_extremes.h"
#include <gtest/gtest.h>

TEST(get_extremes, basic)
{
   std::vector<std::pair<int, int>> intervals = {
      {1,3},
      {2,4}
   };
   ASSERT_EQ(std::pair(1,4), mzlib::interval::get_extremes(intervals));
}

TEST(get_extremes, no_intervals)
{
   std::vector<std::pair<int, int>> intervals = {
   };
   ASSERT_THROW(mzlib::interval::get_extremes(intervals), mzlib::exception::is_empty);

}

TEST(get_extremes, one_interval)
{
   std::vector<std::pair<int, int>> intervals = {
      {1,3}
   };
   ASSERT_EQ(std::pair(1,3), mzlib::interval::get_extremes(intervals));
}

TEST(get_extremes, many_intervals)
{
   std::vector<std::pair<int, int>> intervals = {
      {1,3},
      {2,4},
      {3,5},
      {4,6},
      {5,7},
      {6,8}
   };
   ASSERT_EQ(std::pair(1,8), mzlib::interval::get_extremes(intervals));
}

TEST(get_extremes, intervals_oriented_opposite)
{
   std::vector<std::pair<int, int>> intervals = {
      {3,1},
      {4,2}
   };
   ASSERT_EQ(std::pair(1,4), mzlib::interval::get_extremes(intervals));
}