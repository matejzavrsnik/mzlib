//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "matrix_operations.h"

#include "../nature/matrix.h"

TEST(law_matrix_operations, equals) 
{
   auto one = mzlib::matrix2x2({1,2,3,4});
   auto same = mzlib::matrix2x2({1,2,3,4});
   auto different = mzlib::matrix2x2({1,2,3,3});
   ASSERT_TRUE(mzlib::law::matrix::equals(one, same));
   ASSERT_FALSE(mzlib::law::matrix::equals(one, different));
}

TEST(law_matrix_operations, add) 
{
   mzlib::matrix<int,2,3> left = {1,2,3,4,5,6};
   mzlib::matrix<int,2,3> right = {7,8,9,10,11,12};
   mzlib::matrix<int,2,3> expected = {8,10,12,14,16,18};
   mzlib::matrix<int,2,3> actual = 
      mzlib::law::matrix::add(left, right);
   ASSERT_EQ(expected, actual);
}

TEST(law_matrix_operations, subtract) 
{
   mzlib::matrix<int,2,3> left = {7,8,9,10,11,12};
   mzlib::matrix<int,2,3> right = {1,2,3,4,5,6};
   mzlib::matrix<int,2,3> expected = {6,6,6,6,6,6};
   mzlib::matrix<int,2,3> actual = 
      mzlib::law::matrix::subtract(left, right);
   ASSERT_EQ(expected, actual);
}

TEST(law_matrix_operations, multiply) 
{
   mzlib::matrix<int,2,3> left = {1,2,3,4,5,6};
   mzlib::matrix<int,3,2> right = {7,8,9,10,11,12};
   mzlib::matrix<int,2,2> expected = {58,64,139,154};
   mzlib::matrix<int,2,2> actual = 
      mzlib::law::matrix::multiply(left, right);
   ASSERT_EQ(expected, actual);
}

TEST(law_matrix_operations, scalar_multiply) 
{
   mzlib::matrix<int,2,3> m = {1,2,3,4,5,6};
   mzlib::matrix<int,2,3> expected = {2,4,6,8,10,12};
   mzlib::matrix<int,2,3> actual = 
      mzlib::law::matrix::scalar_multiply(m, 2);
   ASSERT_EQ(expected, actual);
}

TEST(law_matrix_operations, negate) 
{
   mzlib::matrix<int,2,3> m = {1,2,3,4,5,6};
   mzlib::matrix<int,2,3> expected = {-1,-2,-3,-4,-5,-6};
   mzlib::matrix<int,2,3> actual = 
      mzlib::law::matrix::negate(m);
   ASSERT_EQ(expected, actual);
}

TEST(law_matrix_operations, transpose) 
{
   mzlib::matrix<int,2,4> m = {1,2,3,4,5,6,7,8};
   mzlib::matrix<int,4,2> expected = {1,5,2,6,3,7,4,8};
   mzlib::matrix<int,4,2> actual = 
      mzlib::law::matrix::transpose(m);
   ASSERT_EQ(expected, actual);
}

TEST(law_matrix_operations, random_matrix) 
{
   mzlib::matrix<int,4,4> im;
   mzlib::law::matrix::randomise(im);
   
   mzlib::matrix<double,5,4> dm;
   mzlib::law::matrix::randomise(dm);

   mzlib::matrix<char,4,5> cm;
   mzlib::law::matrix::randomise(cm);
   
   ASSERT_TRUE(true);
}
