//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_HASHABLE_SET_H
#define MZLIB_HASHABLE_SET_H

#include "hash_combine.h"

namespace std
{
   // make sets hashable
   template<typename T> struct hash<std::set<T>>
   {
      std::size_t operator()(const std::set<T>& s) const noexcept
      {
         std::size_t hash = 112358;
         std::hash<T> hasher;
         
         for(const auto& element : s)
            ::mzlib::hash_combine(hash, element);

         return hash;
      }
   };
}

#endif // MZLIB_HASHABLE_SET_H
