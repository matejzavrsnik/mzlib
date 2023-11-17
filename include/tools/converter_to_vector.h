//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#pragma once

#include "../lang/concepts.h"
#include <vector>

namespace mzlib
{

template <
   mzlib::iterable IterableContainer,
   typename T = IterableContainer::value_type
>
std::vector<T>
to_vector (const IterableContainer& v)
{
   return std::vector<T>(v.begin(), v.end());
}

}
