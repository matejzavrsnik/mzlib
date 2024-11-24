//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#pragma once

#include <string>

namespace mzlib
{

inline int
binary_string_to_int (
   const std::string& s
)
{
   int result = 0;
   for (int bit_value = 1, i = s.size() - 1; i >= 0; --i, bit_value *= 2)
      if (s[i] == '1')
         result += bit_value;

   return result;
}

}
