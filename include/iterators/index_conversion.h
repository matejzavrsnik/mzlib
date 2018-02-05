
#include <vector>

//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_INDEX_CONVERSION_H
#define MZLIB_INDEX_CONVERSION_H

namespace mzlib {

// converts iterator to index
template<class Iterator> 
size_t get_index (Iterator begin, Iterator it) 
{
   return std::distance(begin, it);
}

// converts index to iterator
template<class Iterator> 
Iterator get_iterator (Iterator begin, size_t index) 
{
   while(index--) ++begin;
   return begin;
}

} // namespace

#endif // MZLIB_INDEX_CONVERSION_H
