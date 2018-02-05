//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_REMOVE_STRINGS_H
#define MZLIB_REMOVE_STRINGS_H

#include "string_start_end.h"
#include <functional>

namespace mzlib {

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

} // namespace

#endif // MZLIB_REMOVE_STRINGS_H
