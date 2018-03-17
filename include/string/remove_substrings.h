//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_REMOVE_SUBSTRINGS_H
#define MZLIB_REMOVE_SUBSTRINGS_H

#include <string_view>

namespace mzlib {

inline std::string 
remove_all_occurences_of_substring(
   std::string_view full_string, 
   std::string_view substring)
{
   std::string result = full_string.data();
   
   if (full_string.length() == 0 || substring.length() == 0) 
      return result;
   
   size_t substring_start = result.find(substring);
   while (substring_start != std::string::npos) {
      result.erase(substring_start, substring.length());
      substring_start = result.find(substring);
   }
   
   return result;
}

} // namespace

#endif // MZLIB_REMOVE_SUBSTRINGS_H
