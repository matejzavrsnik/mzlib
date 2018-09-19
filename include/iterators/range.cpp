//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "range.h"
#include <vector>

TEST(range, distance)
{
   std::vector<int> v = {1,2,3,4,5,6,7};
   using it = std::vector<int>::iterator;
   
   auto range_begin = v.begin()+1; // at 2
   auto range_end = v.begin()+3; // at 4
   
   mzlib::range<it> r(range_begin, range_end);
   
   auto std_distance = std::distance(range_begin, range_end);
   auto range_distance = r.distance();
   
   ASSERT_EQ(std_distance, range_distance);
}

TEST(range, advance)
{
   std::vector<int> v = {1,2,3,4,5,6,7};
   using it = std::vector<int>::iterator;
   
   auto range_begin = v.begin()+1; // at 2
   auto range_end = v.begin()+3; // at 4
   
   mzlib::range<it> r(range_begin, range_end);
   r.advance(1);
   
   ASSERT_EQ(++range_begin, r.begin());
   ASSERT_EQ(++range_end, r.end());
}

TEST(range, advance_preserves_distance)
{
   std::vector<int> v = {1,2,3,4,5,6,7};
   using it = std::vector<int>::iterator;
   
   auto range_begin = v.begin()+1; // at 2
   auto range_end = v.begin()+3; // at 4
   
   mzlib::range<it> r(range_begin, range_end);
   auto distance_before = r.distance();
   
   r.advance(1);
   
   auto distance_after = r.distance();
   
   ASSERT_EQ(distance_before, distance_after);
}