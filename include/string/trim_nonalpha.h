//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_TRIM_PUNCTUATION_H
#define MZLIB_TRIM_PUNCTUATION_H

#include <algorithm>

namespace mzlib {

// strips all non-letter characters from end of string
inline std::string 
trim_nonalpha_from_end(std::string_view word)
{
   auto last = std::find_if(word.rbegin(), word.rend(), isalpha);
   std::string stripped;
   if (last != word.rend()) {
      stripped.assign(word.begin(), last.base());
   }
   return stripped;
}

// strips all non-letter characters from beginning string
inline std::string 
trim_nonalpha_from_start(std::string_view word)
{
   auto first = std::find_if(word.begin(), word.end(), isalpha);
   std::string stripped;
   if (first != word.end()) {
      stripped.assign(first, word.end());
   }
   return stripped;
}

// strips all non-letter characters from beginning and end of string
inline std::string 
trim_nonalpha(std::string_view word)
{
   std::string stripped = trim_nonalpha_from_end(word);
   stripped = trim_nonalpha_from_start(stripped);
   //auto first = std::find_if(word.begin(), word.end(), isalpha);
   //auto last = std::find_if(word.rbegin(), word.rend(), isalpha);
   //std::string stripped;
   //if (first != word.end() && last != word.rend()) {
   //   stripped.assign(first, last.base());
   //}
   return stripped;
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
