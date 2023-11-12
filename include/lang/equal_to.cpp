//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "equal_to.h"

TEST(equal_to, two_equal_integers)
{
   ASSERT_TRUE(mzlib::equal_to(3)(3));
}

TEST(equal_to, two_unequal_integers)
{
   ASSERT_FALSE(mzlib::equal_to(3)(5));
}

TEST(equal_to, two_equal_strings)
{
   auto s1 = std::string("foundation");
   auto s2 = std::string("foundation");
   ASSERT_TRUE(mzlib::equal_to(s1)(s2));
}

TEST(equal_to, two_unequal_strings)
{
   auto s1 = std::string("foundation");
   auto s2 = std::string("second foundation");
   ASSERT_FALSE(mzlib::equal_to(s1)(s2));
}
