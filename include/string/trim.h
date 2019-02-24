//
// Copyright (c) 2019 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_TRIM_H
#define MZLIB_TRIM_H

#include "string_view_find.h"

namespace mzlib {

template<typename StringView, typename CharGroupIdentifier>
StringView trim_from_end(
   StringView str,
   CharGroupIdentifier chars)
{
   auto last_of = rfind_first_not_of(str, chars);
   
   if (last_of != str.npos)
      str.remove_suffix(str.size()-last_of-1); 
   else
      str.remove_suffix(str.size()); 
   
   return str;
}

template<typename StringView, typename CharGroupIdentifier>
StringView trim_from_start(
   StringView str,
   CharGroupIdentifier chars)
{
   auto first_of = find_first_not_of(str, chars);
   
   if (first_of != str.npos)
      str.remove_prefix(first_of); 
   else
      str.remove_prefix(str.size()); 
   
   return str;
}

template<typename StringView, typename CharGroupIdentifier>
StringView trim(
   StringView str,
   CharGroupIdentifier chars)
{
   StringView trimmed = str;
   trimmed = trim_from_end(trimmed, chars);
   trimmed = trim_from_start(trimmed, chars);
   return trimmed;
}

} // namespace

#endif // MZLIB_TRIM_PUNCTUATION_H
