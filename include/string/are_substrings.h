//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_ARE_SUBSTRINGS_H
#define MZLIB_ARE_SUBSTRINGS_H

#include "is_substring.h"
#include <string_view>

namespace mzlib {
   
template<class Iterator>
bool all_are_substrings_ci(
   std::string_view str,
   const Iterator subs_begin,
   const Iterator subs_end)
{
   for(Iterator subs_it = subs_begin; subs_it != subs_end; ++subs_it) {
      if (!is_substring_ci(str, *subs_it)) {
         return false;
      }
   }
   return true;
}

template<class Iterator>
bool none_are_substrings_ci(
   std::string_view str,
   const Iterator subs_begin,
   const Iterator subs_end)
{
   for(Iterator subs_it = subs_begin; subs_it != subs_end; ++subs_it) {
      if (is_substring_ci(str, *subs_it)) {
         return false;
      }
   }
   return true;
}
   
} // namespace mzlib

#endif // MZLIB_ARE_SUBSTRINGS_H
