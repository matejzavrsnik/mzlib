//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_GET_IF_EXISTS_H
#define MZLIB_GET_IF_EXISTS_H

#include <optional>
#include <map>

namespace mzlib {
    
// Wrapper for finding things in maps that returns optional.
   
template<typename Key, typename Value>
const std::optional<Value> 
get_if_exists(
   const Key& what, 
   const std::map<Key, Value>& where)
{
   auto found = where.find(what);
   if (found != where.end())
   {
      return found->second;
   }
   return std::nullopt;
}

template<typename Key, typename Value>
bool
exists(
   const Key& what,
   const std::map<Key, Value>& where)
{
   return where.find(what) != where.end();
}

} // namespace

#endif // MZLIB_GET_IF_EXISTS_H
