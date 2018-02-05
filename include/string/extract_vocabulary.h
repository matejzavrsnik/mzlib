//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_EXTRACT_VOCABULARY_H
#define MZLIB_EXTRACT_VOCABULARY_H

#include "trim_nonalpha.h"
#include "split_on_punctuation.h"
#include "../tools/add_to_tally.h"

namespace mzlib {

template<class InsertIt>
void extract_vocabulary(std::istream& vocab_stream, InsertIt insert_it)
{
   do {
      std::string piece;
      vocab_stream >> piece;
      std::transform(piece.begin(), piece.end(), piece.begin(), ::tolower);
      auto split_words = mzlib::split_on_puctuation(piece);
      for(auto word : split_words) {
         word = mzlib::trim_nonalpha(word);
         if (word.length() > 0) {
            *insert_it++ = word;
         }
      }
   }
   while(vocab_stream);
}

inline std::map<std::string, int> 
extract_vocabulary_with_count(std::istream& vocab_stream)
{
   std::map<std::string, int> word_tally;
   do {
      std::string piece;
      vocab_stream >> piece;
      std::transform(piece.begin(), piece.end(), piece.begin(), ::tolower);
      auto split_words = mzlib::split_on_puctuation(piece);
      for(auto word : split_words) {
         word = mzlib::trim_nonalpha(word);
         if (word.length()) {
            mzlib::add_to_tally(word_tally, word);
         }
      }
   }
   while(vocab_stream);
   return word_tally;
}

} // namespace

#endif // MZLIB_EXTRACT_VOCABULARY_H
