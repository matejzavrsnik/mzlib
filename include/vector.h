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

#include "dbl.h"

namespace mzlib {

// Fixed size mathematical vector.
// Motivation to write own class (goals):
//   - boost::ublas::c_vector can't be constexpr and std::vector isn't mathematical
//   - std::vector is dynamic and can't fail compilation if used with mixed dimensions

// Should I implement base vector class and use that one in physical laws instead of
// concrete template instantiations? No, laws should work with any vector type. I am
// not building another framework. If laws are function templates, that is perfect.
   
template<class TYPE, size_t DIM>
class cvector 
{

private:

   std::array<TYPE, DIM> m_array;
    
public:
    
   // This weird constructor uses variadic templates to try to squeeze anything into a vector
   template <typename... T> constexpr explicit cvector (T... val) : 
      m_array{val...} 
   {
   }
    
   constexpr cvector () : 
      m_array{0} // the rest will be zero too
   {
   };

   cvector (const cvector<TYPE,DIM>&) = default;
   cvector (cvector<TYPE,DIM> &&) = default;
   cvector& operator= (const cvector<TYPE,DIM>&) = default;
   cvector& operator= (cvector<TYPE,DIM>&&) = default;
   ~cvector () = default;
    
   cvector (const std::initializer_list<TYPE>& list) : 
      m_array{0}
   {
      size_t min_dim = std::min(DIM, list.size());
      size_t i = 0;
      for (auto list_it = list.begin(); i<min_dim; ++i, ++list_it) {
         m_array[i] = *list_it;
      }
   }
    
   // implicit conversion from std::vector
   cvector (const std::vector<TYPE>& vec) : 
      m_array{0}
   {
      size_t min_dim = std::min(DIM, vec.size());
      for (size_t i = 0; i<min_dim; ++i) {
         m_array[i] = vec[i];
      }
   }
    
   cvector<TYPE,DIM>& operator= (const std::vector<TYPE>& vec) 
   {    
      size_t min_dim = std::min(DIM, vec.size());
      for (size_t i = 0; i<min_dim; ++i) {
         m_array[i] = vec[i];
      }
      return *this;
   }
    
   cvector<TYPE,DIM>& operator= (const std::initializer_list<TYPE>& list) 
   { 
      size_t min_dim = std::min(DIM, list.size());
      size_t i = 0;
      for (auto list_it = list.begin(); i<min_dim; ++i, ++list_it) {
         m_array[i] = *list_it;
      }
      return *this;
   }
        
   TYPE& operator[] (size_t n) 
   { 
      return m_array[n]; 
   }
    
   const TYPE& operator[] (size_t n) const 
   { 
      return m_array[n];
   }
    
   size_t size() const 
   {
      return DIM;
   }
    
   static cvector<TYPE,DIM> all_ones () 
   {
      cvector<TYPE,DIM> ones;
      for (size_t i = 0; i<DIM; ++i) {
         ones[i] = 1;
      }
      return ones;
   }

   static cvector<TYPE,DIM> all_zeros () 
   {
      cvector<TYPE,DIM> ones;
      for (size_t i = 0; i<DIM; ++i) {
         ones[i] = 0;
      }
      return ones;
   }
    
   cvector<TYPE, DIM> move_by (const cvector<TYPE,DIM>& other) const
   {
      cvector<TYPE, DIM> result(*this);
      for (size_t i = 0; i<DIM; ++i) {
         result[i] += other[i];
      }
      return result;
   }
    
   TYPE square_distance_to(const cvector<TYPE,DIM>& other) const 
   {
      TYPE sqrdist = 0;
      for (size_t i = 0; i<DIM; ++i) {
         sqrdist += std::pow( m_array[i]-other[i], 2);
      }
      return sqrdist;
   }

   TYPE distance_to (const cvector<TYPE,DIM>& other) const 
   {
      TYPE dist = std::sqrt(square_distance_to(other));
      return dist;
   }
    
   cvector<TYPE,DIM> direction_to (const cvector<TYPE,DIM>& other) const 
   {
      return *this - other;
   }
    
   TYPE length () const 
   {
      TYPE len = 0;
      for (size_t i=0; i<DIM; ++i) {
         len += std::pow(m_array[i], 2);
      }
      len = std::sqrt(len);
      return len;
   }
    
   cvector<TYPE, DIM> normalise () const
   {
      cvector<TYPE, DIM> result(*this);
      TYPE l = length();
      for (size_t i=0; i<DIM; ++i) {
         result[i] /= l;
      }
      return result;
   }
    
   // I don't think gcc v4.8.3 handles std::is_integral well. It still reports a
   // floating point comparing problem in this function.
   //todo: remove the diagnostic suppression after it's been fixed. Or after I am proved wrong.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
   bool operator== (const cvector<TYPE,DIM>& other) const
   {
      for (size_t i=0; i<DIM; ++i) {
         //todo: switch to is_integral_v when C++17 is available
         if (std::is_floating_point<TYPE>::value) {
            if (!dbl(m_array[i]).equals(other.m_array[i])) {
               return false;
            }
         }
         else if (m_array[i] != other.m_array[i]) {
            return false;
         }
      }
      return true;
   }
#pragma GCC diagnostic pop
   
   bool operator!= (const cvector<TYPE,DIM>& other) const
   {
      return !operator==(other);
   }
   
   cvector<TYPE,DIM> operator+ (const cvector<TYPE,DIM>& other) const 
   {  
      cvector<TYPE, DIM> result(*this);
      for (size_t i = 0; i<DIM; ++i) {
         result[i] += other[i];
      }
      return result; 
   }
    
   cvector<TYPE,DIM> operator+= (const cvector<TYPE,DIM>& other) 
   {
      *this = *this + other;
      return *this;
   }

   cvector<TYPE,DIM> operator- (const cvector<TYPE,DIM>& other) const 
   {
      // will compiler unwind this loop? test someday. It has every info available.
      cvector<TYPE, DIM> result(*this);
      for (size_t i = 0; i<DIM; ++i) {
         result.m_array[i] -= other[i];
      }
      return result;
   }
    
   cvector<TYPE, DIM> operator- () const
   {
      cvector<TYPE, DIM> result(*this);
      for (size_t i = 0; i<DIM; ++i) {
         result[i] *= -1;
      }
      return result;
   }
    
   cvector<TYPE,DIM> operator-= (const cvector<TYPE,DIM>& other) 
   {
      *this = *this - other;
      return *this;
   }
    
   cvector<TYPE,DIM> operator* (const cvector<TYPE,DIM>& other) const 
   {  
      cvector<TYPE, DIM> result(*this);
      for (size_t i = 0; i<DIM; ++i) {
         result[i] *= other[i];
      }
      return result; 
   }
    
   cvector<TYPE,DIM> operator* (const TYPE& other) const 
   {  
      cvector<TYPE, DIM> result(*this);
      for (size_t i = 0; i<DIM; ++i) {
         result[i] *= other;
      }
      return result; 
   }
    
   cvector<TYPE,DIM> operator*= (const cvector<TYPE,DIM>& other) 
   {
      *this = *this * other;
      return *this;
   }

   cvector<TYPE,DIM> operator*= (const TYPE& other) 
   {
      for (size_t i = 0; i<DIM; ++i) {
         m_array[i] *= other;
      }        
      return *this;
   }
    
   cvector<TYPE,DIM> operator/ (const cvector<TYPE,DIM>& other) const 
   {  
      cvector<TYPE, DIM> result(*this);
      for (size_t i = 0; i<DIM; ++i) {
         result[i] /= other[i];
      }
      return result; 
   }
    
   cvector<TYPE,DIM> operator/ (const TYPE& other) const 
   {  
      cvector<TYPE, DIM> result(*this);
      for (size_t i = 0; i<DIM; ++i) 
      {
         result[i] /= other;
      }
      return result; 
   }
    
   cvector<TYPE,DIM> operator/= (const cvector<TYPE,DIM>& other) 
   {
      *this = *this / other;
      return *this;
   }
    
   cvector<TYPE,DIM> operator/= (const TYPE& other) 
   {
      for (size_t i = 0; i<DIM; ++i) {
         m_array[i] /= other;
      }        
      return *this;
   }
    
};

// And now, useful operators that can't be member functions

template<typename TYPE, size_t DIM> cvector<TYPE,DIM> operator* (const TYPE& scalar, const cvector<TYPE,DIM>& vector)
{
   return vector * scalar; // turning the operands around is enough, operation is commutative
}

template<typename TYPE, size_t DIM> cvector<TYPE,DIM> operator/ (const TYPE& scalar, const cvector<TYPE,DIM>& vector)
{
   return vector / scalar; // turning the operands around is enough, operation is commutative
}

// Convenient types

using cvector2d = cvector<double, 2>;
using cvector3d = cvector<double, 3>;
using cpoint2d  = cvector<double, 2>;
using cpoint3d  = cvector<double, 3>;
    
} // namespace

#endif /* MZLIB_VECTOR_H */

