//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef UTILS_STRING_H
#define UTILS_STRING_H

#include <string>
#include <vector>

namespace mzlib {
namespace util {
        
inline std::vector<std::string> split_string_puctuation (const std::string& str) 
{
   std::vector<std::string> split_string;
   std::string new_candidate = "";
   for (std::string::const_iterator ch_it = str.begin(); ch_it != str.end(); ++ch_it) {
      char ch = *ch_it;
      if (ispunct(ch) && ch!='\'') { // as in "isn't" and such
         if (!new_candidate.empty()) {
            split_string.push_back(new_candidate);
            new_candidate = "";
         }
         std::string ch_str = "";
         ch_str += ch;
         split_string.push_back(ch_str);
      }
      else {
         new_candidate += ch;
      }
   }
   if (!new_candidate.empty()) {
      split_string.push_back(new_candidate);
   }
   return split_string;
}

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
    
} } // namespace mzlib::util

#endif // UTILS_STRING_H

