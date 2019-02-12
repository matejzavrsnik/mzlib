//
// Copyright (c) 2019 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_RELOCATE_H
#define MZLIB_RELOCATE_H

#include <vector>
#include <algorithm>

namespace mzlib {
    
template<class T>
void relocate(T item, std::vector<T>& from, std::vector<T>& to)
{
   to.push_back(item);
   auto it = std::find(from.begin(), from.end(), item);
   from.erase(it);
}

} // namespace

#endif // MZLIB_RELOCATE_H
