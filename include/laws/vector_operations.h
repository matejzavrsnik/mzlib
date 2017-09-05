//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef VECTOR_OPERATIONS_H
#define VECTOR_OPERATIONS_H

#include <cmath> // std::sqrt

namespace mzlib {
namespace law {
namespace vector {

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
-> typename std::decay_t<decltype(from[0])>
{
   typename std::decay_t<decltype(from[0])> dist = 0, sqrdist = 0;
   for (size_t i = 0; i<rank(from); ++i) {
      dist = from[i]-to[i];
      sqrdist += dist * dist;
   }
   return sqrdist;
}

template<class VectorT> 
constexpr auto distance (const VectorT& from, const VectorT& to)
-> decltype(sqr_distance(from, to))
{
   return std::sqrt( sqr_distance(from, to) );
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
constexpr VectorT direction(const VectorT& from, const VectorT& to)
{
   return std::move( subtract(to, from) );
}

template<class VectorT> 
constexpr auto length (const VectorT& v)
-> typename std::decay_t<decltype(v[0])>
{
   typename std::decay_t<decltype(v[0])> l = 0;
   for (size_t i=0; i<rank(v); ++i)
      l += v[i] * v[i];
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

}}} // namespace mzlib::laws::vec_op

#endif /* VECTOR_OPERATIONS_H */

#ifdef MZLIB_BUILDING_TESTS

#ifndef VECTOR_OPERATIONS_TESTS_H
#define VECTOR_OPERATIONS_TESTS_H

TEST(law_vector_operations, rank) 
{
   mzlib::vector2d a{1,2};
   mzlib::vector3d b{1,2,3};
   ASSERT_EQ(2, mzlib::law::vector::rank(a));
   ASSERT_EQ(3, mzlib::law::vector::rank(b));
}

TEST(law_vector_operations, rank_array) 
{
   std::array<int,2> a{1,2};
   std::array<int,3> b{1,2,3};
   ASSERT_EQ(2, mzlib::law::vector::rank(a));
   ASSERT_EQ(3, mzlib::law::vector::rank(b));
}

TEST(law_vector_operations, move_by) 
{
   mzlib::vector3d a{1.1,2.2,3.3}, b{4.4,5.5,6.6};
   mzlib::vector3d v = mzlib::law::vector::move_by(a, b);
   ASSERT_EQ(mzlib::vector3d({5.5,7.7,9.9}), v);
}

TEST(law_vector_operations, sqr_distance) 
{
   mzlib::vector3d a{1.1,2.2,3.3}, b{4.4,5.5,6.6};
   double dist = mzlib::law::vector::sqr_distance(a, b);
   ASSERT_DOUBLE_EQ(32.67, dist);
}

TEST(law_vector_operations, sqr_distance_array) 
{
   std::array<double, 3> a{1.1,2.2,3.3}, b{4.4,5.5,6.6};
   double dist = mzlib::law::vector::sqr_distance(a, b);
   ASSERT_DOUBLE_EQ(32.67, dist);
}

TEST(law_vector_operations, distance) 
{
   mzlib::vector3d a{1.1,2.2,3.3}, b{4.4,5.5,6.6};
   double dist = mzlib::law::vector::distance(a, b);
   ASSERT_DOUBLE_EQ(5.715767664977295, dist);
}

TEST(law_vector_operations, subtract) 
{
   mzlib::vector2d from{3,4};
   mzlib::vector2d v{2,1};
   mzlib::vector2d expected{1,3};
   mzlib::vector2d result = mzlib::law::vector::subtract(from, v);
   ASSERT_EQ(expected, result);
}

TEST(law_vector_operations, direction) 
{
   mzlib::vector2d from{1,2};
   mzlib::vector2d to{4,3};
   mzlib::vector2d expected{3,1};
   mzlib::vector2d direction = mzlib::law::vector::direction(from, to);
   ASSERT_EQ(expected, direction);
}

TEST(law_vector_operations, length) 
{
   mzlib::vector3d a{4.4,5.5,6.6};
   ASSERT_DOUBLE_EQ(9.6524608261313336, mzlib::law::vector::length(a));
}

TEST(law_vector_operations, normalise) 
{
   auto v = mzlib::law::vector::normalise(mzlib::vector3d({4,5,6}));
   ASSERT_EQ(mzlib::vector3d({0.45584230583855184,0.56980288229818976,0.68376345875782774}), v);
}

TEST(law_vector_operations, create_unit_vector) 
{
   auto unit2d = mzlib::law::vector::create_unit_vector<mzlib::vector2d>();
   auto unit3d = mzlib::law::vector::create_unit_vector<mzlib::vector2d>();
   ASSERT_EQ(mzlib::vector2d({0.70710678118654746,0.70710678118654746}), unit2d);
   ASSERT_EQ(mzlib::vector2d({0.70710678118654746,0.70710678118654746,0.70710678118654746}), unit3d);
}

TEST(law_vector_operations, equals) 
{
   auto one = mzlib::vector3d({1,2,3});
   auto same = mzlib::vector3d({1,2,3});
   auto different = mzlib::vector3d({1,2,2});
   ASSERT_TRUE(mzlib::law::vector::equals(one, same));
   ASSERT_FALSE(mzlib::law::vector::equals(one, different));
}

TEST(law_vector_operations, add) 
{
   auto a = mzlib::vector3d({1,2,3});
   auto b = mzlib::vector3d({3,2,1});
   auto expected = mzlib::vector3d({4,4,4});
   ASSERT_EQ(expected, mzlib::law::vector::add(a, b));
}

TEST(law_vector_operations, multiply_by_vector) 
{
   auto a = mzlib::vector3d({1,2,3});
   auto b = mzlib::vector3d({2,3,4});
   auto expected = mzlib::vector3d({2,6,12});
   ASSERT_EQ(expected, mzlib::law::vector::multiply_by_vector(a, b));
}

TEST(law_vector_operations, multiply_by_scalar) 
{
   auto a = mzlib::vector3d({1,2,3});
   auto b = 3;
   auto expected = mzlib::vector3d({3,6,9});
   ASSERT_EQ(expected, mzlib::law::vector::multiply_by_scalar(a, b));
}

TEST(law_vector_operations, divide_by_vector) 
{
   auto a = mzlib::vector3d({1,6,3});
   auto b = mzlib::vector3d({2,3,4});
   auto expected = mzlib::vector3d({0.5,2,0.75});
   ASSERT_EQ(expected, mzlib::law::vector::divide_by_vector(a, b));
}

TEST(law_vector_operations, divide_by_scalar) 
{
   auto a = mzlib::vector3d({6,1,4});
   auto b = 2;
   auto expected = mzlib::vector3d({3,0.5,2});
   ASSERT_EQ(expected, mzlib::law::vector::divide_by_scalar(a, b));
}

TEST(law_vector_operations, flip) 
{
   auto a = mzlib::vector3d({6,1,4});
   auto expected = mzlib::vector3d({-6,-1,-4});
   ASSERT_EQ(expected, mzlib::law::vector::flip(a));
}

#endif // VECTOR_OPERATIONS_TESTS_H

#endif // MZLIB_BUILDING_TESTS
