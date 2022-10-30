//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_IS_SUBSENTENCE_H
#define MZLIB_IS_SUBSENTENCE_H

#include "is_end_start_of_word.h"
#include "case_insensitive_equal.h"
#include "../iterators/contains_range.h"

#include <string_view>

namespace mzlib {
  
// Like substring has same sequence of chars as full string, subsentence has same
// sequence of words as full sentence. This function confirmes that string_view is
// not only substring, but also subsentence.
inline bool is_subsentence(
   std::string_view full, 
   std::string_view sub)
{
   if (sub.empty()) return true;
   if (full.empty()) return false;
   
   const auto substring_start = full.find(sub);
           
   return is_start_of_word(substring_start, full) &&
          is_end_of_word(substring_start + sub.size()-1, full);
}

// case insensitive version
inline bool is_subsentence_ci(
   std::string_view full, 
   std::string_view sub)
{
   if (sub.empty()) return true;
   if (full.empty()) return false;
   
   const auto& substring_start = mzlib::contains_range(
      full.begin(), full.end(),
      sub.begin(), sub.end(),
      mzlib::case_insensitive_equal<std::string_view::value_type>);
   
   return is_start_of_word(substring_start, full.begin(), full.end()) &&
          is_end_of_word(substring_start + sub.size()-1, full.begin(), full.end());
}

} // namespace

#endif /* MZLIB_IS_SUBSENTENCE_H */
