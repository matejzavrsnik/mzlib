//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#pragma once

#include <map>
#include <iostream>

namespace mzlib
{

struct print_parameters
{
   int align = 0;
   std::ostream& stream = std::cout;
   std::map<std::string,std::string> substitutions = {};
};

}
