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

namespace internal
{

template <mzlib::iterable IterableContainer, typename ElementType>
std::ostream&
print_impl (
   const IterableContainer& c,
   const mzlib::print_parameters<ElementType, std::string>& params
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

// The only reason for above is that I couldn't find other way to specify the template for mzlib::print_parameters.
// When non-nested iterator, the element type is Container::value_type.
// When nested iterator, the element type is Container::value_type::value_type.
// Other than that it's the same code, hense two equivalent calls to internal::print_impl.
template <mzlib::nonnested_iterable IterableContainer>
std::ostream&
print (
   const IterableContainer& c,
   const mzlib::print_parameters<typename IterableContainer::value_type, std::string>& p
)
{
   return internal::print_impl(c, p);
}

template <mzlib::nested_iterable IterableContainer>
std::ostream&
print (
   const IterableContainer& c,
   const mzlib::print_parameters<typename IterableContainer::value_type::value_type, std::string>& p
)
{
   return internal::print_impl(c, p);
}

}