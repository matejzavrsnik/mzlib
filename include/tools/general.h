//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_UTILITIES_H
#define MZLIB_UTILITIES_H

#include <string>
#include <iomanip> // std::setprecision
#include <sstream>
#include <vector>
#include <functional> // std::function
#include <limits> // std::numeric_limits
#include <algorithm> // std::find
#include <map>
#include <cstring>
#include <numeric> // std::accumulate
#include <cassert>
#include <unordered_set>

#include "../lang/binary_options.h"
#include "../nature/vector.h"
#include "../lang/exceptions.h"
#include "../lang/optional.h"
#include "iterator_distance_comparison.h"
#include "conditional_find_iterator.h"

namespace mzlib {
    
// Parses main function arguments in form of "--name=value"
inline std::map<std::string, std::string> 
parse_arguments (int argc, char **argv)
{
   std::map<std::string, std::string> arguments;
   if (argc>1) // 0 is executable name
   {
      for (int index = 1; index < argc; ++index)
      {
         if(strncmp(argv[index], "--", 2) == 0)
         {
            const char* name_start = argv[index] + 2;
            size_t name_size = strchr(name_start, '=') - name_start;
            const char* value_start = name_start + name_size + 1;
            size_t value_size = strlen(value_start);
            std::string name(name_start, name_size);
            std::string value(value_start, value_size);
            arguments[name] = value;
         }
      }
   }
   return arguments;
}

// All things considered, this is not a bad way to implement naive factorial
// that only uses C++ built-in data types, because there is no easy way to return
// result for inputs larger then 20. Can't wait for this to come up as some 
// interview question; I want to see their faces when I implement it like this :)
// Also an example of the function that really is too simple to warrant unit testing.
inline constexpr unsigned long long int 
factorial(unsigned short number)
{
   switch(number)
   {
      case 0:  return 0;
      case 1:  return 1;
      case 2:  return 2;
      case 3:  return 6;
      case 4:  return 24;
      case 5:  return 120;
      case 6:  return 720;
      case 7:  return 5040;
      case 8:  return 40320;
      case 9:  return 362880;
      case 10: return 3628800;
      case 11: return 39916800;
      case 12: return 479001600;
      case 13: return 6227020800;
      case 14: return 87178291200;
      case 15: return 1307674368000;
      case 16: return 20922789888000;
      case 17: return 355687428096000;
      case 18: return 6402373705728000;
      case 19: return 121645100408832000;
      case 20: return 2432902008176640000;
      default: throw exception::out_of_range("Input too big.");
   }
}











} // namespace

#endif /* MZLIB_UTILITIES_H */

