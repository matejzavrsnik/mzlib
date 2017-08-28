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

   constexpr static vector<TYPE,DIM> create_unit()
   {
      vector<TYPE,DIM> v;
      for (TYPE& e : v.m_array) e = 1;
      return normalise(v);
   }

public:
   
   constexpr static size_t dimensions()
   {
      return DIM;
   }
   
   constexpr static vector<TYPE,DIM> unit = vector<TYPE,DIM>::create_unit();
    
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
    
   size_t size() const 
   {
      return DIM;
   }
    
   static vector<TYPE,DIM> all_ones () 
   {
      vector<TYPE,DIM> ones;
      for (size_t i = 0; i<DIM; ++i) {
         ones[i] = 1;
      }
      return ones;
   }

   static vector<TYPE,DIM> all_zeros () 
   {
      vector<TYPE,DIM> ones;
      for (size_t i = 0; i<DIM; ++i) {
         ones[i] = 0;
      }
      return ones;
   }
    
   vector<TYPE, DIM> move_by (const vector<TYPE,DIM>& other) const
   {
      vector<TYPE, DIM> result(*this);
      for (size_t i = 0; i<DIM; ++i) {
         result[i] += other[i];
      }
      return result;
   }
    
   TYPE square_distance_to(const vector<TYPE,DIM>& other) const 
   {
      TYPE sqrdist = 0;
      for (size_t i = 0; i<DIM; ++i) {
         sqrdist += std::pow( m_array[i]-other[i], 2);
      }
      return sqrdist;
   }

   TYPE distance_to (const vector<TYPE,DIM>& other) const 
   {
      TYPE dist = std::sqrt(square_distance_to(other));
      return dist;
   }
    
   vector<TYPE,DIM> direction_to (const vector<TYPE,DIM>& other) const 
   {
      return *this - other;
   }
    

    

    
   
};

template<typename TYPE, size_t DIM> 
constexpr TYPE vector_length (const vector<TYPE,DIM>& vector_other)
{
   TYPE len = 0;
   for (size_t i=0; i<DIM; ++i) {
      len += std::pow(vector_other[i], 2);
   }
   len = std::sqrt(len);
   return len;
}

template<typename TYPE, size_t DIM> 
constexpr vector<TYPE, DIM> normalise (vector<TYPE,DIM> vector_other)
{
   TYPE l = vector_length(vector_other);
   for (size_t i=0; i<DIM; ++i) {
      vector_other[i] /= l;
   }
   return vector_other;
}

// I don't think gcc v4.8.3 handles std::is_integral well. It still reports a
// floating point comparing problem in this function.
//todo: remove the diagnostic suppression after it's been fixed. Or after I am proved wrong.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
template<typename TYPE, size_t DIM> 
bool operator== (const mzlib::vector<TYPE,DIM>& vector_this, const vector<TYPE,DIM>& vector_other)
{
   for (size_t i=0; i<DIM; ++i) {
      //todo: switch to is_integral_v when C++17 is available
      if (std::is_floating_point<TYPE>::value) {
         if (!dbl(vector_this[i]).equals(vector_other[i])) {
            return false;
         }
      }
      else if (vector_this[i] != vector_other[i]) {
         return false;
      }
   }
   return true;
}
#pragma GCC diagnostic pop

template<typename TYPE, size_t DIM> 
bool operator!= (const mzlib::vector<TYPE,DIM>& vector_this, const vector<TYPE,DIM>& vector_other)
{
   return !operator==(vector_this, vector_other);
}
   





template<typename TYPE, size_t DIM> 
vector<TYPE,DIM> operator+ (mzlib::vector<TYPE,DIM> vector_this, const vector<TYPE,DIM>& vector_other)
{  
   for (size_t i = 0; i<DIM; ++i) {
      vector_this[i] += vector_other[i];
   }
   return vector_this; 
}

template<typename TYPE, size_t DIM> 
vector<TYPE,DIM> operator+= (mzlib::vector<TYPE,DIM>& vector_this, const vector<TYPE,DIM>& vector_other) 
{
   vector_this = vector_this + vector_other;
   return vector_this;
}

template<typename TYPE, size_t DIM> 
vector<TYPE,DIM> operator- (mzlib::vector<TYPE,DIM> vector_this, const vector<TYPE,DIM>& vector_other)
{
   // will compiler unwind this loop? test someday. It has every info available.
   for (size_t i = 0; i<DIM; ++i) {
      vector_this[i] -= vector_other[i];
   }
   return vector_this;
}

template<typename TYPE, size_t DIM> 
vector<TYPE, DIM> operator- (mzlib::vector<TYPE,DIM> vector_this)
{
   for (size_t i = 0; i<DIM; ++i) {
      vector_this[i] *= -1;
   }
   return vector_this;
}

template<typename TYPE, size_t DIM> 
vector<TYPE,DIM> operator-= (mzlib::vector<TYPE,DIM>& vector_this, const vector<TYPE,DIM>& vector_other) 
{
   vector_this = vector_this - vector_other;
   return vector_this;
}

template<typename TYPE, size_t DIM> 
mzlib::vector<TYPE,DIM> operator* (mzlib::vector<TYPE,DIM> vector_this, const mzlib::vector<TYPE,DIM>& vector_other)
{  
   for (size_t i = 0; i<DIM; ++i) {
      vector_this[i] *= vector_other[i];
   }
   return vector_this; 
}

template<typename TYPE, typename SCALAR, size_t DIM> 
mzlib::vector<TYPE,DIM> operator* (mzlib::vector<TYPE,DIM> vector_this, const SCALAR& other)
{  
   for (size_t i = 0; i<DIM; ++i) {
      vector_this[i] *= other;
   }
   return vector_this; 
}

template<typename TYPE, size_t DIM> 
mzlib::vector<TYPE,DIM> operator*= (mzlib::vector<TYPE,DIM>& vector_this, const mzlib::vector<TYPE,DIM>& vector_other) 
{
   vector_this = vector_this * vector_other;
   return vector_this;
}

template<typename TYPE, size_t DIM> 
mzlib::vector<TYPE,DIM> operator*= (mzlib::vector<TYPE,DIM>& vector_this, const TYPE& other) 
{
   for (size_t i = 0; i<DIM; ++i) {
      vector_this[i] *= other;
   }        
   return vector_this;
}

template<typename TYPE, size_t DIM> 
mzlib::vector<TYPE,DIM> operator/ (mzlib::vector<TYPE,DIM> vector_this, const mzlib::vector<TYPE,DIM>& other)
{  
   for (size_t i = 0; i<DIM; ++i) {
      vector_this[i] /= other[i];
   }
   return vector_this; 
}

template<typename TYPE, size_t DIM> 
mzlib::vector<TYPE,DIM> operator/ (mzlib::vector<TYPE,DIM> vector_this, const TYPE& other)
{  
   for (size_t i = 0; i<DIM; ++i) 
   {
      vector_this[i] /= other;
   }
   return vector_this; 
}

template<typename TYPE, size_t DIM> 
mzlib::vector<TYPE,DIM> operator/= (mzlib::vector<TYPE,DIM>& vector_this, const mzlib::vector<TYPE,DIM>& vector_other) 
{
   vector_this = vector_this / vector_other;
   return vector_this;
}

template<typename TYPE, size_t DIM> 
mzlib::vector<TYPE,DIM> operator/= (mzlib::vector<TYPE,DIM>& vector_this, const TYPE& vector_other) 
{
   for (size_t i = 0; i<DIM; ++i) {
      vector_this[i] /= vector_other;
   }        
   return vector_this;
}

template<typename TYPE, size_t DIM> 
mzlib::vector<TYPE,DIM> operator* (const TYPE& scalar, const mzlib::vector<TYPE,DIM>& vector)
{
   return vector * scalar; // turning the operands around is enough, operation is commutative
}

template<typename TYPE, size_t DIM> 
mzlib::vector<TYPE,DIM> operator/ (const TYPE& scalar, const mzlib::vector<TYPE,DIM>& vector)
{
   return vector / scalar; // turning the operands around is enough, operation is commutative
}

template<class TYPE, size_t DIM>
std::ostream& operator<< (std::ostream& os, const mzlib::vector<TYPE,DIM>& vector)
{
   os << "[";
   for (size_t i=0; i<vector.size(); ++i) {
      if (i!=0) os << ",";
      os << vector[i];
   }
   os << "]";
   return os;
}

// Convenient types

using vector2d = vector<double, 2>;
using vector3d = vector<double, 3>;
using point2d  = vector<double, 2>;
using point3d  = vector<double, 3>;

} // namespace

#endif // MZLIB_VECTOR_H

#ifdef MZLIB_BUILDING_TESTS

#ifndef MZLIB_VECTOR_TESTS_H
#define MZLIB_VECTOR_TESTS_H

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
   mzlib::vector<double, 3> v = {9,9,9};
   std::vector<double> standard_vector = {1,2,3};
   v = standard_vector;
   ASSERT_DOUBLE_EQ(1, v[0]);
   ASSERT_DOUBLE_EQ(2, v[1]);
   ASSERT_DOUBLE_EQ(3, v[2]);
}

TEST_F(fixture_vector, assignment_from_std_vector_too_small) 
{
   mzlib::vector<double, 4> v = {9,9,9,9};
   std::vector<double> standard_vector = {1,2};
   v = standard_vector;
   ASSERT_DOUBLE_EQ(1, v[0]);
   ASSERT_DOUBLE_EQ(2, v[1]);
   ASSERT_DOUBLE_EQ(9, v[2]);
   ASSERT_DOUBLE_EQ(9, v[3]);
}

TEST_F(fixture_vector, assignment_from_std_vector_too_big) 
{
   mzlib::vector<double, 3> v = {9,9,9};
   std::vector<double> standard_vector = {1,2,3,4,5,6};
   v = standard_vector;
   ASSERT_DOUBLE_EQ(1, v[0]);
   ASSERT_DOUBLE_EQ(2, v[1]);
   ASSERT_DOUBLE_EQ(3, v[2]);
}

TEST_F(fixture_vector, move_by) 
{
   mzlib::vector<double, 3> v_dest = v123.move_by(v456);
   ASSERT_DOUBLE_EQ(5.5, v_dest[0]);
   ASSERT_DOUBLE_EQ(7.7, v_dest[1]);
   ASSERT_DOUBLE_EQ(9.9, v_dest[2]);
}

TEST_F(fixture_vector, square_distance_to) 
{
   double dist = v123.square_distance_to(v456);
   ASSERT_DOUBLE_EQ(32.67, dist);
}

TEST_F(fixture_vector, distance_to) 
{
   double dist = v123.distance_to(v456);
   ASSERT_DOUBLE_EQ(5.715767664977295, dist);
}

TEST_F(fixture_vector, length) 
{
   ASSERT_DOUBLE_EQ(9.6524608261313336, vector_length(v456));
}

TEST_F(fixture_vector, operator_equals) 
{
   mzlib::vector<double, 3> v_equal{1.1,2.2,3.3};
   ASSERT_TRUE(v123 == v_equal);
}

TEST_F(fixture_vector, normalise) 
{
   auto v = normalise(v456);
   ASSERT_DOUBLE_EQ(0.45584230583855184, v[0]);
   ASSERT_DOUBLE_EQ(0.56980288229818976, v[1]);
   ASSERT_DOUBLE_EQ(0.68376345875782774, v[2]);
}

TEST_F(fixture_vector, operator_multiply) 
{   
   auto v = v123 * v456;
   ASSERT_DOUBLE_EQ(4.84, v[0]);
   ASSERT_DOUBLE_EQ(12.1, v[1]);
   ASSERT_DOUBLE_EQ(21.77999999999999, v[2]);
}

TEST_F(fixture_vector, operator_multiply_with_scalar) 
{   
   auto v = v123 * 3.14;
   ASSERT_DOUBLE_EQ(3.454, v[0]);
   ASSERT_DOUBLE_EQ(6.908, v[1]);
   ASSERT_DOUBLE_EQ(10.362, v[2]);
}

TEST_F(fixture_vector, operator_multiply_with_scalar_scalarfirst) 
{   
   auto v = 3.14 * v123;
   ASSERT_DOUBLE_EQ(3.454, v[0]);
   ASSERT_DOUBLE_EQ(6.908, v[1]);
   ASSERT_DOUBLE_EQ(10.362, v[2]);
}

TEST_F(fixture_vector, operator_multiply_equals) 
{
   v123 *= v456;
   ASSERT_DOUBLE_EQ(4.84, v123[0]);
   ASSERT_DOUBLE_EQ(12.1, v123[1]);
   ASSERT_DOUBLE_EQ(21.77999999999999, v123[2]);
}

TEST_F(fixture_vector, operator_multiply_equals_with_scalar) 
{
   // todo: do the other with scalar
   v123 *= 3.14;
   ASSERT_DOUBLE_EQ(3.454, v123[0]);
   ASSERT_DOUBLE_EQ(6.908, v123[1]);
   ASSERT_DOUBLE_EQ(10.362, v123[2]);
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
   ASSERT_DOUBLE_EQ(0.35031847133757965, v[0]);
   ASSERT_DOUBLE_EQ(0.7006369426751593, v[1]);
   ASSERT_DOUBLE_EQ(1.0509554140127388, v[2]);
}

TEST_F(fixture_vector, operator_divide_with_scalar_scalarfirst) 
{   
   auto v = 3.14 / v123;
   ASSERT_DOUBLE_EQ(0.35031847133757965, v[0]);
   ASSERT_DOUBLE_EQ(0.7006369426751593, v[1]);
   ASSERT_DOUBLE_EQ(1.0509554140127388, v[2]);
}

TEST_F(fixture_vector, operator_divide_equals) 
{
   v123 /= v456;
   ASSERT_DOUBLE_EQ(0.25, v123[0]);
   ASSERT_DOUBLE_EQ(0.4, v123[1]);
   ASSERT_DOUBLE_EQ(0.5, v123[2]);
}

TEST_F(fixture_vector, operator_divide_equals_with_scalar) 
{
   v123 /= 3.14;
   ASSERT_DOUBLE_EQ(0.35031847133757965, v123[0]);
   ASSERT_DOUBLE_EQ(0.7006369426751593, v123[1]);
   ASSERT_DOUBLE_EQ(1.0509554140127388, v123[2]);
}

TEST_F(fixture_vector, operator_plus) 
{   
   auto v = v123 + v456;
   ASSERT_DOUBLE_EQ(5.5, v[0]);
   ASSERT_DOUBLE_EQ(7.7, v[1]);
   ASSERT_DOUBLE_EQ(9.9, v[2]);
}

TEST_F(fixture_vector, operator_plus_equals) 
{
   v123 += v456;
   ASSERT_DOUBLE_EQ(5.5, v123[0]);
   ASSERT_DOUBLE_EQ(7.7, v123[1]);
   ASSERT_DOUBLE_EQ(9.9, v123[2]);
}

TEST_F(fixture_vector, operator_minus) 
{
   auto v = v456 - v123;
   ASSERT_DOUBLE_EQ(3.3, v[0]);
   ASSERT_DOUBLE_EQ(3.3, v[1]);
   ASSERT_DOUBLE_EQ(3.3, v[2]);
}

TEST_F(fixture_vector, operator_minus_equals) 
{
   v456 -= v123;
   ASSERT_DOUBLE_EQ(3.3, v456[0]);
   ASSERT_DOUBLE_EQ(3.3, v456[1]);
   ASSERT_DOUBLE_EQ(3.3, v456[2]);
}

TEST_F(fixture_vector, operator_minus_unary) 
{
   mzlib::vector<double, 3> negative_v456{-4.4,-5.5,-6.6};
   ASSERT_TRUE(negative_v456 == -v456);
}

TEST_F(fixture_vector, dimensions)
{
   ASSERT_EQ(2, (mzlib::vector<double, 2>::dimensions()));
   ASSERT_EQ(3, (mzlib::vector<double, 3>::dimensions()));
   ASSERT_EQ(4, (mzlib::vector<double, 4>::dimensions()));
}


#endif // MZLIB_VECTOR_TESTS_H

#endif // MZLIB_BUILDING_TESTS
