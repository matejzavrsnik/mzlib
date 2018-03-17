//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_IS_SUBSTRING_H
#define MZLIB_IS_SUBSTRING_H

#include "case.h"
#include <string_view>

namespace mzlib {
   
inline bool is_substring(
   std::string_view full, 
   std::string_view sub)
{
   // Case sensitive version is easy.
   return (full.find(sub) != std::string_view::npos);
}

inline bool is_substring_ci(
   std::string_view full, 
   std::string_view sub)
{
   // to keep the same result as case sensitive version.
   // Also, in a way, it is a substring.
   if (sub.empty()) return true;
   
   // I don't want to create new strings just to convert read-only
   // string_views to lowercase before comparing. I can do it char 
   // by char with just a little bit of work and spend minimum 
   // extra memory as a benefit. And on some weird level I enjoy 
   // watching this too :)
   
   for(auto full_it = full.begin(); full_it != full.end(); ++full_it)
   for(auto cmp_it = full_it, sub_it = sub.begin(); cmp_it != full.end(); ++cmp_it)
      if (tolower(*cmp_it) != tolower(*sub_it)) break;
      else if (++sub_it == sub.end()) return true; // found substring
      
   return false; // didn't find substring
}

} // namespace

#endif /* MZLIB_IS_SUBSTRING_H */
