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
#include <string_view>
#include <vector>

namespace mzlib {

inline std::vector<std::string_view> split(
   std::string_view str, 
   std::string_view delimiters)
{
   if (str.empty()) return std::vector<std::string_view>();

   std::vector<std::string_view> tokens;
   size_t size = str.size();
   size_t begin = 0;
   
   do {
      size_t end = str.find_first_of(delimiters, begin);
      if(end == begin) {
         // Delimiter immediately found; skip this char.
         ++begin;
         continue;
      }
      else if(end == std::string_view::npos) {
         // No more delimiters; need to collect all until end of string
         end = size;
      }
      // Why isn't there a substr that operates on iterators??
      std::string_view new_token = str.substr(begin, end-begin);
      tokens.push_back(new_token);
      begin = end+1;
   }
   while(begin < size);
   
   return tokens;
}

} // namespace

#endif // MZLIB_STRING_SPLIT_H
