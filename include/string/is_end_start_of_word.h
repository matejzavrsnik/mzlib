//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_IS_END_START_OF_WORD_H
#define MZLIB_IS_END_START_OF_WORD_H

#include "is_word_delimiter.h"

#include <string_view>

namespace mzlib {
  
inline bool is_start_of_word(
   std::string_view::iterator location,
   std::string_view::iterator full_begin,
   std::string_view::iterator full_end)
{
   // start of string is a start of word,
   if (location == full_begin) return true;
   
   // end of string can't be start of word
   if (location >= full_end) return false;
   
   // middle of string: if previous is a delimiter
   if (is_word_delimiter(*std::prev(location))) return true;
   
   return false;
}

inline bool is_end_of_word(
   std::string_view::iterator location,
   std::string_view::iterator full_begin,
   std::string_view::iterator full_end)
{
   // start of string can't be an end of word,
   if (location == full_begin) return false;

   // end of string is an end of word
   if (location == std::prev(full_end)) return true;
   
   // error case: beyond the end can't be end of word, a case where not found == end()
   if (location == full_end) return false;
   
   // middle of string: if next is a delimiter
   if (is_word_delimiter(*std::next(location))) return true;
   
   return false;
}

inline bool is_start_of_word(
   const std::string_view::size_type location,
   std::string_view full_string)
{
   // start of string is a start of word,
   if (location == 0) return true;
   
   // end of string (and beyond) can't be start of word
   if (location >= full_string.size()-1) return false;

   // middle of string: if previous is a delimiter
   if (is_word_delimiter(full_string[location-1])) return true;
   
   return false;
}

inline bool is_end_of_word(
   const std::string_view::size_type location,
   std::string_view full_string)
{
   // start of string can't be an end of word,
   if (location == 0) return false;
   
   // end of string is an end of word
   if (location == full_string.size()-1) return true;

   // error case: location larger than string can't be end of word
   if (location > full_string.size()) return false;
   
   // middle of string: if next is a delimiter
   if (is_word_delimiter(full_string[location+1])) return true;
   
   return false;
}

} // namespace

#endif /* MZLIB_IS_END_START_OF_WORD_H */
