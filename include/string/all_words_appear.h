//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_ALL_WORDS_APPEAR_H
#define MZLIB_ALL_WORDS_APPEAR_H

#include "split.h"
#include "trim_nonalpha.h"
#include <algorithm>
#include <string>

namespace mzlib {

inline bool all_words_appear(std::string_view from, std::string_view in)
{
   const std::string_view punctuation_marks = " .,!?:;\"-()[]";
   
   auto split_from = split(from, punctuation_marks);
   std::sort(split_from.begin(), split_from.end());
   
   auto  split_in = split(in, punctuation_marks);
   std::sort(split_in.begin(), split_in.end());
   
   bool appear = std::includes(
      split_in.begin(), split_in.end(),
      split_from.begin(), split_from.end());
   
   return appear;
}

} // namespace

#endif // MZLIB_ALL_WORDS_APPEAR_H
