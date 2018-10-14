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

#include <string>
#include <optional>
#include <map>
#include <list>
#include <algorithm>

namespace mzlib {
   
class syllables
{
   
private:
   
   syllables() = default;
   
   std::map<std::string, int> m_syllables;

public:

   static syllables from_dictionary(
      std::string_view dictionary_filename, 
      char delimiter)
   {
      syllables result;
      auto dictionary_lines = mzlib::read_file_lines(dictionary_filename);
      for(std::string word : dictionary_lines)
      {
         int syllables_count = 1;
         syllables_count += std::count(word.begin(), word.end(), delimiter);
         word.erase(std::remove(word.begin(), word.end(), delimiter), word.end());
         word.erase(std::remove(word.begin(), word.end(), '\r'), word.end());
         result.m_syllables[word] = syllables_count;
      }
      return result;
   }
   
   std::optional<int> count(std::string word) const
   {
      return mzlib::get_if_exists(
         mzlib::trim_nonalpha(word), 
         m_syllables);
   }
   
   std::optional<int> count(const std::list<std::string>& sentence) const
   {
      int count = 0;
      for(const auto& word : sentence)
      {
         auto syllables = mzlib::get_if_exists(
            mzlib::trim_nonalpha(word), 
            m_syllables);
         
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
