//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef IS_WORD_IN_DICTIONARY_H
#define IS_WORD_IN_DICTIONARY_H

#include <regex>
#include <unordered_set>
#include "../lang/binary_options.h"

namespace mzlib {
   
// Pretty trivial version, still worth using for readability if nothing else.
// Fast lookup, but doesn't find partial matches.
inline mzlib::option::match is_word_in_dictionary(
   std::string_view word, 
   const std::unordered_set<std::string>& dictionary)
{  
   return dictionary.find(word.data()) != dictionary.end();
}

// where it gets slightly more complicated is when partial matches count too.

// two separate flags, because a full word can still be just a beginning of another
struct word_match {
   mzlib::option::match full_word;
   mzlib::option::match beginning;
};

// Given a dictionary defined with iterators, check if a word given either exactly 
// matches some word or if there is at least one word that begins with it.
// There are cleverer ways to do it, but at the moment it just does linear search
// until the conditions are satisfied. Worst-case complexity is linear, but on an
// upside at least the container can be pretty much anything (within reason) and 
// it doesn't need to be sorted.
template<class Iterator>
word_match is_word_in_dictionary_partial(
   std::string_view word, 
   const Iterator begin,
   const Iterator end)
{
   word_match match_result;
   // matches entries that start with word
   std::regex txt_regex ("\\b(" + std::string(word) + ")([^ ]*)");   
   uint count_matches = 0;
   Iterator current_it = begin;
   
   while(current_it != end) {
      auto match = std::regex_match(*current_it, txt_regex);
      if(match) {
         ++count_matches;
         if(!match_result.full_word && *current_it == word) {
            match_result.full_word = mzlib::option::match::yes;
         }
         if(!match_result.beginning && count_matches > 1) {
            match_result.beginning = mzlib::option::match::yes;
         }
         if(match_result.beginning && match_result.full_word) {
            break;
         }
      }
      current_it = std::next(current_it);
   }
   
   return match_result;
}
   
} // namespace

#endif /* IS_WORD_IN_DICTIONARY_H */
