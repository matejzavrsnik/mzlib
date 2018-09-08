//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_MATRIX_H
#define MZLIB_MATRIX_H

#include <initializer_list>
#include <array>

#include "../laws/matrix_operations.h"
#include "../iterators/copy_to_nested.h"

namespace mzlib {

// Fixed size mathematical matrix.
   
template<class TypeT, size_t DimRows, size_t DimCols>
class matrix
{

private:

   using matrix_type = std::array<std::array<TypeT, DimCols>, DimRows>;
   matrix_type m_matrix;
   
public:
   
   constexpr matrix (const matrix&) = default;
   constexpr matrix (matrix &&) = default;
   constexpr matrix& operator= (const matrix&) = default;
   constexpr matrix& operator= (matrix&&) = default;
   ~matrix () = default;

   constexpr matrix () :
      m_matrix{{0}}
   {
   }
   
   // implicit conversion from std::initializer_list
   constexpr matrix (const std::initializer_list<TypeT>& list) :
      matrix()
   {
      copy_to_nested(list.begin(), list.end(), m_matrix.begin(), m_matrix.end());
   }

   // implicit conversion from std::vector
   constexpr matrix (const std::vector<TypeT>& vec) :
      matrix()
   {
      copy_to_nested(vec.begin(), vec.end(), m_matrix.begin(), m_matrix.end());
   }

   constexpr TypeT& operator() (size_t row, size_t col) 
   { 
      return m_matrix[row][col]; 
   }
    
   constexpr const TypeT& operator() (size_t row, size_t col) const 
   { 
      return m_matrix[row][col]; 
   }

};

template<typename T, size_t Rows, size_t Cols> 
constexpr bool operator== (const mzlib::matrix<T,Rows,Cols>& a, const mzlib::matrix<T,Rows,Cols>& b)
{
    return law::matrix::equals(a, b);
}

template<typename T, size_t Rows, size_t Cols> 
constexpr bool operator!= (const mzlib::matrix<T,Rows,Cols>& a, const mzlib::matrix<T,Rows,Cols>& b)
{
   return !law::matrix::equals(a, b);
}

template<typename MatrixLeft, typename MatrixRight> 
constexpr auto operator* (const MatrixLeft& left, const MatrixRight& right)
   -> decltype(law::matrix::multiply(left, right))
{
   return law::matrix::multiply(left, right);
}

// Convenient types

using matrix2x2 = matrix<double, 2, 2>;
using matrix3x3 = matrix<double, 3, 3>;

// Inject matrix type properties into law::matrix namespace

namespace law {
namespace matrix {

template<class T, size_t M, size_t N>
struct rows<mzlib::matrix<T,M,N>>
{
   static constexpr size_t count(const mzlib::matrix<T,M,N>&)
   { 
      return M;
   }
};

template<class T, size_t M, size_t N>
struct cols<mzlib::matrix<T, M, N>>
{
   static constexpr size_t count(const mzlib::matrix<T,M,N>&)
   {
      return N;
   }
};

template<class T, size_t M, size_t N>
struct value<mzlib::matrix<T, M, N>>
{
   static constexpr const T& get(
      const mzlib::matrix<T,M,N>& m, 
      size_t row,
      size_t col)
   {
      return m(row,col);
   }
   
   static constexpr T& get(
      mzlib::matrix<T,M,N>& m, 
      size_t row,
      size_t col)
   {
      return m(row,col);
   }
};

template<class T, size_t Tm, size_t Tn, size_t Um, size_t Un>
struct mult<
   mzlib::matrix<T, Tm, Tn>, 
   mzlib::matrix<T, Um, Un>>
{
   mzlib::matrix<T, Tm, Un> type;
};

template<class T, size_t M, size_t N>
struct value_type<mzlib::matrix<T, M, N>>
{
   T type;
};

}} // namespace law::matrix

} // namespace

#endif // MZLIB_MATRIX_H
