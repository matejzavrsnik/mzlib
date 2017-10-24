//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_PARSE_CLI_ARGUMENTS_H
#define MZLIB_PARSE_CLI_ARGUMENTS_H

#include <cstring>
#include <map>

namespace mzlib {

// Parses main function arguments in form of "--name=value"
inline std::map<std::string, std::string> 
parse_arguments (int argc, char const* const* argv)
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

#ifdef MZLIB_PARSE_CLI_ARGUMENTS_TESTS_H

TEST(parse_arguments, zero_arguments) 
{
   const int argc = 1;
   const char* argv[argc] = 
   {
      "program.exe"
   };
   auto arguments = mzlib::parse_arguments(argc, argv);
   ASSERT_EQ(0, arguments.size());
}

TEST(parse_arguments, one_argument) 
{
   const int argc = 2;
   const char* argv[argc] = 
   {
      "program.exe",
      "--superhero=batman"
   };
   auto arguments = mzlib::parse_arguments(argc, argv);
   ASSERT_EQ(1, arguments.size());
   ASSERT_EQ("batman", arguments["superhero"]);
}

TEST(parse_arguments, many_arguments) 
{
   const int argc = 4;
   const char* argv[argc] = 
   {
      "program.exe",
      "--superhero=batman",
      "--sidekick=robin",
      "--archvillain=joker"
   };
   auto arguments = mzlib::parse_arguments(argc, argv);
   ASSERT_EQ(3, arguments.size());
   ASSERT_EQ("batman", arguments["superhero"]);
   ASSERT_EQ("robin", arguments["sidekick"]);
   ASSERT_EQ("joker", arguments["archvillain"]);
}

#endif // MZLIB_PARSE_CLI_ARGUMENTS_TESTS_H
