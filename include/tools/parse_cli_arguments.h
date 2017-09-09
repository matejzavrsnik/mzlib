//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_PARSE_CLI_ARGUMENTS_H
#define MZLIB_PARSE_CLI_ARGUMENTS_H

#include <cstring>

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

} // namespace

#endif // MZLIB_PARSE_CLI_ARGUMENTS_H

#ifdef MZLIB_BUILDING_TESTS

#ifndef MZLIB_PARSE_CLI_ARGUMENTS_TESTS_H
#define MZLIB_PARSE_CLI_ARGUMENTS_TESTS_H

// No tests yet

#endif // MZLIB_PARSE_CLI_ARGUMENTS_TESTS_H

#endif // MZLIB_BUILDING_TESTS

