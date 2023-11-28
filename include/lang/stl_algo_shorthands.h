//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#pragma once

#include <algorithm>

namespace mzlib
{

// short-hand
template <typename Container, typename Operation>
void
transform (
   Container& c,
   Operation op
)
{
   std::transform(c.begin(), c.end(), c.begin(), op);
}

}
