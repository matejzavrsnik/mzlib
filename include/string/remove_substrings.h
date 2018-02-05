//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_REMOVE_SUBSTRINGS_H
#define MZLIB_REMOVE_SUBSTRINGS_H

namespace mzlib {

inline std::string 
remove_all_occurences_of_substring(const std::string& str, const std::string& substring)
{
   if (str.length() == 0 || substring.length() == 0) 
      return str;
   
   std::string washed = str;
   size_t substring_start;
   
   substring_start = washed.find(substring);
   
   while (substring_start != std::string::npos) {
      washed.erase(substring_start, substring.length());
      substring_start = washed.find(substring);
   }
     
   
   return washed;
}


} // namespace

#endif // MZLIB_REMOVE_SUBSTRINGS_H
