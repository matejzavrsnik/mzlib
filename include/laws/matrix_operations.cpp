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

TEST(law_vector_operations, multiply) 
{
   mzlib::matrix<int,2,3> left = {1,2,3,4,5,6};
   mzlib::matrix<int,3,2> right = {7,8,9,10,11,12};
   mzlib::matrix<int,2,2> expected = {58,64,139,154};
   mzlib::matrix<int,2,2> actual = mzlib::law::matrix::multiply(left, right);
   ASSERT_EQ(expected, actual);
}
