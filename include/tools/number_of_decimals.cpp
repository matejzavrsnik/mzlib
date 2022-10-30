//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "number_of_decimals.h"

TEST(get_number_of_decimals, basic) 
{
   double double_num = 0;
   ASSERT_EQ(0, mzlib::get_number_of_decimals(double_num));
   double_num = 1;
   ASSERT_EQ(0, mzlib::get_number_of_decimals(double_num));
   double_num = 0.111;
   ASSERT_EQ(3, mzlib::get_number_of_decimals(double_num));
   double_num = 0.11100;
   ASSERT_EQ(3, mzlib::get_number_of_decimals(double_num));
   double_num = 0.111001;
   ASSERT_EQ(6, mzlib::get_number_of_decimals(double_num));
}