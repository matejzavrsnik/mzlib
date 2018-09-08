//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "matrix.h"

namespace mzlib {

class fixture_matrix : public ::testing::Test 
{

protected:

   fixture_matrix() {}
   virtual ~fixture_matrix() {}
   virtual void SetUp() {}
   virtual void TearDown() {}
  
};

TEST_F(fixture_matrix, construction_default) 
{
   mzlib::matrix3x3 m;
   ASSERT_DOUBLE_EQ(0, m(0,0));
   ASSERT_DOUBLE_EQ(0, m(0,1));
   ASSERT_DOUBLE_EQ(0, m(0,2));
   ASSERT_DOUBLE_EQ(0, m(1,0));
   ASSERT_DOUBLE_EQ(0, m(1,1));
   ASSERT_DOUBLE_EQ(0, m(1,2));
   ASSERT_DOUBLE_EQ(0, m(2,0));
   ASSERT_DOUBLE_EQ(0, m(2,1));
   ASSERT_DOUBLE_EQ(0, m(2,2));
}

TEST_F(fixture_matrix, construction_from_std_initializer_list) 
{
   mzlib::matrix3x3 m = {1,2,3,4,5,6,7,8,9};
   ASSERT_DOUBLE_EQ(1, m(0,0));
   ASSERT_DOUBLE_EQ(2, m(0,1));
   ASSERT_DOUBLE_EQ(3, m(0,2));
   ASSERT_DOUBLE_EQ(4, m(1,0));
   ASSERT_DOUBLE_EQ(5, m(1,1));
   ASSERT_DOUBLE_EQ(6, m(1,2));
   ASSERT_DOUBLE_EQ(7, m(2,0));
   ASSERT_DOUBLE_EQ(8, m(2,1));
   ASSERT_DOUBLE_EQ(9, m(2,2));
}

TEST_F(fixture_matrix, construction_from_std_initializer_list_too_small) 
{
   mzlib::matrix3x3 m = {1,2,3};
   mzlib::matrix3x3 expected = {1,2,3,0,0,0,0,0,0};
   ASSERT_EQ(expected, m);
}

TEST_F(fixture_matrix, construction_from_std_initializer_list_too_big) 
{
   mzlib::matrix2x2 m = {1,2,3,4,5,6};
   ASSERT_EQ(mzlib::matrix2x2({1,2,3,4}), m);
}

TEST_F(fixture_matrix, construction_from_std_vector) 
{
   std::vector<double> standard_vector = {1,2,3,4};
   mzlib::matrix2x2 m = standard_vector;
   ASSERT_EQ(mzlib::matrix2x2({1,2,3,4}), m);
}

TEST_F(fixture_matrix, construction_from_std_vector_too_small) 
{
   std::vector<double> standard_vector = {1,2,3};
   mzlib::matrix2x2 m = standard_vector;
   ASSERT_EQ(mzlib::matrix2x2({1,2,3,0}), m);
}

TEST_F(fixture_matrix, construction_from_std_vector_too_big) 
{
   std::vector<double> standard_vector = {1,2,3,4,5};
   mzlib::matrix2x2 m = standard_vector;
   ASSERT_EQ(mzlib::matrix2x2({1,2,3,4}), m);
}

TEST_F(fixture_matrix, operator_equals) 
{
   ASSERT_TRUE(
      mzlib::matrix2x2({1.1,2.2,3.3,4.4}) == 
      mzlib::matrix2x2({1.1,2.2,3.3,4.4}));
}

TEST_F(fixture_matrix, operator_multiply) 
{   
   mzlib::matrix<int,2,3> left = {1,2,3,4,5,6};
   mzlib::matrix<int,3,2> right = {7,8,9,10,11,12};
   mzlib::matrix<int,2,2> expected = {58,64,139,154};
   mzlib::matrix<int,2,2> actual = left * right;
   ASSERT_EQ(expected, actual);
}

}