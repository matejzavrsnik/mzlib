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

   template<typename Iterator>
   static syllables from_collection(
      const Iterator begin,
      const Iterator end,
      char delimiter)
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
   
   static syllables from_file(
      std::string_view filename, 
      char delimiter)
   {
      const auto dictionary = mzlib::read_file_lines(filename);
      
      return from_collection(
         dictionary.begin(), 
         dictionary.end(),
         delimiter);
   }
   
   std::optional<int> count(std::string word) const
   {
      mzlib::to_lowercase_inplace(word);
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
