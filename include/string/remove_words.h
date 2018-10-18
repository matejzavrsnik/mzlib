//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_REMOVE_WORDS_H
#define MZLIB_REMOVE_WORDS_H

#include "trim_nonalpha.h"

#include <string>

namespace mzlib {

inline std::string 
remove_words_beginning(std::string sentence)
{
   sentence = mzlib::trim_nonalpha_from_start(sentence);
   
   auto next_space = sentence.find_first_of(' ');
   
   // no more spaces -> at most one word -> return empty
   if (next_space == std::string::npos) return ""; 
   
   sentence.erase(0, next_space);
   
   sentence = mzlib::trim_nonalpha_from_start(sentence);
   
   return sentence;
}

} // namespace

#endif // MZLIB_REMOVE_WORDS_H
