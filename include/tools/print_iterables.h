//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#pragma once

#include "../lang/concepts.h"
#include <iostream>
#include "print_generic.h"

namespace mzlib
{

template <mzlib::iterable IterableContainer>
std::ostream&
print (
   const IterableContainer& c,
   std::ostream& os = std::cout
)
{
   bool first = true;
   os << "[";
   for (const auto& e: c)
   {
      if (!first)
         os << ",";
      else
         first = false;
      print(e, os);
   }
   os << "]" << std::endl;
   return os;
}

}