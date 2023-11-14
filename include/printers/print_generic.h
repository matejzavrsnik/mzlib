//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#pragma once

#include "../lang/concepts.h"
#include <iostream>

namespace mzlib
{

template <mzlib::stream_outable StreamOutableType>
std::ostream&
print (
   const StreamOutableType& obj,
   std::ostream& os = std::cout
)
{
   os << obj;
   return os;
}

}
