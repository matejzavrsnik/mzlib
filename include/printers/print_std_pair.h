//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#pragma once

#include <iostream>
#include <utility>

namespace mzlib
{

template <typename First, typename Second>
std::ostream&
print (
   const std::pair<First, Second>& p,
   std::ostream& os = std::cout
)
{
   os << "[" << p.first << "," << p.second << "]" << std::endl;
   return os;
}

}
