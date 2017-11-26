//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_COUNT_BITS_H
#define MZLIB_COUNT_BITS_H

#include <limits>
#include <type_traits>

namespace mzlib {

template <class T>
unsigned int count_bits(T n, short bit,
   typename std::enable_if_t<std::is_integral<T>::value>* = 0)
{
   // corner case
   if(bit==0 && n==0)
      return std::numeric_limits<T>::digits;
   
   unsigned int count = 0;
   while (n)
   {
      count += (n & bit);
      n >>= 1;
   }
   return count;
}

} // namespace

#endif // MZLIB_COUNT_BITS_H

#ifdef MZLIB_COUNT_BITS_TESTS_H
#undef MZLIB_COUNT_BITS_TESTS_H

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

#endif // MZLIB_COUNT_BITS_TESTS_H
