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

#ifdef MZLIB_REMOVE_STRINGS_TESTS_H

TEST(remove_strings, which_end_with)
{
   std::vector<std::string> list;
   list.push_back("I must not fear"); 
   list.push_back("Fear is the mind-killer");
   list.push_back("Fear is the little-death that brings total obliteration");
   list.push_back("I will face my fear");
   list.push_back("I will permit it to pass over me and through me");
   
   using namespace mzlib::parameters::remove_strings_which;
   auto filtered = mzlib::remove_strings_which (list, end_with, {"mind-killer", "obliteration", "me"});
   
   auto not_found = filtered.end();
   ASSERT_EQ(2, filtered.size());
   ASSERT_NE(not_found, std::find(filtered.begin(), filtered.end(), "I must not fear"));   
   ASSERT_NE(not_found, std::find(filtered.begin(), filtered.end(), "I will face my fear"));
}

TEST(remove_strings, which_start_with)
{
   std::vector<std::string> list;
   list.push_back("I must not fear"); 
   list.push_back("Fear is the mind-killer");
   list.push_back("Fear is the little-death that brings total obliteration");
   list.push_back("I will face my fear");
   list.push_back("I will permit it to pass over me and through me");
   
   using namespace mzlib::parameters::remove_strings_which;
   auto filtered = mzlib::remove_strings_which (list, start_with, {"I must", "Fear"});
   
   auto not_found = filtered.end();
   ASSERT_EQ(2, filtered.size());
   ASSERT_NE(not_found, std::find(filtered.begin(), filtered.end(), "I will face my fear"));
   ASSERT_NE(not_found, std::find(filtered.begin(), filtered.end(), "I will permit it to pass over me and through me"));
}

TEST(remove_strings, which_dont_start_with)
{
   std::vector<std::string> list;
   list.push_back("I must not fear"); 
   list.push_back("Fear is the mind-killer");
   list.push_back("Fear is the little-death that brings total obliteration");
   list.push_back("I will face my fear");
   list.push_back("I will permit it to pass over me and through me");
   
   using namespace mzlib::parameters::remove_strings_which;
   auto filtered = mzlib::remove_strings_which_dont (list, start_with, {"I must", "Fear"});
   
   auto not_found = filtered.end();
   ASSERT_EQ(3, filtered.size());
   ASSERT_NE(not_found, std::find(filtered.begin(), filtered.end(), "I must not fear"));
   ASSERT_NE(not_found, std::find(filtered.begin(), filtered.end(), "Fear is the mind-killer")); 
   ASSERT_NE(not_found, std::find(filtered.begin(), filtered.end(), "Fear is the little-death that brings total obliteration"));
}

TEST(remove_strings, which_dont_end_with)
{
   std::vector<std::string> list;
   list.push_back("I must not fear"); 
   list.push_back("Fear is the mind-killer");
   list.push_back("Fear is the little-death that brings total obliteration");
   list.push_back("I will face my fear");
   list.push_back("I will permit it to pass over me and through me");
   
   using namespace mzlib::parameters::remove_strings_which;
   auto filtered = mzlib::remove_strings_which_dont (list, end_with, {"mind-killer", "obliteration"});
   
   auto not_found = filtered.end();
   ASSERT_EQ(2, filtered.size());
   ASSERT_NE(not_found, std::find(filtered.begin(), filtered.end(), "Fear is the mind-killer"));
   ASSERT_NE(not_found, std::find(filtered.begin(), filtered.end(), "Fear is the little-death that brings total obliteration"));
}

#endif // MZLIB_REMOVE_STRINGS_TESTS_H


