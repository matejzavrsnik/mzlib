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

std::vector<std::string> split_on_delimiter(std::string_view str, char delimiter)
{
   //todo: could be refactored to return vector of string_views
   std::string token;
   std::vector<std::string> tokens;
   std::istringstream iss(str.data());
   while(std::getline(iss, token, delimiter))
   {
       tokens.push_back(token);
   }
   return std::move(tokens);
}

} // namespace

#endif // MZLIB_STRING_SPLIT_H
