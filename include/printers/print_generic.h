//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#pragma once

#include "../lang/concepts.h"
#include "print_parameters.h"
#include <iostream>
#include <iomanip>

namespace mzlib
{

std::string print_to_string(const mzlib::stream_outable auto& obj)
{
   std::stringstream ss;
   ss << obj;
   return ss.str();
}

template <mzlib::stream_outable StreamOutableType>
std::ostream&
print (
   const StreamOutableType& obj,
   mzlib::print_parameters params
)
{
   std::string string_representation = print_to_string(obj);

   params.stream
      << std::setfill(' ')
      << std::setw(params.align)
      << (params.substitutions.contains(string_representation)
         ? params.substitutions.at(string_representation)
         : string_representation);

   return params.stream;
}

}
