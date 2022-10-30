//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_HASH_COMBINE_H
#define MZLIB_HASH_COMBINE_H

#include <functional> // for std::hash

namespace mzlib {
   
// taken from boost
template <class T>
inline void hash_combine(std::size_t& seed, const T& v)
{
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

} // namespace

#endif // MZLIB_HASH_COMBINE_H
