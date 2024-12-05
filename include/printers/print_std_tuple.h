//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#pragma once

#include <iostream>
#include <utility>
#include "print_iterables.h"

namespace mzlib
{

template <typename... TupleArgs>
std::ostream&
print (
   const std::tuple<TupleArgs...>& tpl,
   mzlib::print_parameters params = mzlib::print_parameters()
)
{
   params.stream << "[";
   std::apply([&params](auto&&... element){((print(element, params) << ","), ...);}, tpl);
   params.stream << "]" << std::endl;
   return params.stream;
}

}
