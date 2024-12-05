//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#pragma once

#include "../lang/concepts.h"
#include <iostream>
#include <ranges>

#include "print_generic.h"
#include "print_parameters.h"

namespace mzlib
{

/*
 * Won't work with filter_view and I don't know how to fix it.
 * You can't iterate const filter_view because it caches.
 */
template <typename IterableContainer>
requires (
   // only iterable containers to be printed with this function
   mzlib::iterable<IterableContainer>
   // but don't print strings same as vectors
   && !std::same_as<std::string, IterableContainer>
   && !std::same_as<std::string_view, IterableContainer>
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
