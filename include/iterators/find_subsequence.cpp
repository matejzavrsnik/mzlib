//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "find_subsequence.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace ::testing;

TEST(find_subsequence, demo) 
{
   std::vector<int> full = {1,2,3,4,5,6,1,2,3,4,7,8,9};
   //            repeated:  _______     _______
   auto range_begin = full.begin(); // from 1
   auto range_end = full.begin()+4; // to 4
   
   auto repetitions = mzlib::find_subsequence(
      full.begin(), full.end(),
      range_begin, range_end);
   
   ASSERT_THAT(repetitions, UnorderedElementsAre(
      full.begin(),
      full.begin()+6));
}

TEST(find_subsequence, when_last_repeat_ends_at_the_end) 
{
   std::vector<int> full = {1,2,7,8,9,6,1,2,3,4,7,8,9};
   auto range_begin = full.begin()+2;
   auto range_end = full.begin()+5;
   
   auto repetitions = mzlib::find_subsequence(
      full.begin(), full.end(),
      range_begin, range_end);
   
   ASSERT_THAT(repetitions, UnorderedElementsAre(
      full.begin()+2,
      full.begin()+10));
}
