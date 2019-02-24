//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_TRIM_PUNCTUATION_H
#define MZLIB_TRIM_PUNCTUATION_H

#include "string_view_find.h"

#include <algorithm>
#include <string_view>
#include <functional>

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
   
// strips all non-letter characters from end of string
inline std::string_view 
trim_nonalpha_from_end(std::string_view word)
{
   return trim_from_end(word, std::not_fn(isalpha));
}

// strips all non-letter characters from beginning string
inline std::string_view 
trim_nonalpha_from_start(std::string_view word)
{
   return trim_from_start(word, std::not_fn(isalpha));
}

// strips all non-letter characters from beginning and end of string
inline std::string_view
trim_nonalpha(std::string_view word)
{
   std::string_view trimmed = word;
   trimmed = trim_nonalpha_from_end(trimmed);
   trimmed = trim_nonalpha_from_start(trimmed);
   return trimmed;
}

// strips all non-letter characters from whole string
inline std::string 
trim_nonalpha_whole(std::string_view word)
{
   std::string trimmed;
   for(auto ch : word) {
      if(std::isalpha(ch))
         trimmed.push_back(ch);
   }
   return trimmed;
}

} // namespace

#endif // MZLIB_TRIM_PUNCTUATION_H
