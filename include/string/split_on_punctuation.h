//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_SPLIT_STRING_PUNCTUATION_H
#define MZLIB_SPLIT_STRING_PUNCTUATION_H

#include "is_word_delimiter.h"

#include <string>
#include <vector>

namespace mzlib {
        
inline std::vector<std::string> split_on_puctuation (std::string_view str) 
{
   std::vector<std::string> split_string;
   std::string new_candidate = "";
   char ch_prev = 0;
   for (auto ch_it = str.begin(); ch_it != str.end(); ++ch_it) {
      char ch = *ch_it;
      if ( !is_word_delimiter(ch_prev, ch) )
      {
         new_candidate += ch;
      }
      else
      {
         if (!new_candidate.empty()) {
            split_string.push_back(new_candidate);
            new_candidate = "";
         }
         std::string ch_str = "";
         ch_str += ch;
         split_string.push_back(ch_str);
      }
      ch_prev = ch;
   }
   if (!new_candidate.empty()) {
      split_string.push_back(new_candidate);
   }
   return split_string;
}

} // namespace

#endif // MZLIB_SPLIT_STRING_PUNCTUATION_H
