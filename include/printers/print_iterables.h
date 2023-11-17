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
#include "print_parameters.h"

namespace mzlib
{

template <typename IterableContainer>
requires (
   // only iterable containers to be printed with this function
   mzlib::iterable<IterableContainer>
   // but don't print strings same as vectors
   && !std::same_as<std::string, IterableContainer>
)
std::ostream&
print (
   const IterableContainer& c,
   mzlib::print_parameters params = mzlib::print_parameters()
)
{
   bool first = true;
   params.stream << "[";
   for (const auto& e: c)
   {
      if (!first)
         params.stream << ",";
      first = false;
      print(e, params);
   }
   params.stream << "]" << std::endl;
   return params.stream;
}

}
