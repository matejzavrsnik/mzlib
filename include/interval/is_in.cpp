//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "is_in.h"
#include <gtest/gtest.h>

TEST(is_in, value_in_single_interval_cases)
{
   ASSERT_FALSE(mzlib::interval::is_in(std::pair{2, 4}, 1));
   ASSERT_TRUE(mzlib::interval::is_in(std::pair{2, 4}, 2));
   ASSERT_TRUE(mzlib::interval::is_in(std::pair{2, 4}, 3));
   ASSERT_TRUE(mzlib::interval::is_in(std::pair{2, 4}, 4));
   ASSERT_FALSE(mzlib::interval::is_in(std::pair{2, 4}, 5));
}

TEST(is_in, value_in_single_interval_cases_orientation)
{
   ASSERT_FALSE(mzlib::interval::is_in(std::pair{4, 2}, 1));
   ASSERT_TRUE(mzlib::interval::is_in(std::pair{4, 2}, 2));
   ASSERT_TRUE(mzlib::interval::is_in(std::pair{4, 2}, 3));
   ASSERT_TRUE(mzlib::interval::is_in(std::pair{4, 2}, 4));
   ASSERT_FALSE(mzlib::interval::is_in(std::pair{4, 2}, 5));
}

TEST(is_in, value_in_many_intervals_cases)
{
   auto intervals = std::vector{
      std::pair{2,4},
      std::pair{6,8},
      std::pair{12,10}
   };

   ASSERT_FALSE(mzlib::interval::is_in(intervals, 1));
   ASSERT_TRUE(mzlib::interval::is_in(intervals, 2));
   ASSERT_TRUE(mzlib::interval::is_in(intervals, 3));
   ASSERT_TRUE(mzlib::interval::is_in(intervals, 4));
   ASSERT_FALSE(mzlib::interval::is_in(intervals, 5));
   ASSERT_TRUE(mzlib::interval::is_in(intervals, 6));
   ASSERT_TRUE(mzlib::interval::is_in(intervals, 7));
   ASSERT_TRUE(mzlib::interval::is_in(intervals, 8));
   ASSERT_FALSE(mzlib::interval::is_in(intervals, 9));
   ASSERT_TRUE(mzlib::interval::is_in(intervals, 10));
   ASSERT_TRUE(mzlib::interval::is_in(intervals, 11));
   ASSERT_TRUE(mzlib::interval::is_in(intervals, 12));
   ASSERT_FALSE(mzlib::interval::is_in(intervals, 13));
}

TEST(is_in, value_in_many_intervals_cases_orientation)
{
   auto intervals = std::vector{
      std::pair{4,2},
      std::pair{8,6},
      std::pair{10,12}
   };

   ASSERT_FALSE(mzlib::interval::is_in(intervals, 1));
   ASSERT_TRUE(mzlib::interval::is_in(intervals, 2));
   ASSERT_TRUE(mzlib::interval::is_in(intervals, 3));
   ASSERT_TRUE(mzlib::interval::is_in(intervals, 4));
   ASSERT_FALSE(mzlib::interval::is_in(intervals, 5));
   ASSERT_TRUE(mzlib::interval::is_in(intervals, 6));
   ASSERT_TRUE(mzlib::interval::is_in(intervals, 7));
   ASSERT_TRUE(mzlib::interval::is_in(intervals, 8));
   ASSERT_FALSE(mzlib::interval::is_in(intervals, 9));
   ASSERT_TRUE(mzlib::interval::is_in(intervals, 10));
   ASSERT_TRUE(mzlib::interval::is_in(intervals, 11));
   ASSERT_TRUE(mzlib::interval::is_in(intervals, 12));
   ASSERT_FALSE(mzlib::interval::is_in(intervals, 13));
}

TEST(is_in, interval_in_single_interval_cases)
{
   ASSERT_TRUE(mzlib::interval::is_in(std::pair{2, 3}, std::pair{1, 4}));
   ASSERT_TRUE(mzlib::interval::is_in(std::pair{3, 2}, std::pair{4, 1}));
   ASSERT_TRUE(mzlib::interval::is_in(std::pair{1, 3}, std::pair{1, 4}));
   ASSERT_TRUE(mzlib::interval::is_in(std::pair{2, 4}, std::pair{1, 4}));
   ASSERT_TRUE(mzlib::interval::is_in(std::pair{1, 4}, std::pair{1, 4}));
   ASSERT_TRUE(mzlib::interval::is_in(std::pair{1, 1}, std::pair{1, 4}));
   ASSERT_TRUE(mzlib::interval::is_in(std::pair{4, 4}, std::pair{1, 4}));

   ASSERT_FALSE(mzlib::interval::is_in(std::pair{1, 3}, std::pair{4, 6}));
   ASSERT_FALSE(mzlib::interval::is_in(std::pair{3, 1}, std::pair{6, 4}));
   ASSERT_FALSE(mzlib::interval::is_in(std::pair{1, 4}, std::pair{4, 6}));
   ASSERT_FALSE(mzlib::interval::is_in(std::pair{1, 5}, std::pair{4, 6}));
   ASSERT_FALSE(mzlib::interval::is_in(std::pair{5, 8}, std::pair{4, 6}));
   ASSERT_FALSE(mzlib::interval::is_in(std::pair{6, 8}, std::pair{4, 6}));
   ASSERT_FALSE(mzlib::interval::is_in(std::pair{7, 8}, std::pair{4, 6}));
}