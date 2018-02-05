//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "remove_strings.h"

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