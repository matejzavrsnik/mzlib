//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_VECTOR_H
#define MZLIB_VECTOR_H

#include <vector> // for conversion from std::vector
#include <cmath> // std::pow, std::sqrt
#include <initializer_list>
#include <array>
#include <ostream>

#include "../lang/dbl.h"

namespace mzlib {

// Fixed size mathematical vector.
// Motivation to write own class (goals):
//   - boost::ublas::c_vector can't be constexpr and std::vector isn't mathematical
//   - std::vector is dynamic and can't fail compilation if used with mixed dimensions

// Should I implement base vector class and use that one in physical laws instead of
// concrete template instantiations? No, laws should work with any vector type. I am
// not building another framework. If laws are function templates, that is perfect.
   
template<class TYPE, size_t DIM>
class vector 
{

private:

   std::array<TYPE, DIM> m_array;

public:
   
   // This weird constructor uses variadic templates to try to squeeze anything into a vector
   template <typename... T> constexpr explicit vector (T... val) : 
      m_array{val...}
   {
   }
    
   constexpr vector () : 
      m_array{0} // the rest will be zero too
   {
   };
   
   vector (const vector<TYPE,DIM>&) = default;
   vector (vector<TYPE,DIM> &&) = default;
   vector& operator= (const vector<TYPE,DIM>&) = default;
   vector& operator= (vector<TYPE,DIM>&&) = default;
   ~vector () = default;
    
   vector (const std::initializer_list<TYPE>& list) : 
      m_array{0}
   {
      size_t min_dim = std::min(DIM, list.size());
      size_t i = 0;
      for (auto list_it = list.begin(); i<min_dim; ++i, ++list_it) {
         m_array[i] = *list_it;
      }
   }
    
   // implicit conversion from std::vector
   vector (const std::vector<TYPE>& vec) : 
      m_array{0}
   {
      size_t min_dim = std::min(DIM, vec.size());
      for (size_t i = 0; i<min_dim; ++i) {
         m_array[i] = vec[i];
      }
   }
    
   vector<TYPE,DIM>& operator= (const std::vector<TYPE>& vec) 
   {    
      size_t min_dim = std::min(DIM, vec.size());
      for (size_t i = 0; i<min_dim; ++i) {
         m_array[i] = vec[i];
      }
      return *this;
   }
    
   vector<TYPE,DIM>& operator= (const std::initializer_list<TYPE>& list) 
   { 
      size_t min_dim = std::min(DIM, list.size());
      size_t i = 0;
      for (auto list_it = list.begin(); i<min_dim; ++i, ++list_it) {
         m_array[i] = *list_it;
      }
      return *this;
   }
        
   constexpr TYPE& operator[] (size_t n) 
   { 
      return m_array[n]; 
   }
    
   constexpr const TYPE& operator[] (size_t n) const 
   { 
      return m_array[n];
   }
    
   constexpr static size_t size()
   {
      return DIM;
   }
  
};

namespace vec_op { // rename to simply vector if I chose to abolish vector class at some point

template<class VectorT> 
constexpr size_t rank (const VectorT& v)
{
   return v.size();
}
    
template<class VectorT> 
constexpr VectorT move_by (const VectorT& from, const VectorT& by)
{
   VectorT result(from);
   for (size_t i = 0; i<rank(from); ++i) 
      result[i] += by[i];
   return std::move(result);
}
    
template<class VectorT> 
constexpr auto sqr_distance(const VectorT& from, const VectorT& to)
-> decltype(std::pow(from[0], 2)) // limited to return type of std::pow
{
   decltype(std::pow(from[0], 2)) sqrdist = 0;
   for (size_t i = 0; i<rank(from); ++i)
      sqrdist += std::pow( from[i]-to[i], 2);
   return sqrdist;
}

template<class VectorT> 
constexpr auto distance (const VectorT& from, const VectorT& to)
-> decltype(sqr_distance(from, to))
{
   return std::sqrt( sqr_distance(from, to) );
}

template<class VectorT>
constexpr VectorT direction(const VectorT& from, const VectorT& to)
{
   return std::move(from - to);
}

template<class VectorT> 
constexpr auto length (const VectorT& v)
-> decltype(std::pow(v[0], 2)) // limited to return type of std::pow
{
   decltype(std::pow(v[0], 2)) l = 0;
   for (size_t i=0; i<rank(v); ++i)
      l += std::pow(v[i], 2);
   return std::sqrt(l);
}

template<class VectorT> 
constexpr VectorT normalise (const VectorT& v)
{
   auto l = length(v);
   VectorT result(v);
   for (size_t i=0; i<rank(v); ++i)
      result[i] /= l;
   return std::move(result);
}

template<class VectorT> 
constexpr VectorT create_unit_vector()
{
   VectorT v;
   for (size_t i = 0; i<rank(v); ++i) 
       v[i] = 1;
   return normalise(v);
}

template<class VectorT> 
constexpr bool equals(const VectorT& a, const VectorT& b)
{
   if (std::is_integral<decltype(a[0])>::value) {
      for (size_t i = 0; i<rank(a); ++i) 
         if (a[i] != b[i])
            return false;
   }
   else {
      for (size_t i = 0; i<rank(a); ++i)
         if (!dbl(a[i]).equals(b[i]))
            return false;
   }
   return true;
}

template<class VectorT> 
constexpr VectorT add (const VectorT& a, const VectorT& b)
{  
   VectorT result(a);
   for (size_t i = 0; i<rank(a); ++i)
      result[i] += b[i];
   return std::move(result); 
}

template<class VectorT> 
constexpr VectorT subtract (const VectorT& a, const VectorT& b)
{  
   VectorT result(a);
   for (size_t i = 0; i<rank(a); ++i)
      result[i] -= b[i];
   return std::move(result); 
}

template<class VectorT> 
constexpr VectorT multiply_by_vector (const VectorT& a, const VectorT& b)
{  
   VectorT result(a);
   for (size_t i = 0; i<rank(a); ++i)
      result[i] *= b[i];
   return std::move(result); 
}

template<class VectorT, class ScalarT> 
constexpr VectorT multiply_by_scalar (const VectorT& a, const ScalarT& b)
{  
   VectorT result(a);
   for (size_t i = 0; i<rank(a); ++i)
      result[i] *= b;
   return std::move(result); 
}

template<class VectorT> 
constexpr VectorT divide_by_vector (const VectorT& a, const VectorT& b)
{  
   VectorT result(a);
   for (size_t i = 0; i<rank(a); ++i)
      result[i] /= b[i];
   return std::move(result); 
}

template<class VectorT, class ScalarT> 
constexpr VectorT divide_by_scalar (const VectorT& a, const ScalarT& b)
{  
   VectorT result(a);
   for (size_t i = 0; i<rank(a); ++i)
      result[i] /= b;
   return std::move(result); 
}

template<class VectorT> 
constexpr VectorT flip (const VectorT& v)
{  
   VectorT result(v);
   for (size_t i = 0; i<rank(v); ++i)
      result[i] *= -1;
   return std::move(result); 
}

} // namespace vec_op

template<typename T, size_t D> 
constexpr bool operator== (const mzlib::vector<T,D>& a, const vector<T,D>& b)
{
    return vec_op::equals(a, b);
}

template<typename T, size_t D> 
constexpr bool operator!= (const mzlib::vector<T,D>& a, const vector<T,D>& b)
{
   return !vec_op::equals(a, b);
}

template<typename T, size_t D> 
constexpr vector<T,D> operator+ (const mzlib::vector<T,D>& a, const vector<T,D>& b)
{  
   return vec_op::add(a, b);
}

template<typename T, size_t D>
constexpr vector<T,D>& operator+= (mzlib::vector<T,D>& a, const vector<T,D>& b) 
{
   return a = vec_op::add(a, b);
}

template<typename T, size_t D> 
constexpr vector<T,D> operator- (const mzlib::vector<T,D>& a, const vector<T,D>& b)
{
   return vec_op::subtract(a, b);
}

template<typename T, size_t D> 
constexpr vector<T,D>& operator-= (mzlib::vector<T,D>& a, const vector<T,D>& b) 
{
   return a = vec_op::subtract(a, b);
}

template<typename T, size_t D> 
constexpr vector<T, D> operator- (const mzlib::vector<T,D>& v)
{
   return vec_op::flip(v);
}

template<typename T, size_t D> 
constexpr mzlib::vector<T,D> operator* (const mzlib::vector<T,D>& a, const mzlib::vector<T,D>& b)
{  
   return vec_op::multiply_by_vector(a, b);
}

template<typename T, size_t D> 
constexpr mzlib::vector<T,D>& operator*= (mzlib::vector<T,D>& a, const mzlib::vector<T,D>& b) 
{
   return a = vec_op::multiply_by_vector(a, b);
}

template<typename T, typename S, size_t D> 
constexpr mzlib::vector<T,D> operator* (const mzlib::vector<T,D>& vec, const S& scalar)
{  
   return vec_op::multiply_by_scalar(vec, scalar);
}

template<typename T, typename S, size_t D> 
constexpr mzlib::vector<T,D>& operator*= (mzlib::vector<T,D>& vec, const S& scalar) 
{
   return vec = vec_op::multiply_by_scalar(vec, scalar); 
}

template<typename T, typename S, size_t D> 
constexpr mzlib::vector<T,D> operator* (const S& scalar, const mzlib::vector<T,D>& vec)
{
   return vec_op::multiply_by_scalar(vec, scalar);
}

template<typename T, size_t D> 
constexpr mzlib::vector<T,D> operator/ (const mzlib::vector<T,D>& a, const mzlib::vector<T,D>& b)
{  
   return vec_op::divide_by_vector(a, b);
}

template<typename T, size_t D> 
constexpr mzlib::vector<T,D>& operator/= (mzlib::vector<T,D>& a, const mzlib::vector<T,D>& b) 
{
   return a = vec_op::divide_by_vector(a, b);
}

template<typename T, typename S, size_t D> 
constexpr mzlib::vector<T,D> operator/ (const mzlib::vector<T,D>& vec, const S& scalar)
{  
   return vec_op::divide_by_scalar(vec, scalar);
}

template<typename T, typename S, size_t D> 
constexpr mzlib::vector<T,D>& operator/= (mzlib::vector<T,D>& vec, const S& scalar) 
{
   return vec = vec_op::divide_by_scalar(vec, scalar); 
}

template<typename T, typename S, size_t D> 
constexpr mzlib::vector<T,D> operator/ (const S& scalar, const mzlib::vector<T,D>& vec)
{
   return vec_op::divide_by_scalar(vec, scalar); 
}

// Convenient types

using vector2d = vector<double, 2>;
using vector3d = vector<double, 3>;
using point2d  = vector<double, 2>;
using point3d  = vector<double, 3>;

// convenient values

constexpr vector2d unit_vector2d = vec_op::create_unit_vector<vector2d>();
constexpr vector3d unit_vector3d = vec_op::create_unit_vector<vector3d>();

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

   mzlib::vector<double, 3> v123{1.1,2.2,3.3};
   mzlib::vector<double, 3> v456{4.4,5.5,6.6};
  
};

TEST_F(fixture_vector, construction_default) 
{
   mzlib::vector<double, 3> v;
   ASSERT_DOUBLE_EQ(0, v[0]);
   ASSERT_DOUBLE_EQ(0, v[1]);
   ASSERT_DOUBLE_EQ(0, v[2]);
}

TEST_F(fixture_vector, construction_from_std_initializer_list) 
{
   mzlib::vector<double, 3> v = {1,2,3};
   ASSERT_DOUBLE_EQ(1, v[0]);
   ASSERT_DOUBLE_EQ(2, v[1]);
   ASSERT_DOUBLE_EQ(3, v[2]);
}

TEST_F(fixture_vector, construction_from_std_initializer_list_too_small) 
{
   mzlib::vector<double, 4> v = {1,2};
   ASSERT_DOUBLE_EQ(1, v[0]);
   ASSERT_DOUBLE_EQ(2, v[1]);
   ASSERT_DOUBLE_EQ(0, v[2]);
   ASSERT_DOUBLE_EQ(0, v[3]);
}

TEST_F(fixture_vector, construction_from_std_initializer_list_too_big) 
{
   mzlib::vector<double, 3> v = {1,2,3,4,5,6};
   ASSERT_DOUBLE_EQ(1, v[0]);
   ASSERT_DOUBLE_EQ(2, v[1]);
   ASSERT_DOUBLE_EQ(3, v[2]);
}

TEST_F(fixture_vector, construction_from_std_vector) 
{
   std::vector<double> standard_vector = {1,2,3};
   mzlib::vector<double, 3> v = standard_vector;
   ASSERT_DOUBLE_EQ(1, v[0]);
   ASSERT_DOUBLE_EQ(2, v[1]);
   ASSERT_DOUBLE_EQ(3, v[2]);
}

TEST_F(fixture_vector, construction_from_std_vector_too_small) 
{
   std::vector<double> standard_vector = {1,2};
   mzlib::vector<double, 4> v = standard_vector;
   ASSERT_DOUBLE_EQ(1, v[0]);
   ASSERT_DOUBLE_EQ(2, v[1]);
   ASSERT_DOUBLE_EQ(0, v[2]);
   ASSERT_DOUBLE_EQ(0, v[3]);
}

TEST_F(fixture_vector, construction_from_std_vector_too_big) 
{
   std::vector<double> standard_vector = {1,2,3,4,5,6};
   mzlib::vector<double, 3> v = standard_vector;
   ASSERT_DOUBLE_EQ(1, v[0]);
   ASSERT_DOUBLE_EQ(2, v[1]);
   ASSERT_DOUBLE_EQ(3, v[2]);
}

TEST_F(fixture_vector, assignment_from_std_initializer_list) 
{
   mzlib::vector<double, 3> v = {9,9,9};
   v = {1,2,3};
   ASSERT_DOUBLE_EQ(1, v[0]);
   ASSERT_DOUBLE_EQ(2, v[1]);
   ASSERT_DOUBLE_EQ(3, v[2]);
}

TEST_F(fixture_vector, assignment_from_std_initializer_list_too_small) 
{
   mzlib::vector<double, 4> v = {9,9,9,9};
   v = {1,2};
   ASSERT_DOUBLE_EQ(1, v[0]);
   ASSERT_DOUBLE_EQ(2, v[1]);
   ASSERT_DOUBLE_EQ(9, v[2]);
   ASSERT_DOUBLE_EQ(9, v[3]);
}

TEST_F(fixture_vector, assignment_from_std_initializer_list_too_big) 
{
   mzlib::vector<double, 3> v = {9,9,9};
   v = {1,2,3,4,5,6};
   ASSERT_DOUBLE_EQ(1, v[0]);
   ASSERT_DOUBLE_EQ(2, v[1]);
   ASSERT_DOUBLE_EQ(3, v[2]);
}

TEST_F(fixture_vector, assignment_from_std_vector) 
{
   mzlib::vector<int, 3> v = {9,9,9};
   std::vector<int> standard_vector = {1,2,3};
   v = standard_vector;
   ASSERT_DOUBLE_EQ(1, v[0]);
   ASSERT_DOUBLE_EQ(2, v[1]);
   ASSERT_DOUBLE_EQ(3, v[2]);
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

TEST_F(fixture_vector, move_by) 
{
   mzlib::vector<double, 3> v = vec_op::move_by(v123, v456);
   ASSERT_EQ(mzlib::vector3d(5.5,7.7,9.9), v);
}

TEST_F(fixture_vector, square_distance_to) 
{
   double dist = vec_op::sqr_distance(v123, v456);
   ASSERT_DOUBLE_EQ(32.67, dist);
}

TEST_F(fixture_vector, square_distance_std_array) 
{
   std::array<double, 3> a123{1.1,2.2,3.3};
   std::array<double, 3> a456{4.4,5.5,6.6};
   double dist = vec_op::sqr_distance(a123, a456);
   ASSERT_DOUBLE_EQ(32.67, dist);
}

TEST_F(fixture_vector, distance_to) 
{
   double dist = vec_op::distance(v123, v456);
   ASSERT_DOUBLE_EQ(5.715767664977295, dist);
}

TEST_F(fixture_vector, length) 
{
   ASSERT_DOUBLE_EQ(9.6524608261313336, vec_op::length(v456));
}

TEST_F(fixture_vector, operator_equals) 
{
   ASSERT_TRUE(mzlib::vector3d(1.1,2.2,3.3) == v123);
}

TEST_F(fixture_vector, normalise) 
{
   auto v = vec_op::normalise(v456);
   ASSERT_EQ(mzlib::vector3d(0.45584230583855184,0.56980288229818976,0.68376345875782774), v);
}

TEST_F(fixture_vector, operator_multiply) 
{   
   auto v = v123 * v456;
   ASSERT_EQ(mzlib::vector3d(4.84,12.1,21.77999999999999), v);
}

TEST_F(fixture_vector, operator_multiply_with_scalar) 
{   
   auto v = v123 * 3.14;
   ASSERT_EQ(mzlib::vector3d(3.454,6.908,10.362), v);
}

TEST_F(fixture_vector, operator_multiply_with_scalar_scalarfirst) 
{   
   auto v = 3.14 * v123;
   ASSERT_EQ(mzlib::vector3d(3.454,6.908,10.362), v);
}

TEST_F(fixture_vector, operator_multiply_equals) 
{
   v123 *= v456;
   ASSERT_EQ(mzlib::vector3d(4.84,12.1,21.77999999999999), v123);
}

TEST_F(fixture_vector, operator_multiply_equals_with_scalar) 
{
   // todo: do the other with scalar
   v123 *= 3.14;
   ASSERT_EQ(mzlib::vector3d(3.454,6.908,10.362), v123);
}

TEST_F(fixture_vector, operator_divide) 
{   
   auto v = v123 / v456;
   ASSERT_DOUBLE_EQ(0.25, v[0]);
   ASSERT_DOUBLE_EQ(0.4, v[1]);
   ASSERT_DOUBLE_EQ(0.5, v[2]);
}

TEST_F(fixture_vector, operator_divide_with_scalar) 
{   
   auto v = v123 / 3.14;
   ASSERT_EQ(mzlib::vector3d(0.35031847133757965,0.7006369426751593,1.0509554140127388), v);
}

TEST_F(fixture_vector, operator_divide_with_scalar_scalarfirst) 
{   
   auto v = 3.14 / v123;
   ASSERT_EQ(mzlib::vector3d(0.35031847133757965,0.7006369426751593,1.0509554140127388), v);
}

TEST_F(fixture_vector, operator_divide_equals) 
{
   v123 /= v456;
   ASSERT_EQ(mzlib::vector3d(0.25,0.4,0.5), v123);
}

TEST_F(fixture_vector, operator_divide_equals_with_scalar) 
{
   v123 /= 3.14;
   ASSERT_EQ(mzlib::vector3d(0.35031847133757965,0.7006369426751593,1.0509554140127388), v123);
}

TEST_F(fixture_vector, operator_plus) 
{   
   auto v = v123 + v456;
   ASSERT_EQ(mzlib::vector3d(5.5,7.7,9.9), v);
}

TEST_F(fixture_vector, operator_plus_equals) 
{
   v123 += v456;
   ASSERT_EQ(mzlib::vector3d(5.5,7.7,9.9), v123);
}

TEST_F(fixture_vector, operator_minus) 
{
   auto v = v456 - v123;
   ASSERT_EQ(mzlib::vector3d(3.3,3.3,3.3), v);
}

TEST_F(fixture_vector, operator_minus_equals) 
{
   v456 -= v123;
   ASSERT_EQ(mzlib::vector3d(3.3,3.3,3.3), v456);
}

TEST_F(fixture_vector, operator_minus_unary) 
{
   ASSERT_EQ(mzlib::vector3d(-4.4,-5.5,-6.6), -v456);
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
