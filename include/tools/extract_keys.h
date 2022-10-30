//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_EXTRACT_KEYS_H
#define MZLIB_EXTRACT_KEYS_H

#include <set>

namespace mzlib {

template<typename Container>
std::set<typename Container::key_type> extract_keys(const Container& container)
{
   std::set<typename Container::key_type> keys;
   for(const auto& [key, value] : container)
      keys.insert(key);
   return keys;
}


} // namespace

#endif // MZLIB_EXTRACT_KEYS_H
