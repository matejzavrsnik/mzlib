//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "copy_first_n_over_rest.h"

TEST(copy_first_n_over_rest, demo) 
{
   std::vector<int> v       {1,2,3, 4,5,6, 7,8,9, 10};
   std::vector<int> expected{1,2,3, 1,2,3, 1,2,3, 1};
   
   mzlib::copy_first_n_over_rest(v, 3);
   
   ASSERT_EQ(expected, v);
}