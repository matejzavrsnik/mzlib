//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "../include/tools/string.h"
#include "gtest/gtest.h"

#include <set>
#include <map>
    
class fixture_tools_string : public ::testing::Test 
{

protected:

   fixture_tools_string() {}
   virtual ~fixture_tools_string() {}
   virtual void SetUp() {}
   virtual void TearDown() {}
   
};

TEST_F(fixture_tools_string, string_ends_with)
{
   std::string test_string = "Fear is the little-death that brings total obliteration.";
   ASSERT_TRUE (mzlib::string_ends_with(test_string, "obliteration."));
   ASSERT_FALSE(mzlib::string_ends_with(test_string, "bliss."));
}

TEST_F(fixture_tools_string, string_starts_with)
{
   std::string test_string = "Fear is the little-death that brings total obliteration.";
   ASSERT_TRUE (mzlib::string_starts_with(test_string, "Fear"));
   ASSERT_FALSE(mzlib::string_starts_with(test_string, "Courage"));
}

TEST_F(fixture_tools_string, remove_strings_that_end_with)
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


TEST_F(fixture_tools_string, remove_strings_that_start_with)
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

TEST_F(fixture_tools_string, remove_strings_that_dont_start_with)
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

TEST_F(fixture_tools_string, remove_strings_that_dont_end_with)
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

TEST_F(fixture_tools_string, trim_punctiation_from_start_end)
{
   ASSERT_EQ("", mzlib::trim_punctiation(""));
   ASSERT_EQ("", mzlib::trim_punctiation("."));
   ASSERT_EQ("", mzlib::trim_punctiation(".!#$%"));
   ASSERT_EQ("I must not fear", mzlib::trim_punctiation(".!#I must not fear$%")); 
   ASSERT_EQ("I must not fear", mzlib::trim_punctiation("I must not fear$%")); 
   ASSERT_EQ("I must not fear", mzlib::trim_punctiation(".!#I must not fear")); 
   ASSERT_EQ("I must not fear", mzlib::trim_punctiation("I must not fear")); 
   ASSERT_EQ("", mzlib::trim_punctiation("123"));
   ASSERT_EQ("I must not fear", mzlib::trim_punctiation("11I must not fear11")); 
}



TEST_F(fixture_tools_string, trim_punctiation_whole)
{
   std::string text(" !?I must not fear.,: Fear is the mind-killer.,* ");
   std::string trimmed = mzlib::trim_punctiation_whole(text);
   
   ASSERT_EQ("ImustnotfearFearisthemindkiller", trimmed);
}

TEST_F(fixture_tools_string, to_lowercase)
{
   std::string text("I must not fear. Fear is the mind-killer.");
   mzlib::to_lowercase(text);
   
   ASSERT_EQ("i must not fear. fear is the mind-killer.", text);
}

TEST_F(fixture_tools_string, to_uppercase)
{
   std::string text("I must not fear.");
   mzlib::to_uppercase(text);
   
   ASSERT_EQ("I MUST NOT FEAR.", text);
}