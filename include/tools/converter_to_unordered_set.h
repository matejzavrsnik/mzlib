//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#pragma once

#include "../lang/concepts.h"
#include <unordered_set>

namespace mzlib
{

// I give up on making this fully generic :(

template <
   mzlib::iterable IterableContainer,
   typename T = IterableContainer::value_type
>
std::unordered_set<T>
to_unordered_set (const IterableContainer& v)
{
   return std::unordered_set<T>(v.begin(), v.end());
}

}
