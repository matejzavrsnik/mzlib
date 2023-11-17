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

template <
   template<typename T> typename Container,
   mzlib::iterable IterableContainer,
   typename T = typename IterableContainer::value_type
>
requires (
   !std::is_same<Container<T>, IterableContainer>() // fail compilation if same containers
)
Container<T>
to (const IterableContainer& v)
{
   return Container<T>(v.begin(), v.end());
}

}
