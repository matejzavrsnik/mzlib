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
   const std::tuple<First, Second>& p,
   mzlib::print_parameters params = mzlib::print_parameters()
)
{
   params.stream << "[";
   print(std::get<0>(p), params) << ",";
   print(std::get<1>(p), params) << "]" << std::endl;
   return params.stream;
}

}
