//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "less_than.h"

TEST(less_than, is_equal)
{
   ASSERT_FALSE(mzlib::less_than(3)(3));
}

TEST(less_than, is_more)
{
   ASSERT_FALSE(mzlib::less_than(3)(5));
}

TEST(less_than, is_less)
{
   ASSERT_TRUE(mzlib::less_than(3)(2));
}
