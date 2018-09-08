//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

// the point of these tests: demonstrate matrix operations
// can be used on matrix implementations not compatible with 
// mzlib::matrix as long as you set out the properties of the
// matrix type properly

#include "gtest/gtest.h"

#include "matrix_operations.h"

namespace {

// this one is not even fully compile-time type-safe and
// access to values is done using [a][b] instead of (a,b).
using mat = std::vector<std::vector<int>>;

}

// Inject alternative matrix type properties into law::matrix namespace

namespace mzlib {
namespace law {
namespace matrix {

template<>
struct rows<mat>
{
   static size_t count(const mat& m)
   {
      return m.size();
   };
};

template<>
struct cols<mat>
{
   static size_t count(const mat& m)
   {
      return m[0].size();
   }
};

template<>
struct value<mat>
{
   // this other matrix implementation is not static,
   // I need to expand it in runtime when value is 
   // accessed to avoid segfaults
   static void resize_to_access(const mat& mc, size_t row, size_t col)
   {
      mat& m = const_cast<mat&>(mc);
      
      if(m.size()<=row)
         m.resize(row+1);
      
      for(auto& v : m)
         if(v.size()<=col)
            v.resize(col+1);
   }
   
   static const int& get(const mat& m, size_t row, size_t col)
   {
      resize_to_access(m, row, col);   
      return m[row][col];
   }
   
   static int& get(mat& m, size_t row, size_t col)
   {
      resize_to_access(m, row, col);
      return m[row][col];
   }
};
   
template<>
struct mult<mat, mat>
{
   mat type;
};

template<>
struct value_type<mat>
{
   int type;
};

}}} // namespace mzlib::law::matrix

TEST(law_matrix_operations_alternative, equals) 
{
   mat one = {{1,2},{3,4}};
   mat same = {{1,2},{3,4}};
   mat different = {{1,2},{3,3}};
   ASSERT_TRUE(mzlib::law::matrix::equals(one, same));
   ASSERT_FALSE(mzlib::law::matrix::equals(one, different));
}

TEST(law_vector_operations_alternative, multiply) 
{
   mat left = {{1,2,3},{4,5,6}};
   mat right = {{7,8},{9,10},{11,12}};
   mat expected = {{58,64},{139,154}};
   mat actual = mzlib::law::matrix::multiply(left, right);
   ASSERT_EQ(expected, actual);
}
