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

template <typename First, typename Second>
std::ostream&
print (
   const std::pair<First, Second>& p,
   mzlib::print_parameters params
)
{
   params.stream << "[";
   print(p.first, params) << ",";
   print(p.second, params) << "]" << std::endl;
   return params.stream;
}

}
