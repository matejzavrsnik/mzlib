//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "parity.h"

TEST(parity, is_even) 
{
   ASSERT_TRUE (mzlib::is_even(0));
   ASSERT_FALSE(mzlib::is_even(1));
   ASSERT_TRUE (mzlib::is_even(2));
   ASSERT_TRUE (mzlib::is_even(4));
   ASSERT_FALSE(mzlib::is_even(-1));
   ASSERT_TRUE (mzlib::is_even(-2));
}

TEST(parity, is_odd) 
{
   ASSERT_FALSE(mzlib::is_odd(0));
   ASSERT_TRUE (mzlib::is_odd(1));
   ASSERT_FALSE(mzlib::is_odd(2));
   ASSERT_TRUE (mzlib::is_odd(3));
   ASSERT_FALSE(mzlib::is_odd(4));
   ASSERT_TRUE (mzlib::is_odd(-1));
   ASSERT_FALSE(mzlib::is_odd(-2));
}