//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "fast_forward.h"

TEST(fast_forward, demo)
{
   std::vector<int> v = {1,2,3,4,5,6,7,8,9};
   
   using namespace std::placeholders;
   
   auto result_f = mzlib::fast_forward<int>(
      v.begin(), v.end(), 
      std::bind(std::greater<int>(), _1, 5));
   ASSERT_EQ(6, *result_f);
   
   auto result_b = mzlib::fast_forward<int>(
      v.rbegin(), v.rend(), 
      std::bind(std::less<int>(), _1, 5));
   ASSERT_EQ(4, *result_b);
}