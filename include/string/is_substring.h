//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_IS_SUBSTRING_H
#define MZLIB_IS_SUBSTRING_H

#include "case.h"
#include "case_insensitive_equal.h"
#include "is_word_delimiter.h"
#include "../iterators/contains_range.h"

#include <string_view>

namespace mzlib {
  
inline bool is_substring(
   std::string_view full, 
   std::string_view sub)
{
   // Case sensitive version is worth keeping this way. Using my is_substring
   // implementation that works on general iterators is 4x slower and doesn't
   // produce any beneficial side effects.
   return (full.find(sub) != std::string_view::npos);
}

inline bool is_substring_ci(
   std::string_view full, 
   std::string_view sub)
{
   // I don't want to create new strings just to convert read-only
   // string_views to lowercase before comparing. I can do it char 
   // by char with just a little bit of work and spend minimum 
   // extra memory as a benefit.
   
   // Measurements show it's still at least twice slower than creating temp
   // std::strings, make them lower case, and find substring with .find,
   // but it does at least save on memory.
   
   const auto& range_start_it = mzlib::contains_range(
      full.begin(), full.end(),
      sub.begin(), sub.end(),
      mzlib::case_insensitive_equal<std::string_view::value_type>);
   
   return range_start_it != full.end();
}

} // namespace

#endif /* MZLIB_IS_SUBSTRING_H */
