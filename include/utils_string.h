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
#include <algorithm> // std::generate

#include "utilities.h" // fast_threeway_min

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

inline int wagner_fischer_distance (const std::string& str1, const std::string& str2)
{
   // Optimised version of this algorithm only needs two vectors, current and 
   // previous rows of the matrix
   std::vector<int> prev_row (str2.length()+1, 0);
   std::vector<int> curr_row (str2.length()+1, 0);
   
   int n=0;
   std::generate (curr_row.begin(), curr_row.end(), [&n]{ return n++; });
   
   // The core of the algorithm: a crazy cacophony of narrowly avoided off-by-ones
   for(size_t i = 1; i<str1.length()+1; i++) {
      // Some maintenance due to the fact there are only two lines available
      prev_row = curr_row;
      std::fill (curr_row.begin(), curr_row.end(), 0);;
      curr_row [0] = i;
      
      for(size_t j = 1; j<str2.length()+1; j++) {
         if(str1 [i-1] == str2 [j-1]) {
            curr_row [j] = prev_row [j-1];
         }
         else {
            curr_row [j] = fast_threeway_min(
               prev_row [j-1] +1, // substitution
               prev_row [j]   +1, // deletion
               curr_row [j-1] +1  // insertion
            );
         }
      }
   }

   return curr_row [curr_row.size()-1];
}

} } // namespace mzlib::util

#endif // UTILS_STRING_H

