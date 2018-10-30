//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_RESIZE_H
#define MZLIB_RESIZE_H

#include <vector>

namespace mzlib {

template<typename T>
void resize_nested_vector(
   std::vector<std::vector<T>>& vv, 
   size_t row, 
   size_t col)
{
   if(vv.size()<row)
      vv.resize(row);

   for(auto& v : vv)
      if(v.size()<col)
         v.resize(col);
}

} // namespace

#endif // MZLIB_RESIZE_H
