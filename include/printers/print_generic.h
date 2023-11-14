//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#pragma once

#include "../lang/concepts.h"
#include <iostream>
#include <iomanip>

namespace mzlib
{

template <mzlib::stream_outable StreamOutableType>
std::ostream&
print (
   const StreamOutableType& obj,
   const mzlib::print_parameters<StreamOutableType, std::string>& params
)
{
   params.stream << std::setfill(' ') << std::setw(params.align);

   if (params.substitutions.contains(obj))
      params.stream << params.substitutions.at(obj);
   else
      params.stream << obj;

   return params.stream;
}

}
