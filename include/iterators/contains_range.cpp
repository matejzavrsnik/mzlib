//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "contains_range.h"
#include <vector>

TEST(contains_range, returns_first_iterator_to_start) 
{
   std::vector<int> full = {1,2,3,4,5,6,7,8,4,5,6,7,8,9};
   std::vector<int> sub = {4,5,6};
   auto where_sub_begins = full.begin()+3;
   
   const auto& result_it = mzlib::contains_range(
      full.begin(), full.end(),
      sub.begin(), sub.end());
   
   ASSERT_EQ(where_sub_begins, result_it);
}

TEST(contains_range, returns_end_iterator_if_range_not_found) 
{
   std::vector<int> full = {1,2,3,4,5,6,7,8,4,5,6,7,8,9};
   std::vector<int> sub = {10,11,12};
   
   const auto& result_it = mzlib::contains_range(
      full.begin(), full.end(),
      sub.begin(), sub.end());
   
   ASSERT_EQ(full.end(), result_it);
}

TEST(contains_range, works_if_range_different_type) 
{
   std::vector<int> full = {1,2,3,4,5,6,7,8,4,5,6,7,8,9};
   std::array<int, 3> sub = {10,11,12};
   
   const auto& result_it = mzlib::contains_range(
      full.begin(), full.end(),
      sub.begin(), sub.end());
   
   ASSERT_EQ(full.end(), result_it);
}