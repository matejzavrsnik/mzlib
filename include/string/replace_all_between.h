//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_STRING_REPLACE_ALL_BETWEEN_H
#define MZLIB_STRING_REPLACE_ALL_BETWEEN_H

#include "get_substring.h"
#include "replace.h"

namespace mzlib {

template<class T>
struct delimiting_tag
{ 
   T open;
   T close;
};

template<class T>
struct replacement
{ 
   T what;
   T with;
};
   
// Replace all occurrences of a string in a string when they occur within
// any of string delimiters
inline void string_replace_all_between (
   std::string& original, 
   const std::vector<delimiting_tag<std::string_view>>& replace_between, 
   const std::vector<replacement<std::string_view>>& replacements) 
{
   for(auto& fence : replace_between)
   {
      int which_one = 0;
      std::string_view to_fix;
      while(
         to_fix = get_substring_between(
            original, 
            fence.open, 
            fence.close, 
            which_one),
         ++which_one,
         !to_fix.empty())
      {
         std::string fixed(to_fix);
         for(auto& replace : replacements)
         {
            string_replace(fixed, replace.what, replace.with);
         }
         string_replace(original, to_fix, fixed);
      }
   }
}

} // namespace

#endif // HEADER_H
