//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "greater_than.h"

TEST(greater_than, is_equal)
{
   ASSERT_FALSE(mzlib::greater_than(3)(3));
}

TEST(greater_than, is_more)
{
   ASSERT_TRUE(mzlib::greater_than(3)(5));
}

TEST(greater_than, is_less)
{
   ASSERT_FALSE(mzlib::greater_than(3)(2));
}
