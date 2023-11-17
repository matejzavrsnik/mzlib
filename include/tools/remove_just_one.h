//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//
#pragma once

#include <set>
#include <algorithm>

namespace mzlib {

// removes just one elements from multiset, which isn't a feature otherwise
template <class Type>
void
remove_just_one (
   std::multiset<Type>& window,
   const Type& element
)
{
   const auto found = std::find(window.begin(), window.end(), element);
   if (found != window.end())
      window.erase(found);
}

}
