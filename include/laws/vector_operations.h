//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef VECTOR_OPERATIONS_H
#define VECTOR_OPERATIONS_H

#include <cmath> // std::sqrt
#include "../lang/dbl.h"

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
