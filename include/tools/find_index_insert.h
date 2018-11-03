//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_FIND_INDEX_INSERT_H
#define MZLIB_FIND_INDEX_INSERT_H

#include <vector>

namespace mzlib {

// If item isn't in the vector it will insert it, but
// in any case it will return an index of it in it
template<typename T>
unsigned find_index_insert(std::vector<T>& vec, T val)
{
   for (unsigned i=0; i<vec.size(); ++i)
      if (vec[i] == val)
         return i;
   
   vec.push_back(val);
   
   return vec.size()-1;
}

} // namespace

#endif // MZLIB_FIND_INDEX_INSERT_H
