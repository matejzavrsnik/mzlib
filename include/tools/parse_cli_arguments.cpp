//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "parse_cli_arguments.h"

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