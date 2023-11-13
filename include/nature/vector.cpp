//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "vector.h"
#include <unordered_set>

namespace mzlib {

class fixture_vector : public ::testing::Test 
{

protected:

   fixture_vector() {}
   virtual ~fixture_vector() {}
   virtual void SetUp() {}
   virtual void TearDown() {}

   mzlib::vector3d v123{1.1,2.2,3.3};
   mzlib::vector3d v456{4.4,5.5,6.6};
  
};

TEST_F(fixture_vector, construction_default) 
{
   mzlib::vector3d v;
   ASSERT_DOUBLE_EQ(0, v[0]);
   ASSERT_DOUBLE_EQ(0, v[1]);
   ASSERT_DOUBLE_EQ(0, v[2]);
}

TEST_F(fixture_vector, construction_from_std_initializer_list) 
{
   mzlib::vector3d v = {1,2,3};
   ASSERT_DOUBLE_EQ(1, v[0]);
   ASSERT_DOUBLE_EQ(2, v[1]);
   ASSERT_DOUBLE_EQ(3, v[2]);
}

TEST_F(fixture_vector, construction_from_std_initializer_list_too_small) 
{
   mzlib::vector<double, 4> v = {1,2};
   mzlib::vector<double, 4> expected = {1,2,0,0};
   ASSERT_EQ(expected, v);
}

TEST_F(fixture_vector, construction_from_std_initializer_list_too_big) 
{
   mzlib::vector3d v = {1,2,3,4,5,6};
   ASSERT_EQ(mzlib::vector3d({1,2,3}), v);
}

TEST_F(fixture_vector, construction_from_std_vector) 
{
   std::vector<double> standard_vector = {1,2,3};
   mzlib::vector3d v = standard_vector;
   ASSERT_EQ(mzlib::vector3d({1,2,3}), v);
}

TEST_F(fixture_vector, construction_from_std_vector_too_small) 
{
   std::vector<double> standard_vector = {1,2};
   mzlib::vector<double, 4> v = standard_vector;
   auto v_should_be = mzlib::vector<double, 4>({1,2,0,0});
   ASSERT_EQ(v_should_be, v);
}

TEST_F(fixture_vector, construction_from_std_vector_too_big) 
{
   std::vector<double> standard_vector = {1,2,3,4,5,6};
   mzlib::vector3d v = standard_vector;
   ASSERT_EQ(mzlib::vector3d({1,2,3}), v);
}

TEST_F(fixture_vector, assignment_from_std_initializer_list) 
{
   mzlib::vector3d v = {9,9,9};
   v = {1,2,3};
   ASSERT_EQ(mzlib::vector3d({1,2,3}), v);
}

TEST_F(fixture_vector, assignment_from_std_initializer_list_too_small) 
{
   mzlib::vector<double, 4> v = {9,9,9,9};
   mzlib::vector<double, 4> v_should_be = {1,2,9,9};
   v = {1,2};
   ASSERT_EQ(v_should_be, v);
}

TEST_F(fixture_vector, assignment_from_std_initializer_list_too_big) 
{
   mzlib::vector3d v = {9,9,9};
   v = {1,2,3,4,5,6};
   ASSERT_EQ(mzlib::vector3d({1,2,3}), v);
}

TEST_F(fixture_vector, assignment_from_std_vector) 
{
   mzlib::vector<int, 3> v = {9,9,9};
   std::vector<int> standard_vector = {1,2,3};
   v = standard_vector;
   
   mzlib::vector<int, 3> expected{1,2,3};
   ASSERT_EQ(expected, v);
}

TEST_F(fixture_vector, assignment_from_std_vector_too_small) 
{
   mzlib::vector<int, 4> v = {9,9,9,9};
   mzlib::vector<int, 4> v_should_be = {1,2,9,9};
   
   std::vector<int> standard_vector = {1,2};
   v = standard_vector;

   ASSERT_EQ(v_should_be, v);
}

TEST_F(fixture_vector, assignment_from_std_vector_too_big) 
{
   mzlib::vector<int, 3> v = {9,9,9};
   mzlib::vector<int, 3> v_should_be = {1,2,3};
   
   std::vector<int> standard_vector = {1,2,3,4,5,6};
   v = standard_vector;
   
   ASSERT_EQ(v_should_be, v);
}

TEST_F(fixture_vector, large_fits_on_stack)
{
   mzlib::vector<double, 1000000> large;
   ASSERT_TRUE(true);
}

TEST_F(fixture_vector, operator_equals) 
{
   ASSERT_TRUE(mzlib::vector3d({1.1,2.2,3.3}) == v123);
}

TEST_F(fixture_vector, operator_multiply) 
{   
   auto v = v123 * v456;
   ASSERT_EQ(mzlib::vector3d({4.84,12.1,21.77999999999999}), v);
}

TEST_F(fixture_vector, operator_multiply_with_scalar) 
{   
   auto v = v123 * 3.14;
   ASSERT_EQ(mzlib::vector3d({3.454,6.908,10.362}), v);
}

TEST_F(fixture_vector, operator_multiply_with_scalar_scalarfirst) 
{   
   auto v = 3.14 * v123;
   ASSERT_EQ(mzlib::vector3d({3.454,6.908,10.362}), v);
}

TEST_F(fixture_vector, operator_multiply_equals) 
{
   v123 *= v456;
   ASSERT_EQ(mzlib::vector3d({4.84,12.1,21.77999999999999}), v123);
}

TEST_F(fixture_vector, operator_multiply_equals_with_scalar) 
{
   // todo: do the other with scalar
   v123 *= 3.14;
   ASSERT_EQ(mzlib::vector3d({3.454,6.908,10.362}), v123);
}

TEST_F(fixture_vector, operator_divide) 
{   
   auto v = v123 / v456;
   ASSERT_EQ(mzlib::vector3d({0.25,0.4,0.5}), v);
}

TEST_F(fixture_vector, operator_divide_with_scalar) 
{   
   auto v = v123 / 3.14;
   ASSERT_EQ(mzlib::vector3d({0.35031847133757965,0.7006369426751593,1.0509554140127388}), v);
}

TEST_F(fixture_vector, operator_divide_with_scalar_scalarfirst) 
{   
   auto v = 3.14 / v123;
   ASSERT_EQ(mzlib::vector3d({0.35031847133757965,0.7006369426751593,1.0509554140127388}), v);
}

TEST_F(fixture_vector, operator_divide_equals) 
{
   v123 /= v456;
   ASSERT_EQ(mzlib::vector3d({0.25,0.4,0.5}), v123);
}

TEST_F(fixture_vector, operator_divide_equals_with_scalar) 
{
   v123 /= 3.14;
   ASSERT_EQ(mzlib::vector3d({0.35031847133757965,0.7006369426751593,1.0509554140127388}), v123);
}

TEST_F(fixture_vector, operator_plus) 
{   
   auto v = v123 + v456;
   ASSERT_EQ(mzlib::vector3d({5.5,7.7,9.9}), v);
}

TEST_F(fixture_vector, operator_plus_equals) 
{
   v123 += v456;
   ASSERT_EQ(mzlib::vector3d({5.5,7.7,9.9}), v123);
}

TEST_F(fixture_vector, operator_minus) 
{
   auto v = v456 - v123;
   ASSERT_EQ(mzlib::vector3d({3.3,3.3,3.3}), v);
}

TEST_F(fixture_vector, operator_minus_equals) 
{
   v456 -= v123;
   ASSERT_EQ(mzlib::vector3d({3.3,3.3,3.3}), v456);
}

TEST_F(fixture_vector, operator_minus_unary) 
{
   ASSERT_EQ(mzlib::vector3d({-4.4,-5.5,-6.6}), -v456);
}

TEST_F(fixture_vector, dimensions)
{
   ASSERT_EQ(2, (mzlib::vector<double, 2>::size()));
   ASSERT_EQ(3, (mzlib::vector<double, 3>::size()));
   ASSERT_EQ(4, (mzlib::vector<double, 4>::size()));
}

TEST_F(fixture_vector, can_store_it_in_set)
{
   std::set<mzlib::vector<int, 2>> s;

   for(int i=0; i<100; i++)
      for(int j=0; j<100; j++)
         s.insert({i,j});
   s.insert({1,1});

   ASSERT_EQ(10'000, s.size());
}

TEST_F(fixture_vector, can_store_in_unordered_set)
{
   std::unordered_set<mzlib::vector<int, 2>> s;

   for(int i=0; i<100; i++)
      for(int j=0; j<100; j++)
         s.insert({i,j});
   s.insert({1,1});

   ASSERT_EQ(10'000, s.size());
}

TEST_F(fixture_vector, can_use_as_key_in_map)
{
   mzlib::vector<int, 2> v1{0,0};
   mzlib::vector<int, 2> v2{0,1};
   mzlib::vector<int, 2> v3{0,1};
   std::map<mzlib::vector<int, 2>, std::string> m;
   m[v1] = "v1";
   m[v2] = "v2";
   m[v3] = "v3";
   ASSERT_EQ(2, m.size());
   ASSERT_EQ("v3", m[v2]);
}

} // namespace mzlib::vecns