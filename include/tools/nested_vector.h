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

#include "../lang/exceptions.h"
#include <vector>

namespace mzlib {
   
namespace nested_vector {

template<typename T>
using type = std::vector<std::vector<T>>;
   
template<typename T>
void enlarge(
   type<T>& vv,
   std::size_t row_count,
   std::size_t col_count)
{
   if(vv.size()<row_count)
      vv.resize(row_count);

   for(auto& v : vv)
      if(v.size()<col_count)
         v.resize(col_count);
}

template<typename T>
void add_top(
   type<T>& vv,
   int row_count,
   const T& val)
{
   vv.insert(vv.begin(), row_count, std::vector<T>(vv[0].size(), val));
}

// Value is not universal reference, because unless this is
// a special case with size 1x1, it needs to be in multiple
// locations anyway, and there is no way to put it there by
// moving.
template<typename T>
type<T> construct(
   std::size_t row_count,
   std::size_t col_count,
   const T& val)
{
   type<T> v(row_count, std::vector<T>(col_count, val));
   return v;
}

template<typename T>
T& access(
   type<T>& vv,
   std::size_t row_index,
   std::size_t col_index)
{
   // Nothing guarantees it's correct height so it needs
   // to be enlarged to this size just in case.
   // The get function works with indexes whilst enlarge 
   // works with count. That's why they are incremented 
   enlarge(vv, row_index+1, col_index+1);  
   return vv[row_index][col_index];
}

// Read only access
template<typename T>
const T& access(
   const type<T>& vv,
   std::size_t row_index,
   std::size_t col_index)
{
   // Read-only version cannot enlarge
   if (vv.size() == 0 || row_index >= vv.size() || col_index >= vv[0].size())
      throw mzlib::exception::out_of_range();
   return vv[row_index][col_index];
}

// Overload for using coordinates (x,y)-system to access field (row, col)-system
template<typename T>
T& access(
   type<T>& vv,
   const mzlib::coordinates2d& coordinates)
{
   // Tricky: they are swapped. In normal coordinate system, second dimension, y, is up-down, whereas
   // in nested vectors, up-down is the first dimension.
   return access(vv, coordinates[1], coordinates[0]);
}

// When you need this overload for read-only
template<typename T>
const T& access(
   const type<T>& vv,
   const mzlib::coordinates2d& coordinates)
{
   // Tricky: they are swapped. In normal coordinate system, second dimension, y, is up-down, whereas
   // in nested vectors, up-down is the first dimension.
   return access(vv, coordinates[1], coordinates[0]);
}

// It's good to have these things named and implemented in one
// place rather than keep thinking which dimension represents
// width and height
template<typename T>
auto width(
   const type<T>& vv) -> decltype(vv.size())
{
   // vv[rows = height][cols = width]
   return vv.size()==0 ? 0 : vv[0].size();
}

template<typename T>
auto height(
   const type<T>& vv) -> decltype(vv.size())
{
   // vv[rows = height][cols = width]
   return vv.size();
}

// useful because you can add the coordinates vector to other vectors
template<typename T>
mzlib::coordinates2d size(
   const type<T>& vv)
{
   // todo: avoid narrowing
   return mzlib::coordinates2d{(int)width(vv), (int)height(vv)};
}

} // namespace nested_vector

} // namespace mzlib

#endif // MZLIB_NESTED_VECTOR_H
