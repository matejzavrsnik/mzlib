//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "fast_min.h"

TEST(fast_min, basic_lvalue) 
{
   int i1 = 1, i2 = 2, i3 = 3;
   // all permutations
   ASSERT_EQ(1, mzlib::fast_min_ref(i1, i2, i3));
   ASSERT_EQ(1, mzlib::fast_min_ref(i1, i3, i2));
   ASSERT_EQ(1, mzlib::fast_min_ref(i2, i1, i3));
   ASSERT_EQ(1, mzlib::fast_min_ref(i2, i3, i1));
   ASSERT_EQ(1, mzlib::fast_min_ref(i3, i1, i2));
   ASSERT_EQ(1, mzlib::fast_min_ref(i3, i2, i1));
}

TEST(lvalue, basic_rvalue) 
{
   // all permutations
   ASSERT_EQ(1, mzlib::fast_min(1, 2, 3));
   ASSERT_EQ(1, mzlib::fast_min(1, 3, 2));
   ASSERT_EQ(1, mzlib::fast_min(2, 1, 3));
   ASSERT_EQ(1, mzlib::fast_min(2, 3, 1));
   ASSERT_EQ(1, mzlib::fast_min(3, 1, 2));
   ASSERT_EQ(1, mzlib::fast_min(3, 2, 1));
}