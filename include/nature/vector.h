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
#include <memory> // for unique_ptr
#include <concepts> // for integral

#include "../lang/dbl.h"
#include "../laws/vector_operations.h"
#include "../iterators/copy.h"
#include "../lang/hash_combine.h"

namespace mzlib {

// Fixed size mathematical vector.
   
// Motivation to write own class (goals):
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

   using vector_type = std::array<TypeT, DimT>;
   std::unique_ptr<vector_type> m_array;
   
public:

   using value_type = TypeT;

   vector (vector<TypeT,DimT> &&) = default;
   vector& operator= (vector<TypeT,DimT>&&) = default;
   ~vector () = default;

   vector () : 
      m_array(std::make_unique<vector_type>())
   {
   };
   
   vector (const vector<TypeT,DimT>& other) :
      vector()
   {
      *m_array = *other.m_array;
   }

   vector& operator= (const vector<TypeT,DimT>& other)
   {
      *m_array = *other.m_array;
      return *this;
   }
   
   // implicit conversion from std::initializer_list
   // cppcheck-suppress noExplicitConstructor
   vector (const std::initializer_list<TypeT>& list) : 
      vector()
   {
      copy(list.begin(), list.end(), m_array->begin(), m_array->end());
   }
    
   // implicit conversion from std::vector
   // cppcheck-suppress noExplicitConstructor
   vector (const std::vector<TypeT>& vec) :
      vector()
   {
      copy(vec.begin(), vec.end(), m_array->begin(), m_array->end());
   }
    
   vector<TypeT,DimT>& operator= (const std::vector<TypeT>& vec) 
   {    
      copy(vec.begin(), vec.end(), m_array->begin(), m_array->end());
      return *this;
   }
    
   vector<TypeT,DimT>& operator= (const std::initializer_list<TypeT>& list) 
   { 
      copy(list.begin(), list.end(), m_array->begin(), m_array->end());
      return *this;
   }
        
   TypeT& operator[] (size_t n) 
   { 
      return (*m_array)[n]; 
   }
    
   const TypeT& operator[] (size_t n) const 
   { 
      return (*m_array)[n];
   }
    
   static size_t size()
   {
      return DimT;
   }

   // iteration
   // todo: ideally I wouldn't leak internal implementation here, but that would require writing own iterator
   vector_type::iterator begin() noexcept
   {
      return m_array->begin();
   }

   vector_type::const_iterator begin() const noexcept
   {
      return m_array->begin();
   }

   vector_type::const_iterator cbegin() const noexcept
   {
      return m_array->cbegin();
   }

   vector_type::iterator end() noexcept
   {
      return m_array->end();
   }

   vector_type::const_iterator end() const noexcept
   {
      return m_array->end();
   }

   vector_type::const_iterator cend() const noexcept
   {
      return m_array->cend();
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

template<typename T, size_t D>
constexpr auto operator<(const mzlib::vector<T,D> lhs, const mzlib::vector<T,D> rhs)
{
   for (size_t i = 0; i<D; ++i)
      if(lhs[i] < rhs[i]) return true;
      else if(lhs[i] > rhs[i]) return false;

   return false;
}

template<typename T, size_t D>
auto begin(mzlib::vector<T,D>& v) -> decltype(v.begin())
{
   return v.begin();
}

template<typename T, size_t D>
std::array<T, D>::const_iterator cbegin(const mzlib::vector<T,D>& v)
{
   return v.cbegin();
}

template<typename T, size_t D>
auto end(mzlib::vector<T,D>& v) -> decltype(v.end())
{
   return v.end();
}

template<typename T, size_t D>
std::array<T, D>::const_iterator cend(const mzlib::vector<T,D>& v)
{
   return v.cend();
}

// convenient partial templates
// using _t postfix to save more convenient name for the application code

template<typename T> using vector2_t = mzlib::vector<T, 2>;
template<typename T> using vector3_t = mzlib::vector<T, 3>;
template<std::integral T> using grid_t = vector2_t<vector2_t<T>>;
template<std::integral T> using lattice_t = vector3_t<vector3_t<T>>;
template<std::floating_point T> using field_t = vector2_t<vector2_t<T>>;
template<std::floating_point T> using space_t = vector3_t<vector3_t<T>>;

// convenient types

using vector2d = vector2_t<double>;
using vector3d = vector3_t<double>;
using point2d  = vector2_t<double>;
using point3d  = vector3_t<double>;
using coordinates2d  = vector2_t<long>;
using coordinates3d  = vector3_t<long>;

// convenient values

static const vector2d unit_vector2d = law::vector::create_unit_vector<vector2d>();
static const vector3d unit_vector3d = law::vector::create_unit_vector<vector3d>();

} // namespace

namespace std
{
template <typename T, size_t D>
struct hash<mzlib::vector<T, D>>
{
   size_t
   operator() (const mzlib::vector<T, D>& v) const noexcept
   {
      size_t hash = 112358;

      for (size_t i = 0; i<D; ++i)
         ::mzlib::hash_combine(hash, v[i]);

      return hash;
   }
};

}

#endif // MZLIB_VECTOR_H
