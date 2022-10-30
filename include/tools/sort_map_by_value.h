//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_SORT_MAP_BY_VALUE_H
#define MZLIB_SORT_MAP_BY_VALUE_H

#include <map>
#include <algorithm>
#include "../lang/binary_options.h"

namespace mzlib {
    
// Map is already intrinsically sorted by keys, but what if you need items sorted
// by values instead?
template <class Key, class Value>
std::vector<std::pair<Key, Value>> sort_map_by_value(
   const std::map<Key,Value>& unsorted, 
   option::descending descending = option::descending::no)
{
   std::vector<std::pair<Key, Value>> result;
   
   std::copy (unsorted.begin(),unsorted.end(),std::back_inserter(result));
   
   std::sort(result.begin(), result.end(), 
      [&descending](const std::pair<Key, Value>& a, const std::pair<Key, Value>& b) 
      {
         return descending ? 
            b.second < a.second : 
            b.second > a.second;   
      });
   return result;
}

} // namespace

#endif // MZLIB_SORT_MAP_BY_VALUE_H
