//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_VECTOR_H
#define MZLIB_VECTOR_H

#include <vector> // for conversion from std::vector
#include <initializer_list>
#include <array>
#include <ostream>

#include "../lang/dbl.h"
#include "../laws/vector_operations.h"
#include "../tools/copy_iterators.h"

namespace mzlib {

// Fixed size mathematical vector.
   
// Motivation to write own class (goals):
//   - boost::ublas::c_vector can't be constexpr
//   - std::vector is dynamic and can't fail compilation if used with mixed dimensions
//   - I couldn't find a way to construct and fill std::array in constexpr context.
//     For example: something like std::array({1,1,1,1}) but templetised for any array size.
//   - and to have specific type against which to overload operators

// Should I implement base vector class and use that one in physical laws instead of
// concrete template instantiations? No, laws should work with any vector type. I am
// not building another framework. If laws are function templates, that is perfect.
   
template<class TypeT, size_t DimT>
class vector
{

private:

   std::array<TypeT, DimT> m_array;
   
public:
   
   vector (const vector<TypeT,DimT>&) = default;
   vector (vector<TypeT,DimT> &&) = default;
   vector& operator= (const vector<TypeT,DimT>&) = default;
   vector& operator= (vector<TypeT,DimT>&&) = default;
   ~vector () = default;

   constexpr vector () : 
      m_array{0} // all will be zero
   {
   };
   
   // implicit conversion from std::initializer_list
   constexpr vector (const std::initializer_list<TypeT>& list) : 
      m_array{0}
   {
      copy(list.begin(), list.end(), m_array.begin(), m_array.end());
   }
    
   // implicit conversion from std::vector
   constexpr vector (const std::vector<TypeT>& vec)
   {
      copy(vec.begin(), vec.end(), m_array.begin(), m_array.end());
   }
    
   constexpr vector<TypeT,DimT>& operator= (const std::vector<TypeT>& vec) 
   {    
      copy(vec.begin(), vec.end(), m_array.begin(), m_array.end());
      return *this;
   }
    
   constexpr vector<TypeT,DimT>& operator= (const std::initializer_list<TypeT>& list) 
   { 
      copy(list.begin(), list.end(), m_array.begin(), m_array.end());
      return *this;
   }
        
   constexpr TypeT& operator[] (size_t n) 
   { 
      return m_array[n]; 
   }
    
   constexpr const TypeT& operator[] (size_t n) const 
   { 
      return m_array[n];
   }
    
   constexpr static size_t size()
   {
      return DimT;
   }
  
};

template<typename T, size_t D> 
constexpr bool operator== (const mzlib::vector<T,D>& a, const vector<T,D>& b)
{
    return law::vector::equals(a, b);
}

template<typename T, size_t D> 
constexpr bool operator!= (const mzlib::vector<T,D>& a, const vector<T,D>& b)
{
   return !law::vector::equals(a, b);
}

template<typename T, size_t D> 
constexpr vector<T,D> operator+ (const mzlib::vector<T,D>& a, const vector<T,D>& b)
{  
   return law::vector::add(a, b);
}

template<typename T, size_t D>
constexpr vector<T,D>& operator+= (mzlib::vector<T,D>& a, const vector<T,D>& b) 
{
   return a = law::vector::add(a, b);
}

template<typename T, size_t D> 
constexpr vector<T,D> operator- (const mzlib::vector<T,D>& a, const vector<T,D>& b)
{
   return law::vector::subtract(a, b);
}

template<typename T, size_t D> 
constexpr vector<T,D>& operator-= (mzlib::vector<T,D>& a, const vector<T,D>& b) 
{
   return a = law::vector::subtract(a, b);
}

template<typename T, size_t D> 
constexpr vector<T, D> operator- (const mzlib::vector<T,D>& v)
{
   return law::vector::flip(v);
}

template<typename T, size_t D> 
constexpr mzlib::vector<T,D> operator* (const mzlib::vector<T,D>& a, const mzlib::vector<T,D>& b)
{  
   return law::vector::multiply_by_vector(a, b);
}

template<typename T, size_t D> 
constexpr mzlib::vector<T,D>& operator*= (mzlib::vector<T,D>& a, const mzlib::vector<T,D>& b) 
{
   return a = law::vector::multiply_by_vector(a, b);
}

template<typename T, typename S, size_t D> 
constexpr mzlib::vector<T,D> operator* (const mzlib::vector<T,D>& vec, const S& scalar)
{  
   return law::vector::multiply_by_scalar(vec, scalar);
}

template<typename T, typename S, size_t D> 
constexpr mzlib::vector<T,D>& operator*= (mzlib::vector<T,D>& vec, const S& scalar) 
{
   return vec = law::vector::multiply_by_scalar(vec, scalar); 
}

template<typename T, typename S, size_t D> 
constexpr mzlib::vector<T,D> operator* (const S& scalar, const mzlib::vector<T,D>& vec)
{
   return law::vector::multiply_by_scalar(vec, scalar);
}

template<typename T, size_t D> 
constexpr mzlib::vector<T,D> operator/ (const mzlib::vector<T,D>& a, const mzlib::vector<T,D>& b)
{  
   return law::vector::divide_by_vector(a, b);
}

template<typename T, size_t D> 
constexpr mzlib::vector<T,D>& operator/= (mzlib::vector<T,D>& a, const mzlib::vector<T,D>& b) 
{
   return a = law::vector::divide_by_vector(a, b);
}

template<typename T, typename S, size_t D> 
constexpr mzlib::vector<T,D> operator/ (const mzlib::vector<T,D>& vec, const S& scalar)
{  
   return law::vector::divide_by_scalar(vec, scalar);
}

template<typename T, typename S, size_t D> 
constexpr mzlib::vector<T,D>& operator/= (mzlib::vector<T,D>& vec, const S& scalar) 
{
   return vec = law::vector::divide_by_scalar(vec, scalar); 
}

template<typename T, typename S, size_t D> 
constexpr mzlib::vector<T,D> operator/ (const S& scalar, const mzlib::vector<T,D>& vec)
{
   return law::vector::divide_by_scalar(vec, scalar); 
}
   
// Convenient types

using vector2d = vector<double, 2>;
using vector3d = vector<double, 3>;
using point2d  = vector<double, 2>;
using point3d  = vector<double, 3>;

// convenient values

constexpr vector2d unit_vector2d = law::vector::create_unit_vector<vector2d>();
constexpr vector3d unit_vector3d = law::vector::create_unit_vector<vector3d>();

} // namespace

template<class TYPE, size_t DIM>
constexpr std::ostream& operator<< (std::ostream& os, const mzlib::vector<TYPE,DIM>& vector)
{
   os << "[";
   for (size_t i=0; i<vector.size(); ++i) {
      if (i!=0) os << ",";
      os << vector[i];
   }
   os << "]";
   return os;
}

#endif // MZLIB_VECTOR_H

#ifdef MZLIB_BUILDING_TESTS

#ifndef MZLIB_VECTOR_TESTS_H
#define MZLIB_VECTOR_TESTS_H

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

} // namespace mzlib::vecns

#endif // MZLIB_VECTOR_TESTS_H

#endif // MZLIB_BUILDING_TESTS
