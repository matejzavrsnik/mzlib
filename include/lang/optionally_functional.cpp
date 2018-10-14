//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "optionally_functional.h"

namespace
{
   using oi = std::optional<int>;
   using ob = std::optional<bool>;
}

// I MAY have gone a bit overboard with unit tests, but
// it's a nice lazy rainy day so why not?

TEST(optionally_functional, plus_normal) 
{
   oi a = 3;
   oi b = 4;
   oi c = mzlib::plus(a, b);
   ASSERT_TRUE(c.has_value());
   ASSERT_EQ(7, *c);
}

TEST(optionally_functional, plus_lhs_no_value) 
{
   oi a;
   oi b = 4;
   oi c = mzlib::plus(a, b);
   ASSERT_FALSE(c.has_value());
}

TEST(optionally_functional, plus_rhs_no_value) 
{
   oi a = 3;
   oi b;
   oi c = mzlib::plus(a, b);
   ASSERT_FALSE(c.has_value());
}

TEST(optionally_functional, plus_both_no_value) 
{
   oi a, b;
   oi c = mzlib::plus(a, b);
   ASSERT_FALSE(c.has_value());
}

TEST(optionally_functional, minus_normal) 
{
   oi a = 3;
   oi b = 4;
   oi c = mzlib::minus(a, b);
   ASSERT_TRUE(c.has_value());
   ASSERT_EQ(-1, *c);
}

TEST(optionally_functional, minus_lhs_no_value) 
{
   oi a;
   oi b = 4;
   oi c = mzlib::minus(a, b);
   ASSERT_FALSE(c.has_value());
}

TEST(optionally_functional, minus_rhs_no_value) 
{
   oi a = 3;
   oi b;
   oi c = mzlib::minus(a, b);
   ASSERT_FALSE(c.has_value());
}

TEST(optionally_functional, minus_both_no_value) 
{
   oi a, b;
   oi c = mzlib::minus(a, b);
   ASSERT_FALSE(c.has_value());
}

TEST(optionally_functional, multiplies_normal) 
{
   oi a = 3;
   oi b = 4;
   oi c = mzlib::multiplies(a, b);
   ASSERT_TRUE(c.has_value());
   ASSERT_EQ(12, *c);
}

TEST(optionally_functional, multiplies_lhs_no_value) 
{
   oi a;
   oi b = 4;
   oi c = mzlib::multiplies(a, b);
   ASSERT_FALSE(c.has_value());
}

TEST(optionally_functional, multiplies_rhs_no_value) 
{
   oi a = 3;
   oi b;
   oi c = mzlib::multiplies(a, b);
   ASSERT_FALSE(c.has_value());
}

TEST(optionally_functional, multiplies_both_no_value) 
{
   oi a, b;
   oi c = mzlib::multiplies(a, b);
   ASSERT_FALSE(c.has_value());
}

TEST(optionally_functional, divides_normal) 
{
   oi a = 8;
   oi b = 4;
   oi c = mzlib::divides(a, b);
   ASSERT_TRUE(c.has_value());
   ASSERT_EQ(2, *c);
}

TEST(optionally_functional, divides_lhs_no_value) 
{
   oi a;
   oi b = 4;
   oi c = mzlib::divides(a, b);
   ASSERT_FALSE(c.has_value());
}

TEST(optionally_functional, divides_rhs_no_value) 
{
   oi a = 3;
   oi b;
   oi c = mzlib::divides(a, b);
   ASSERT_FALSE(c.has_value());
}

TEST(optionally_functional, divides_both_no_value) 
{
   oi a, b;
   oi c = mzlib::divides(a, b);
   ASSERT_FALSE(c.has_value());
}

TEST(optionally_functional, modulus_normal) 
{
   oi a = 9;
   oi b = 4;
   oi c = mzlib::modulus(a, b);
   ASSERT_TRUE(c.has_value());
   ASSERT_EQ(1, *c);
}

TEST(optionally_functional, modulus_lhs_no_value) 
{
   oi a;
   oi b = 4;
   oi c = mzlib::modulus(a, b);
   ASSERT_FALSE(c.has_value());
}

TEST(optionally_functional, modulus_rhs_no_value) 
{
   oi a = 3;
   oi b;
   oi c = mzlib::modulus(a, b);
   ASSERT_FALSE(c.has_value());
}

TEST(optionally_functional, modulus_both_no_value) 
{
   oi a, b;
   oi c = mzlib::modulus(a, b);
   ASSERT_FALSE(c.has_value());
}

TEST(optionally_functional, negate_positive) 
{
   oi a = 9;
   oi c = mzlib::negate(a);
   ASSERT_TRUE(c.has_value());
   ASSERT_EQ(-9, *c);
}

TEST(optionally_functional, negate_negative) 
{
   oi a = -9;
   oi c = mzlib::negate(a);
   ASSERT_TRUE(c.has_value());
   ASSERT_EQ(9, *c);
}

TEST(optionally_functional, negate_no_value) 
{
   oi a;
   oi c = mzlib::negate(a);
   ASSERT_FALSE(c.has_value());
}

TEST(optionally_functional, equal_to_is) 
{
   oi a = 4;
   oi b = 4;
   ob c = mzlib::equal_to(a, b);
   ASSERT_TRUE(c.has_value());
   ASSERT_TRUE(*c);
}

TEST(optionally_functional, equal_to_isnt) 
{
   oi a = 3;
   oi b = 4;
   ob c = mzlib::equal_to(a, b);
   ASSERT_TRUE(c.has_value());
   ASSERT_FALSE(*c);
}

TEST(optionally_functional, equal_to_lhs_no_value) 
{
   oi a;
   oi b = 4;
   ob c = mzlib::equal_to(a, b);
   ASSERT_FALSE(c.has_value());
}

TEST(optionally_functional, equal_to_rhs_no_value) 
{
   oi a = 3;
   oi b;
   ob c = mzlib::equal_to(a, b);
   ASSERT_FALSE(c.has_value());
}

TEST(optionally_functional, equal_to_both_no_value) 
{
   oi a, b;
   ob c = mzlib::equal_to(a, b);
   ASSERT_FALSE(c.has_value());
}











TEST(optionally_functional, not_equal_to_is) 
{
   oi a = 3;
   oi b = 4;
   ob c = mzlib::not_equal_to(a, b);
   ASSERT_TRUE(c.has_value());
   ASSERT_TRUE(*c);
}

TEST(optionally_functional, not_equal_to_isnt) 
{
   oi a = 4;
   oi b = 4;
   ob c = mzlib::not_equal_to(a, b);
   ASSERT_TRUE(c.has_value());
   ASSERT_FALSE(*c);
}

TEST(optionally_functional, not_equal_to_lhs_no_value) 
{
   oi a;
   oi b = 4;
   ob c = mzlib::not_equal_to(a, b);
   ASSERT_FALSE(c.has_value());
}

TEST(optionally_functional, not_equal_to_rhs_no_value) 
{
   oi a = 3;
   oi b;
   ob c = mzlib::not_equal_to(a, b);
   ASSERT_FALSE(c.has_value());
}

TEST(optionally_functional, not_equal_to_both_no_value) 
{
   oi a, b;
   ob c = mzlib::not_equal_to(a, b);
   ASSERT_FALSE(c.has_value());
}









TEST(optionally_functional, greater_is) 
{
   oi a = 5;
   oi b = 4;
   ob c = mzlib::greater(a, b);
   ASSERT_TRUE(c.has_value());
   ASSERT_TRUE(*c);
}

TEST(optionally_functional, greater_isnt) 
{
   oi a = 4;
   oi b = 4;
   ob c = mzlib::greater(a, b);
   ASSERT_TRUE(c.has_value());
   ASSERT_FALSE(*c);
}

TEST(optionally_functional, greater_lhs_no_value) 
{
   oi a;
   oi b = 4;
   ob c = mzlib::greater(a, b);
   ASSERT_FALSE(c.has_value());
}

TEST(optionally_functional, greater_rhs_no_value) 
{
   oi a = 3;
   oi b;
   ob c = mzlib::greater(a, b);
   ASSERT_FALSE(c.has_value());
}

TEST(optionally_functional, greater_both_no_value) 
{
   oi a, b;
   ob c = mzlib::greater(a, b);
   ASSERT_FALSE(c.has_value());
}












TEST(optionally_functional, less_is) 
{
   oi a = 3;
   oi b = 4;
   ob c = mzlib::less(a, b);
   ASSERT_TRUE(c.has_value());
   ASSERT_TRUE(*c);
}

TEST(optionally_functional, less_isnt) 
{
   oi a = 4;
   oi b = 4;
   ob c = mzlib::less(a, b);
   ASSERT_TRUE(c.has_value());
   ASSERT_FALSE(*c);
}

TEST(optionally_functional, less_lhs_no_value) 
{
   oi a;
   oi b = 4;
   ob c = mzlib::less(a, b);
   ASSERT_FALSE(c.has_value());
}

TEST(optionally_functional, less_rhs_no_value) 
{
   oi a = 3;
   oi b;
   ob c = mzlib::less(a, b);
   ASSERT_FALSE(c.has_value());
}

TEST(optionally_functional, less_both_no_value) 
{
   oi a, b;
   ob c = mzlib::less(a, b);
   ASSERT_FALSE(c.has_value());
}









TEST(optionally_functional, greater_equal_greater) 
{
   oi a = 5;
   oi b = 4;
   ob c = mzlib::greater_equal(a, b);
   ASSERT_TRUE(c.has_value());
   ASSERT_TRUE(*c);
}

TEST(optionally_functional, greater_equal_equal) 
{
   oi a = 4;
   oi b = 4;
   ob c = mzlib::greater_equal(a, b);
   ASSERT_TRUE(c.has_value());
   ASSERT_TRUE(*c);
}

TEST(optionally_functional, greater_equal_less) 
{
   oi a = 3;
   oi b = 4;
   ob c = mzlib::greater_equal(a, b);
   ASSERT_TRUE(c.has_value());
   ASSERT_FALSE(*c);
}

TEST(optionally_functional, greater_equal_lhs_no_value) 
{
   oi a;
   oi b = 4;
   ob c = mzlib::greater_equal(a, b);
   ASSERT_FALSE(c.has_value());
}

TEST(optionally_functional, greater_equal_rhs_no_value) 
{
   oi a = 3;
   oi b;
   ob c = mzlib::greater_equal(a, b);
   ASSERT_FALSE(c.has_value());
}

TEST(optionally_functional, greater_equal_both_no_value) 
{
   oi a, b;
   ob c = mzlib::greater_equal(a, b);
   ASSERT_FALSE(c.has_value());
}









TEST(optionally_functional, less_equal_greater) 
{
   oi a = 5;
   oi b = 4;
   ob c = mzlib::less_equal(a, b);
   ASSERT_TRUE(c.has_value());
   ASSERT_FALSE(*c);
}

TEST(optionally_functional, less_equal_equal) 
{
   oi a = 4;
   oi b = 4;
   ob c = mzlib::less_equal(a, b);
   ASSERT_TRUE(c.has_value());
   ASSERT_TRUE(*c);
}

TEST(optionally_functional, less_equal_less) 
{
   oi a = 3;
   oi b = 4;
   ob c = mzlib::less_equal(a, b);
   ASSERT_TRUE(c.has_value());
   ASSERT_TRUE(*c);
}

TEST(optionally_functional, less_equal_lhs_no_value) 
{
   oi a;
   oi b = 4;
   ob c = mzlib::less_equal(a, b);
   ASSERT_FALSE(c.has_value());
}

TEST(optionally_functional, less_equal_rhs_no_value) 
{
   oi a = 3;
   oi b;
   ob c = mzlib::less_equal(a, b);
   ASSERT_FALSE(c.has_value());
}

TEST(optionally_functional, less_equal_both_no_value) 
{
   oi a, b;
   ob c = mzlib::less_equal(a, b);
   ASSERT_FALSE(c.has_value());
}