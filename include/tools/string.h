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
#include <functional>

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

namespace parameters {
namespace remove_strings_which {
enum E { start_with, end_with};
}}

inline std::vector<std::string> 
remove_strings_which (const std::vector<std::string>& all_strings, parameters::remove_strings_which::E which, const std::vector<std::string>& edge_strings)
{
   using namespace parameters::remove_strings_which;
   
   std::function<bool(const std::string&, const std::string&)> deciding_function;
   if (which == start_with)
      deciding_function = string_starts_with;
   else
      deciding_function = string_ends_with;

   std::vector<std::string> filtered;
   for (const auto& full_string : all_strings) {
      bool goes_on_the_list = false;
      for (const auto& edge_string : edge_strings) 
      {
         if (deciding_function(full_string, edge_string))
         {
            goes_on_the_list = true;
            break;
         }
      }
      if(!goes_on_the_list) {
         filtered.push_back(full_string);
      }
   }
   return std::move(filtered);
}

inline std::vector<std::string> 
remove_strings_which_dont (const std::vector<std::string>& all_strings, parameters::remove_strings_which::E which, const std::vector<std::string>& edge_strings)
{
   using namespace parameters::remove_strings_which;
   
   std::function<bool(const std::string&, const std::string&)> deciding_function;
   if (which == start_with)
      deciding_function = string_starts_with;
   else
      deciding_function = string_ends_with;
   
   std::vector<std::string> filtered;
   for (const auto& full_string : all_strings) {
      bool goes_on_the_list = false;
      for (const auto& edge_string : edge_strings) 
      {
         goes_on_the_list = deciding_function(full_string, edge_string);
         if(goes_on_the_list) 
         {
            filtered.push_back(full_string);
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

