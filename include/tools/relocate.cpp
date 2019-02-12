//
// Copyright (c) 2019 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "relocate.h"

TEST(relocate, demo) 
{
   std::vector<int> a{1,2,3,4,5,6};
   std::vector<int> b{1,2,3};
   
   mzlib::relocate(4, a, b);
   
   std::vector<int> new_a{1,2,3,5,6};
   std::vector<int> new_b{1,2,3,4};
   
   ASSERT_EQ(a, new_a);
   ASSERT_EQ(b, new_b);
}