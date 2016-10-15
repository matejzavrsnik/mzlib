//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "../include/vector.h"
#include "gtest/gtest.h"
    
class fixture_cvector : public ::testing::Test 
{

protected:

   fixture_cvector() {}
   virtual ~fixture_cvector() {}
   virtual void SetUp() {}
   virtual void TearDown() {}

   mzlib::cvector<double, 3> v123{1.1,2.2,3.3};
   mzlib::cvector<double, 3> v456{4.4,5.5,6.6};
  
};

TEST_F(fixture_cvector, construction_default) 
{
   mzlib::cvector<double, 3> v;
   ASSERT_DOUBLE_EQ(0, v[0]);
   ASSERT_DOUBLE_EQ(0, v[1]);
   ASSERT_DOUBLE_EQ(0, v[2]);
}

TEST_F(fixture_cvector, construction_from_std_initializer_list) 
{
   mzlib::cvector<double, 3> v = {1,2,3};
   ASSERT_DOUBLE_EQ(1, v[0]);
   ASSERT_DOUBLE_EQ(2, v[1]);
   ASSERT_DOUBLE_EQ(3, v[2]);
}

TEST_F(fixture_cvector, construction_from_std_initializer_list_too_small) 
{
   mzlib::cvector<double, 4> v = {1,2};
   ASSERT_DOUBLE_EQ(1, v[0]);
   ASSERT_DOUBLE_EQ(2, v[1]);
   ASSERT_DOUBLE_EQ(0, v[2]);
   ASSERT_DOUBLE_EQ(0, v[3]);
}

TEST_F(fixture_cvector, construction_from_std_initializer_list_too_big) 
{
   mzlib::cvector<double, 3> v = {1,2,3,4,5,6};
   ASSERT_DOUBLE_EQ(1, v[0]);
   ASSERT_DOUBLE_EQ(2, v[1]);
   ASSERT_DOUBLE_EQ(3, v[2]);
}

TEST_F(fixture_cvector, construction_from_std_vector) 
{
   std::vector<double> standard_vector = {1,2,3};
   mzlib::cvector<double, 3> v = standard_vector;
   ASSERT_DOUBLE_EQ(1, v[0]);
   ASSERT_DOUBLE_EQ(2, v[1]);
   ASSERT_DOUBLE_EQ(3, v[2]);
}

TEST_F(fixture_cvector, construction_from_std_vector_too_small) 
{
   std::vector<double> standard_vector = {1,2};
   mzlib::cvector<double, 4> v = standard_vector;
   ASSERT_DOUBLE_EQ(1, v[0]);
   ASSERT_DOUBLE_EQ(2, v[1]);
   ASSERT_DOUBLE_EQ(0, v[2]);
   ASSERT_DOUBLE_EQ(0, v[3]);
}

TEST_F(fixture_cvector, construction_from_std_vector_too_big) 
{
   std::vector<double> standard_vector = {1,2,3,4,5,6};
   mzlib::cvector<double, 3> v = standard_vector;
   ASSERT_DOUBLE_EQ(1, v[0]);
   ASSERT_DOUBLE_EQ(2, v[1]);
   ASSERT_DOUBLE_EQ(3, v[2]);
}

TEST_F(fixture_cvector, assignment_from_std_initializer_list) 
{
   mzlib::cvector<double, 3> v = {9,9,9};
   v = {1,2,3};
   ASSERT_DOUBLE_EQ(1, v[0]);
   ASSERT_DOUBLE_EQ(2, v[1]);
   ASSERT_DOUBLE_EQ(3, v[2]);
}

TEST_F(fixture_cvector, assignment_from_std_initializer_list_too_small) 
{
   mzlib::cvector<double, 4> v = {9,9,9,9};
   v = {1,2};
   ASSERT_DOUBLE_EQ(1, v[0]);
   ASSERT_DOUBLE_EQ(2, v[1]);
   ASSERT_DOUBLE_EQ(9, v[2]);
   ASSERT_DOUBLE_EQ(9, v[3]);
}

TEST_F(fixture_cvector, assignment_from_std_initializer_list_too_big) 
{
   mzlib::cvector<double, 3> v = {9,9,9};
   v = {1,2,3,4,5,6};
   ASSERT_DOUBLE_EQ(1, v[0]);
   ASSERT_DOUBLE_EQ(2, v[1]);
   ASSERT_DOUBLE_EQ(3, v[2]);
}

TEST_F(fixture_cvector, assignment_from_std_vector) 
{
   mzlib::cvector<double, 3> v = {9,9,9};
   std::vector<double> standard_vector = {1,2,3};
   v = standard_vector;
   ASSERT_DOUBLE_EQ(1, v[0]);
   ASSERT_DOUBLE_EQ(2, v[1]);
   ASSERT_DOUBLE_EQ(3, v[2]);
}

TEST_F(fixture_cvector, assignment_from_std_vector_too_small) 
{
   mzlib::cvector<double, 4> v = {9,9,9,9};
   std::vector<double> standard_vector = {1,2};
   v = standard_vector;
   ASSERT_DOUBLE_EQ(1, v[0]);
   ASSERT_DOUBLE_EQ(2, v[1]);
   ASSERT_DOUBLE_EQ(9, v[2]);
   ASSERT_DOUBLE_EQ(9, v[3]);
}

TEST_F(fixture_cvector, assignment_from_std_vector_too_big) 
{
   mzlib::cvector<double, 3> v = {9,9,9};
   std::vector<double> standard_vector = {1,2,3,4,5,6};
   v = standard_vector;
   ASSERT_DOUBLE_EQ(1, v[0]);
   ASSERT_DOUBLE_EQ(2, v[1]);
   ASSERT_DOUBLE_EQ(3, v[2]);
}

TEST_F(fixture_cvector, move_by) 
{
   mzlib::cvector<double, 3> v_dest = v123.move_by(v456);
   ASSERT_DOUBLE_EQ(5.5, v_dest[0]);
   ASSERT_DOUBLE_EQ(7.7, v_dest[1]);
   ASSERT_DOUBLE_EQ(9.9, v_dest[2]);
}

TEST_F(fixture_cvector, square_distance_to) 
{
   double dist = v123.square_distance_to(v456);
   ASSERT_DOUBLE_EQ(32.67, dist);
}

TEST_F(fixture_cvector, distance_to) 
{
   double dist = v123.distance_to(v456);
   ASSERT_DOUBLE_EQ(5.715767664977295, dist);
}

TEST_F(fixture_cvector, length) 
{
   ASSERT_DOUBLE_EQ(9.6524608261313336, v456.length());
}

TEST_F(fixture_cvector, operator_equals) 
{
   mzlib::cvector<double, 3> v_equal{1.1,2.2,3.3};
   ASSERT_TRUE(v123 == v_equal);
}

TEST_F(fixture_cvector, normalise) 
{
   auto v = v456.normalise();
   ASSERT_DOUBLE_EQ(0.45584230583855184, v[0]);
   ASSERT_DOUBLE_EQ(0.56980288229818976, v[1]);
   ASSERT_DOUBLE_EQ(0.68376345875782774, v[2]);
}

TEST_F(fixture_cvector, operator_multiply) 
{   
   auto v = v123 * v456;
   ASSERT_DOUBLE_EQ(4.84, v[0]);
   ASSERT_DOUBLE_EQ(12.1, v[1]);
   ASSERT_DOUBLE_EQ(21.77999999999999, v[2]);
}

TEST_F(fixture_cvector, operator_multiply_with_scalar) 
{   
   auto v = v123 * 3.14;
   ASSERT_DOUBLE_EQ(3.454, v[0]);
   ASSERT_DOUBLE_EQ(6.908, v[1]);
   ASSERT_DOUBLE_EQ(10.362, v[2]);
}

TEST_F(fixture_cvector, operator_multiply_with_scalar_scalarfirst) 
{   
   auto v = 3.14 * v123;
   ASSERT_DOUBLE_EQ(3.454, v[0]);
   ASSERT_DOUBLE_EQ(6.908, v[1]);
   ASSERT_DOUBLE_EQ(10.362, v[2]);
}

TEST_F(fixture_cvector, operator_multiply_equals) 
{
   v123 *= v456;
   ASSERT_DOUBLE_EQ(4.84, v123[0]);
   ASSERT_DOUBLE_EQ(12.1, v123[1]);
   ASSERT_DOUBLE_EQ(21.77999999999999, v123[2]);
}

TEST_F(fixture_cvector, operator_multiply_equals_with_scalar) 
{
   // todo: do the other with scalar
   v123 *= 3.14;
   ASSERT_DOUBLE_EQ(3.454, v123[0]);
   ASSERT_DOUBLE_EQ(6.908, v123[1]);
   ASSERT_DOUBLE_EQ(10.362, v123[2]);
}

TEST_F(fixture_cvector, operator_divide) 
{   
   auto v = v123 / v456;
   ASSERT_DOUBLE_EQ(0.25, v[0]);
   ASSERT_DOUBLE_EQ(0.4, v[1]);
   ASSERT_DOUBLE_EQ(0.5, v[2]);
}

TEST_F(fixture_cvector, operator_divide_with_scalar) 
{   
   auto v = v123 / 3.14;
   ASSERT_DOUBLE_EQ(0.35031847133757965, v[0]);
   ASSERT_DOUBLE_EQ(0.7006369426751593, v[1]);
   ASSERT_DOUBLE_EQ(1.0509554140127388, v[2]);
}

TEST_F(fixture_cvector, operator_divide_with_scalar_scalarfirst) 
{   
   auto v = 3.14 / v123;
   ASSERT_DOUBLE_EQ(0.35031847133757965, v[0]);
   ASSERT_DOUBLE_EQ(0.7006369426751593, v[1]);
   ASSERT_DOUBLE_EQ(1.0509554140127388, v[2]);
}

TEST_F(fixture_cvector, operator_divide_equals) 
{
   v123 /= v456;
   ASSERT_DOUBLE_EQ(0.25, v123[0]);
   ASSERT_DOUBLE_EQ(0.4, v123[1]);
   ASSERT_DOUBLE_EQ(0.5, v123[2]);
}

TEST_F(fixture_cvector, operator_divide_equals_with_scalar) 
{
   v123 /= 3.14;
   ASSERT_DOUBLE_EQ(0.35031847133757965, v123[0]);
   ASSERT_DOUBLE_EQ(0.7006369426751593, v123[1]);
   ASSERT_DOUBLE_EQ(1.0509554140127388, v123[2]);
}

TEST_F(fixture_cvector, operator_plus) 
{   
   auto v = v123 + v456;
   ASSERT_DOUBLE_EQ(5.5, v[0]);
   ASSERT_DOUBLE_EQ(7.7, v[1]);
   ASSERT_DOUBLE_EQ(9.9, v[2]);
}

TEST_F(fixture_cvector, operator_plus_equals) 
{
   v123 += v456;
   ASSERT_DOUBLE_EQ(5.5, v123[0]);
   ASSERT_DOUBLE_EQ(7.7, v123[1]);
   ASSERT_DOUBLE_EQ(9.9, v123[2]);
}

TEST_F(fixture_cvector, operator_minus) 
{
   auto v = v456 - v123;
   ASSERT_DOUBLE_EQ(3.3, v[0]);
   ASSERT_DOUBLE_EQ(3.3, v[1]);
   ASSERT_DOUBLE_EQ(3.3, v[2]);
}

TEST_F(fixture_cvector, operator_minus_equals) 
{
   v456 -= v123;
   ASSERT_DOUBLE_EQ(3.3, v456[0]);
   ASSERT_DOUBLE_EQ(3.3, v456[1]);
   ASSERT_DOUBLE_EQ(3.3, v456[2]);
}

TEST_F(fixture_cvector, operator_minus_unary) 
{
   mzlib::cvector<double, 3> negative_v456{-4.4,-5.5,-6.6};
   ASSERT_TRUE(negative_v456 == -v456);
}
