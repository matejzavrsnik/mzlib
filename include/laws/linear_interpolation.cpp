//
// Copyright (c) 2019 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "linear_interpolation.h"

TEST(linear_interpolation, middle_simple) 
{
   double y = mzlib::law::linear_interpolation({1,1}, {3,3}, 2);
   ASSERT_DOUBLE_EQ(2, y);
}

TEST(linear_interpolation, middle_type_double) 
{
   double y = mzlib::law::linear_interpolation({1.1,1.1}, {3.3,3.3}, 2.2);
   ASSERT_DOUBLE_EQ(2.2, y);
}

TEST(linear_interpolation, middle_not_square) 
{
   double y = mzlib::law::linear_interpolation({1,2}, {4,3}, 2.5);
   ASSERT_DOUBLE_EQ(2.5, y);
}

TEST(linear_interpolation, middle_not_same_x_y)
{
   double y = mzlib::law::linear_interpolation({1,1}, {4,2}, 2.5);
   ASSERT_DOUBLE_EQ(1.5, y);
}

TEST(linear_interpolation, left_simple) 
{
   double y = mzlib::law::linear_interpolation({1,1}, {3,3}, 0);
   ASSERT_DOUBLE_EQ(0, y);
}

TEST(linear_interpolation, left_type_double) 
{
   double y = mzlib::law::linear_interpolation({1.1,1.1}, {3.3,3.3}, 0.1);
   ASSERT_NEAR(0.1, y, 0.000000001); // 0.1 is problematic in double
}

TEST(linear_interpolation, left_not_square) 
{
   double y = mzlib::law::linear_interpolation({1,2}, {4,3}, 0.5);
   ASSERT_DOUBLE_EQ(1+5.0/6.0, y);
}

TEST(linear_interpolation, left_not_same_x_y)
{
   double y = mzlib::law::linear_interpolation({1,1}, {4,2}, 0.5);
   ASSERT_DOUBLE_EQ(5.0/6.0, y);
}

TEST(linear_interpolation, right_simple) 
{
   double y = mzlib::law::linear_interpolation({1,1}, {3,3}, 4);
   ASSERT_DOUBLE_EQ(4, y);
}

TEST(linear_interpolation, right_type_double) 
{
   double y = mzlib::law::linear_interpolation({1.1,1.1}, {3.3,3.3}, 4.4);
   ASSERT_DOUBLE_EQ(4.4, y);
}

TEST(linear_interpolation, right_not_square) 
{
   double y = mzlib::law::linear_interpolation({1,2}, {4,3}, 4.5);
   ASSERT_DOUBLE_EQ(3+1.0/6.0, y);
}

TEST(linear_interpolation, right_not_same_x_y)
{
   double y = mzlib::law::linear_interpolation({1,1}, {4,2}, 4.5);
   ASSERT_DOUBLE_EQ(2+1.0/6.0, y);
}

TEST(linear_interpolation, x_exactly_like_first_point_x)
{
   double y = mzlib::law::linear_interpolation({1.1,2.2}, {3.3,4.4}, 1.1);
   ASSERT_DOUBLE_EQ(2.2, y);
}

TEST(linear_interpolation, x_exactly_like_second_point_x)
{
   double y = mzlib::law::linear_interpolation({1.1,2.2}, {3.3,4.4}, 3.3);
   ASSERT_DOUBLE_EQ(4.4, y);
}