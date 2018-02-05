//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "count_bits.h"

TEST(count_bits, long_0_bit_1)
{
   long n = 0;
   auto count = mzlib::count_bits(n, 1);
   ASSERT_EQ(0, count);
}

TEST(count_bits, long_1_bit_1)
{
   long n = 1;
   auto count = mzlib::count_bits(n, 1);
   ASSERT_EQ(1, count);
}

TEST(count_bits, long_2_bit_1)
{
   long n = 2;
   auto count = mzlib::count_bits(n, 1);
   ASSERT_EQ(1, count);
}

TEST(count_bits, long_3_bit_1)
{
   long n = 3;
   auto count = mzlib::count_bits(n, 1);
   ASSERT_EQ(2, count);
}

TEST(count_bits, long_max_bit_1)
{
   long n = std::numeric_limits<long>::max();
   auto count = mzlib::count_bits(n, 1);
   ASSERT_EQ(std::numeric_limits<long>::digits, count);
}

TEST(count_bits, long_0_bit_0)
{
   long n = 0;
   auto count = mzlib::count_bits(n, 0);
   ASSERT_EQ(std::numeric_limits<long>::digits, count);
}

TEST(count_bits, unsigned_long_max_bit_1)
{
   unsigned long n = std::numeric_limits<unsigned long>::max();
   auto count = mzlib::count_bits(n, 1);
   ASSERT_EQ(std::numeric_limits<unsigned long>::digits, count);
}

TEST(count_bits, unsigned_long_0_bit_0)
{
   unsigned long n = 0;
   auto count = mzlib::count_bits(n, 0);
   ASSERT_EQ(std::numeric_limits<unsigned long>::digits, count);
}

TEST(count_bits, not_integral)
{
   // auto count = mzlib::count_bits(0.12, 0);
   // should not even compile but how to test that?
}