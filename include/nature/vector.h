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
#include "../iterators/copy.h"

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
