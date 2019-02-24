//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_SYLLABLES_H
#define MZLIB_SYLLABLES_H

#include "../filesystem/read_write_file.h"
#include "../tools/get_if_exists.h"
#include "../string/trim_nonalpha.h"
#include "../string/case.h"
#include "../string/split.h"

#include <string>
#include <optional>
#include <map>
#include <list>
#include <algorithm>
#include <iterator>
#include <string_view>

namespace mzlib {
   
class syllables
{
   
private:
   
   syllables() = default;
   
   std::map<std::string, int> m_syllables;

public:

   template<typename Iterator>
   static syllables from_collection(
      const Iterator begin, const Iterator end, char delimiter)
   {
      syllables result;
      for(Iterator it = begin; it != end; ++it)
      {
         auto word = *it;
         int syllables_count = 1;
         syllables_count += std::count(word.begin(), word.end(), delimiter);
         word.erase(std::remove(word.begin(), word.end(), delimiter), word.end());
         word.erase(std::remove(word.begin(), word.end(), '\r'), word.end());
         result.m_syllables[word] = syllables_count;
      }
      return result;
   }
   
   static syllables from_file (std::string_view filename, char delimiter)
   {
      const auto dictionary = mzlib::read_file_lines(filename);
      return from_collection(dictionary.begin(), dictionary.end(), delimiter);
   }
   
   std::optional<int> count_word(std::string_view word) const
   {
      auto word_str = mzlib::to_lowercase_copy<std::string>(word);
      return mzlib::get_if_exists(
         std::string{mzlib::trim_nonalpha(word_str)}, 
         m_syllables);
   }
   
   std::optional<int> count_sentence(std::string sentence) const
   {
      std::vector<std::string_view> collection = mzlib::split(sentence, " ");
      return count_collection(collection.begin(), collection.end());
   }
   
   template<typename Iterator>
   std::optional<int> count_collection(
      const Iterator begin, const Iterator end) const
   {
      int count = 0;
      for(Iterator it = begin; it != end; ++it)
      {
         auto syllables = count_word(*it);
         
         // if syllable count for this word is unknown, then 
         // syllable count for the whole sentence is not known
         if(!syllables) return std::nullopt;
         
         count += *syllables; 
      }
      return count;
   }

};

} // namespaces


#endif /* MZLIB_SYLLABLES_H */
