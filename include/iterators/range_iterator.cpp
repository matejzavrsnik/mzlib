//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "range_iterator.h"
#include <vector>

TEST(range_iterator, first)
{
   std::vector<int> v = {1,2,3,4};
   mzlib::range_iterator rit(v.begin(), v.end(), 2);
   mzlib::range r = rit.first();
   ASSERT_EQ(v.begin(), r.begin());
   ASSERT_EQ(v.begin()+3, r.end());
}

TEST(range_iterator, next_same_size)
{
   std::vector<int> v = {1,2,3,4};
   mzlib::range assumed_current(v.begin()+1, v.begin()+2);
   
   mzlib::range_iterator rit(v.begin(), v.end(), 2);
   auto next = rit.next(assumed_current);
   
   ASSERT_EQ(assumed_current.begin()+1, next.begin());
   ASSERT_EQ(assumed_current.end()+1, next.end());
}

TEST(range_iterator, next_transition_to_lower_size)
{
   std::vector<int> v = {1,2,3,4};
   mzlib::range assumed_current(v.begin()+1, v.end());
   
   mzlib::range_iterator rit(v.begin(), v.end(), 2);
   auto next = rit.next(assumed_current);
   
   ASSERT_EQ(v.begin(), next.begin());
   ASSERT_EQ(v.begin()+2, next.end());
}

TEST(range_iterator, end_isnt_because_in_the_middle)
{
   std::vector<int> v = {1,2,3,4,5};
   mzlib::range assumed_current(v.begin()+1, v.begin()+3);
   
   mzlib::range_iterator rit(v.begin(), v.end(), 2);
   
   ASSERT_FALSE(rit.end(assumed_current));
}

TEST(range_iterator, end_isnt_because_not_yet_min_range_size)
{
   std::vector<int> v = {1,2,3,4};
   mzlib::range assumed_current(v.begin()+1, v.end());
   
   mzlib::range_iterator rit(v.begin(), v.end(), 2);
   
   ASSERT_FALSE(rit.end(assumed_current));
}

TEST(range_iterator, end_isnt_the_last_one_still_counts)
{
   std::vector<int> v = {1,2,3,4};
   
   mzlib::range assumed_current(
      v.begin()+2, v.end());
   
   mzlib::range_iterator rit(v.begin(), v.end(), 2);
   
   ASSERT_FALSE(rit.end(assumed_current));
}

TEST(range_iterator, complete_run)
{
   std::vector<int> v = {1,2,3,4,5};
   mzlib::range_iterator rit(v.begin(), v.end(), 2);
   auto v1 = v.begin();
   auto v2 = v.begin()+1;
   auto v3 = v.begin()+2;
   auto v4 = v.begin()+3;
   auto v5 = v.begin()+4;
   auto v_end = v.end();
   
   using range_type = mzlib::range<std::vector<int>::iterator>;
   std::vector<range_type> ranges;
   for (auto r = rit.first(); !rit.end(r); r = rit.next(r)) {
      ranges.push_back(r);
   }
   
   ASSERT_EQ(9, ranges.size());
   
   // 2 x range size 4
   ASSERT_EQ(ranges[0].begin(), v1);
   ASSERT_EQ(ranges[0].end(), v5);
   
   ASSERT_EQ(ranges[1].begin(), v2);
   ASSERT_EQ(ranges[1].end(), v_end);
   
   // 3 x range size 3
   ASSERT_EQ(ranges[2].begin(), v1);
   ASSERT_EQ(ranges[2].end(), v4);
   
   ASSERT_EQ(ranges[3].begin(), v2);
   ASSERT_EQ(ranges[3].end(), v5);
   
   ASSERT_EQ(ranges[4].begin(), v3);
   ASSERT_EQ(ranges[4].end(), v_end);
   
   // 5 x range size 2
   ASSERT_EQ(ranges[5].begin(), v1);
   ASSERT_EQ(ranges[5].end(), v3);
   
   ASSERT_EQ(ranges[6].begin(), v2);
   ASSERT_EQ(ranges[6].end(), v4);
   
   ASSERT_EQ(ranges[7].begin(), v3);
   ASSERT_EQ(ranges[7].end(), v5);
   
   ASSERT_EQ(ranges[8].begin(), v4);
   ASSERT_EQ(ranges[8].end(), v_end);
}