//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_UTILS_STRING_H
#define MZLIB_UTILS_STRING_H

#include <string>
#include <vector>
#include <set>
#include <algorithm> // std::generate
#include <map>
#include <sstream>

#include "split_string_puctuation.h"
#include "fast_min.h" // fast_threeway_min
#include "add_to_tally.h" // add_to_tally

namespace mzlib {

// Replace all occurrences of a string in a string
inline void string_replace (std::string& str, const std::string& replace_what, const std::string& replace_with) 
{
   for (size_t pos = 0; 
        (pos = str.find(replace_what, pos)) != std::string::npos; 
        pos += replace_with.length()) 
   {
      str.replace(pos, replace_what.length(), replace_with);
   }
}
    
inline std::string get_substring_between (const std::string& str, const std::string& start, const std::string& end)
{
   std::string result;
   size_t pos_start = str.find(start)+start.length();
   size_t pos_end = str.find(end, pos_start);
   if (pos_start != std::string::npos && 
       pos_end   != std::string::npos) 
   {
      if (pos_end < pos_start) {
         std::swap(pos_start, pos_end);
      }
      result = str.substr(pos_start, pos_end-pos_start);
   }
   return result;
}
    
    
// Change a string into one that is suitable for filename
inline std::string filenamearise (const std::string& filename_candidate, char space_ch)
{
   std::string filenamearised = "";
   for (auto letter : filename_candidate) {
      if (std::isspace(letter) && filenamearised.back() != space_ch) {
         filenamearised += space_ch;
      }
      else if (std::isalnum(letter)) {
         filenamearised += std::tolower(letter);
      }
   }
   return filenamearised;
}

inline std::string extract_filename_from_path (std::string path)
{
   size_t pos = path.find_last_of("/\\");
   if (pos == std::string::npos) return "";
   return path.substr(pos+1, path.length()-pos);
}    

inline bool string_ends_with (const std::string& str, const std::string& end) {
   if (str.length() >= end.length()) {
      const int comparisson = str.compare (str.length() - end.length(), end.length(), end);
      return (comparisson == 0);
   }
   else {
      return false;
   }
}

inline bool string_starts_with (const std::string& str, const std::string& start) {
   if (str.length() >= start.length()) {
      const int comparisson = str.compare (0, start.length(), start);
      return (comparisson == 0);
   }
   else {
      return false;
   }
}

inline std::vector<std::string> 
remove_strings_that_end_with (const std::vector<std::string>& all_str, const std::vector<std::string>& ends)
{
   std::vector<std::string> filtered;
   for (const auto& str : all_str) {
      bool is_on_the_list = false;
      for (const auto& end : ends) {
         if (string_ends_with(str, end)) {
            is_on_the_list = true;
            break;
         }
      }
      if(!is_on_the_list) {
         filtered.push_back(str);
      }
   }
   return std::move(filtered);
}

inline std::vector<std::string> 
remove_strings_that_start_with (const std::vector<std::string>& all_str, const std::vector<std::string>& starts)
{
   std::vector<std::string> filtered;
   for (const auto& str : all_str) {
      bool is_on_the_list = false;
      for (const auto& start : starts) {
         if (string_starts_with(str, start)) {
            is_on_the_list = true;
            break;
         }
      }
      if(!is_on_the_list) {
         filtered.push_back(str);
      }
   }
   return std::move(filtered);
}

inline std::vector<std::string> 
remove_strings_that_dont_start_with (const std::vector<std::string>& all_str, const std::vector<std::string>& ends)
{
   std::vector<std::string> filtered;
   for (const auto& str : all_str) {
      bool is_on_the_list = false;
      for (const auto& end : ends) {
         is_on_the_list = string_starts_with(str, end);
         if(is_on_the_list) {
            filtered.push_back(str);
            break;
         }
      }
   }
   return std::move(filtered);
}

inline std::vector<std::string> 
remove_strings_that_dont_end_with (const std::vector<std::string>& all_str, const std::vector<std::string>& ends)
{
   std::vector<std::string> filtered;
   for (const auto& str : all_str) {
      bool is_on_the_list = false;
      for (const auto& end : ends) {
         is_on_the_list = string_ends_with(str, end);
         if(is_on_the_list) {
            filtered.push_back(str);
            break;
         }
      }
   }
   return std::move(filtered);
}

// strips all non-letter characters from beginning and end of string
inline std::string 
trim_punctiation(const std::string& word)
{
   auto first = std::find_if(word.begin(), word.end(), isalpha);
   auto last = std::find_if(word.rbegin(), word.rend(), isalpha);
   std::string stripped;
   if (first != word.end() && last  != word.rend()) {
      stripped.assign(first, last.base());
   }
   return stripped;
}

// strips all non-letter characters from whole string
inline std::string 
trim_punctiation_whole(const std::string& word)
{
   std::string trimmed;
   for(auto ch : word) {
      if(std::isalpha(ch))
         trimmed.push_back(ch);
   }
   return trimmed;
}

template<class InsertIt>
void extract_vocabulary(std::istream& vocab_stream, InsertIt insert_it)
{
   do {
      std::string piece;
      vocab_stream >> piece;
      std::transform(piece.begin(), piece.end(), piece.begin(), ::tolower);
      auto split_words = mzlib::split_string_puctuation(piece);
      for(auto word : split_words) {
         word = mzlib::trim_punctiation(word);
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
      auto split_words = mzlib::split_string_puctuation(piece);
      for(auto word : split_words) {
         word = mzlib::trim_punctiation(word);
         if (word.length()) {
            mzlib::add_to_tally(word_tally, word);
         }
      }
   }
   while(vocab_stream);
   return word_tally;
}

inline void to_lowercase(std::string& str)
{
   std::transform(str.begin(), str.end(), str.begin(), 
      [](unsigned char c) { 
         return std::tolower(c); 
      });
}

inline void to_uppercase(std::string& str)
{
   std::transform(str.begin(), str.end(), str.begin(), 
      [](unsigned char c) { 
         return std::toupper(c); 
      });
}

} // namespace

#endif /* MZLIB_UTILS_STRING_H */

