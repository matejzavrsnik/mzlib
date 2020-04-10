//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_ARE_SUBSENTENCES_H
#define MZLIB_ARE_SUBSENTENCES_H

#include "is_subsentence.h"
#include "../lang/concepts.h"
#include <string_view>

namespace mzlib {
   
bool all_are_subsentences_ci(
   std::string_view str,
   const iterable subs_begin,
   const iterable subs_end)
{
   for(iterable subs_it = subs_begin; subs_it != subs_end; ++subs_it) {
      if (!is_subsentence_ci(str, *subs_it)) {
         return false;
      }
   }
   return true;
}

bool none_are_subsentences_ci(
   std::string_view str,
   const iterable subs_begin,
   const iterable subs_end)
{
   for(iterable subs_it = subs_begin; subs_it != subs_end; ++subs_it) {
      if (is_subsentence_ci(str, *subs_it)) {
         return false;
      }
   }
   return true;
}
   
} // namespace mzlib

#endif // MZLIB_ARE_SUBSENTENCES_H
