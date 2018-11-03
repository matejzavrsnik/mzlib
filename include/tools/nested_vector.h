//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_NESTED_VECTOR_H
#define MZLIB_NESTED_VECTOR_H

// This collection of convenient functions to better 
// handle vectors of vectors that pop up every now and then

#include <vector>

namespace mzlib {
   
namespace nested_vector {

template<typename T>
using type = std::vector<std::vector<T>>;
   
template<typename T>
void enlarge(
   type<T>& vv, 
   size_t row_count, 
   size_t col_count)
{
   if(vv.size()<row_count)
      vv.resize(row_count);

   for(auto& v : vv)
      if(v.size()<col_count)
         v.resize(col_count);
}

// Value is not universal reference, because unless this is
// a special case with size 1x1, it needs to be in multiple
// locations anyway, and there is no way to put it there by
// moving.
template<typename T>
type<T> construct(
   size_t row_count, 
   size_t col_count,
   const T& val)
{
   type<T> v(row_count, std::vector<T>(col_count, val));
   return v;
};

template<typename T>
T& access(
   type<T>& vv,
   size_t row_index, 
   size_t col_index)
{
   // Nothing guarantees it's correct height so it needs
   // to be enlarged to this size just in case.
   // The get function works with indexes whilst enlarge 
   // works with count. That's why they are incremented 
   enlarge(vv, row_index+1, col_index+1);  
   return vv[row_index][col_index];
}

} // namespace nested_vector

} // namespace mzlib

#endif // MZLIB_NESTED_VECTOR_H
