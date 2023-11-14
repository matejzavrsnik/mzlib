//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#pragma once

#include <iostream>
#include <utility>
#include "print_parameters.h"

namespace mzlib
{

template <typename First, typename Second>
std::ostream&
print (
   const std::pair<First, Second>& p,
   const mzlib::print_parameters<std::pair<First, Second>, std::string>& params
)
{
   params.stream << "[" << p.first << "," << p.second << "]" << std::endl;
   return params.stream;
}

}
