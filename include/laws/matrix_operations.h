//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include "../lang/dbl.h"
#include "../tools/random.h"

namespace mzlib {
namespace law {
namespace matrix {

// These template classes exist to help totally decouple matrix 
// implementations from algorithms over matrices in a way that allows
// for a lot to be done at compile time. For example, some matrices
// like mzlib::matrix will have dimensions encoded in the type itself,
// whereas some other implementation may have dynamic managing of
// dimensions. First case will have dimensions available with something
// like MatrixType::Rows and other in matrix.get_rows() form. The latter
// approach is fundamentally incompatible with the first, so algos
// written for compile-time error checks will not work with them. Even 
// in the case where two implementations took the same approach, what is
// the likelyhood that both will have the same name for variables or
// function names which can be used to get dimensions? May happen, but
// for a truly generic algorithm that is not good enough.
// The attempted solution here for this problem is to decouple actual 
// matrix object from it's manipulation procedures with intermediate
// template classes, which can be specialised for each particular matrix
// implementation. You can think of these as merely ideas for what the
// algos want to learn from matrices, then instruct concrete ways to
// achieve that by specialising class templates for any particular
// matric implementation. See examples in tests, where I successfully
// used the same algos on mzlib::matrix and plain vector<vector>, all 
// I had to do is provide template specialisations for the following.
// I may have gone a bit overboard, but it was fun and it does work, 
// so there you go :)
   
// get dimensions
template<class> struct rows {};
template<class> struct cols {};
// Accessing matrix values can be done in at least two very intuitive
// ways: m(2,3) and m[2][3], depending on implementation. I've seen
// both a lot online. This is as a contrast to various 1D containers 
// which are traditionally accessed through operator[]. If any generic
// algo wants to work with 1D containers, it can afford to use [] and
// it will be useful for most of them. Generic algos on matrices need
// to handle both, if not more implementations of value access.
template<class> struct value {};
// What type is correct for result of multiplication of two matrices?
// If it's dynamic, the same as both matrices and correctness cannot be
// enforced at compile time because dimension is encoded in some 
// variable value. With static matrices it can be because information 
// is encoded in the type itself, but then algos need some way of 
// determining what the result type of an operation is in order to 
// enforce it.
template<class,class> struct mult {};
template<class> struct transposed {};
// this is just underlying type. What is stored in the matrix. Most
// often int, double, that sort of thing.
template<class> struct value_type {};
   
// Now for the actual algos on matrices.

template<class MatrixT> 
bool equals(const MatrixT& a, const MatrixT& b)
{
   if (std::is_integral<decltype(value_type<MatrixT>::type)>::value) {
      for (size_t m = 0; m < rows<MatrixT>::count(a); ++m)
         for (size_t n = 0; n < cols<MatrixT>::count(a); ++n)
         if (value<MatrixT>::get(a,m,n) != value<MatrixT>::get(b,m,n))
            return false;
   }
   else {
      for (size_t m = 0; m < rows<MatrixT>::count(a); ++m)
         for (size_t n = 0; n < cols<MatrixT>::count(a); ++n)
            if (!dbl(value<MatrixT>::get(a,m,n)).equals(value<MatrixT>::get(b,m,n)))
               return false;
   }
   return true;
}

template<class MatrixT>
MatrixT add(const MatrixT& left, const MatrixT& right)
{
   MatrixT res = left;
   
   const auto all_cols = cols<MatrixT>::count(left);
   const auto all_rows = rows<MatrixT>::count(left);

   for(int row = 0; row < all_rows; ++row)
   for(int col = 0; col < all_cols; ++col)
   {
      value<MatrixT>::get(res, row, col) += 
         value<MatrixT>::get(right, row, col);
   }
   
   return res;
};

template<
   class MatrixLeft,
   class MatrixRight,
   class Result = decltype(mult<MatrixLeft,MatrixRight>::type)>
Result multiply(MatrixLeft left, MatrixRight right)
{
   Result res;
   
   const auto left_cols = cols<MatrixLeft>::count(left);
   const auto left_rows = rows<MatrixLeft>::count(left);
   const auto right_cols = cols<MatrixRight>::count(right);
   const auto right_rows = rows<MatrixRight>::count(right);
   
   for(int left_row = 0; left_row < left_rows; ++left_row)
   for(int right_col = 0; right_col < right_cols; ++right_col)
   {
      value<Result>::get(res, left_row, right_col) = 0;
      for(int index  = 0; index < left_cols; ++index)
      {
         const auto left_cell = value<MatrixLeft>::get(left, left_row, index);
         const auto right_cell = value<MatrixRight>::get(right, index, right_col);
         value<Result>::get(res, left_row, right_col) += left_cell * right_cell;
      }
   }
   
   return res;
};

template<class MatrixT, class Scalar>
MatrixT scalar_multiply(const MatrixT& matrix, const Scalar& scalar)
{
   MatrixT res = matrix;
   const auto all_cols = cols<MatrixT>::count(matrix);
   const auto all_rows = rows<MatrixT>::count(matrix);

   for(int row = 0; row < all_rows; ++row)
   for(int col = 0; col < all_cols; ++col)
   {
      value<MatrixT>::get(res, row, col) *= scalar;
   }
   
   return res;
};

template<
   class MatrixT,
   class Result = decltype(transposed<MatrixT>::type)>
Result transpose(const MatrixT& matrix)
{
   Result res;
   const auto all_cols = cols<MatrixT>::count(matrix);
   const auto all_rows = rows<MatrixT>::count(matrix);

   for(int row = 0; row < all_rows; ++row)
   for(int col = 0; col < all_cols; ++col)
   {
      value<Result>::get(res, col, row) = 
         value<MatrixT>::get(matrix, row, col);
   }
   
   return res;
};

template<class MatrixT>
MatrixT negate(const MatrixT& matrix)
{
   MatrixT res = scalar_multiply(matrix, -1);   
   return res;
};

template<class MatrixT>
MatrixT subtract(const MatrixT& left, const MatrixT& right)
{
   MatrixT res = add(left, negate(right));   
   return res;
};

template<class MatrixT>
void randomise(MatrixT& matrix)
{  
   const auto all_cols = cols<MatrixT>::count(matrix);
   const auto all_rows = rows<MatrixT>::count(matrix);

   for(int row = 0; row < all_rows; ++row)
   for(int col = 0; col < all_cols; ++col)
   {
      value<MatrixT>::get(matrix, row, col) = 
         get_random<decltype(value_type<MatrixT>::type)>();
   }
};

}}} // namespace mzlib::law::matrix

#endif /* MATRIX_OPERATIONS_H */
