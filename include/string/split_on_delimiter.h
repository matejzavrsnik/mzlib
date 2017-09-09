//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_STRING_SPLIT_H
#define MZLIB_STRING_SPLIT_H

#include <string>
#include <vector>
#include <sstream>

namespace mzlib {

std::vector<std::string> split_on_delimiter(std::string str, char delimiter)
{
   std::string token;
   std::vector<std::string> tokens;
   std::istringstream iss(str);
   while(std::getline(iss, token, delimiter))
   {
       tokens.push_back(token);
   }
   return std::move(tokens);
}

} // namespace

#endif // MZLIB_STRING_SPLIT_H

#ifdef MZLIB_BUILDING_TESTS

#ifndef MZLIB_STRING_SPLIT_TESTS_H
#define MZLIB_STRING_SPLIT_TESTS_H



#endif // MZLIB_STRING_SPLIT_TESTS_H

#endif // MZLIB_BUILDING_TESTS
