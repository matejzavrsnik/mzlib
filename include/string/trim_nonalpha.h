//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_TRIM_PUNCTUATION_H
#define MZLIB_TRIM_PUNCTUATION_H

#include "trim.h"

#include <string_view>
#include <functional>

namespace mzlib {
   
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
   return trim(word, std::not_fn(isalpha));
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
