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
   
   auto filtered = mzlib::remove_strings_that_end_with (list, {"mind-killer", "obliteration", "me"});
   
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
   
   auto filtered = mzlib::remove_strings_that_start_with (list, {"I must", "Fear"});
   
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
   
   auto filtered = mzlib::remove_strings_that_dont_start_with (list, {"I must", "Fear"});
   
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
   
   auto filtered = mzlib::remove_strings_that_dont_end_with (list, {"mind-killer", "obliteration"});
   
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

TEST_F(fixture_tools_string, extract_vocabulary_demo)
{
   std::istringstream text("I must not fear.Fear is the mind-killer.");
   std::set<std::string> words;
   mzlib::extract_vocabulary(text, std::inserter(words, words.begin()));
   
   // There were 8 words in the sentence but just 7 unique.
   // If used with set, only unique will be stored.
   ASSERT_EQ(7, words.size());
   ASSERT_NE(words.end(), words.find("i"));
   ASSERT_NE(words.end(), words.find("must"));
   ASSERT_NE(words.end(), words.find("not"));
   ASSERT_NE(words.end(), words.find("fear"));
   ASSERT_NE(words.end(), words.find("is"));
   ASSERT_NE(words.end(), words.find("the"));
   ASSERT_NE(words.end(), words.find("mind-killer"));
}

TEST_F(fixture_tools_string, extract_vocabulary_another_type_of_container)
{
   std::istringstream text("I must not fear.Fear is the mind-killer.");
   std::vector<std::string> words;
   mzlib::extract_vocabulary(text, std::inserter(words, words.end()));
   
   // There were 8 words in the sentence but just 7 unique.
   // If used with vector, duplicate will appear
   ASSERT_EQ(8, words.size());
   ASSERT_NE(words.end(), std::find (words.begin(), words.end(), "i"));
   ASSERT_NE(words.end(), std::find (words.begin(), words.end(), "must"));
   ASSERT_NE(words.end(), std::find (words.begin(), words.end(), "not"));
   ASSERT_NE(words.end(), std::find (words.begin(), words.end(), "fear"));
   ASSERT_NE(words.end(), std::find (words.begin(), words.end(), "is"));
   ASSERT_NE(words.end(), std::find (words.begin(), words.end(), "the"));
   ASSERT_NE(words.end(), std::find (words.begin(), words.end(), "mind-killer"));
}

TEST_F(fixture_tools_string, extract_vocabulary_empty_stream)
{
   std::istringstream text("");
   std::set<std::string> words;
   mzlib::extract_vocabulary(text, std::inserter(words, words.end()));
   
   ASSERT_EQ(0, words.size());
}

TEST_F(fixture_tools_string, extract_vocabulary_with_count_demo)
{
   std::istringstream text("I must not fear.Fear is the mind-killer.");
   std::map<std::string, int> words = mzlib::extract_vocabulary_with_count(text);
   
   // There were 8 words in the sentence but just 7 unique.
   // It recognised dot at the end of first sentence is not part of a word.
   ASSERT_EQ(7, words.size());
   ASSERT_NE(words.end(), words.find("i"));
   ASSERT_NE(words.end(), words.find("must"));
   ASSERT_NE(words.end(), words.find("not"));
   ASSERT_NE(words.end(), words.find("fear"));
   ASSERT_NE(words.end(), words.find("is"));
   ASSERT_NE(words.end(), words.find("the"));
   ASSERT_NE(words.end(), words.find("mind-killer"));
   ASSERT_EQ(2, words["fear"]); // word "fear" appears twice
}

TEST_F(fixture_tools_string, extract_vocabulary_with_count_empty_stream)
{
   std::istringstream text("");
   std::map<std::string, int> words = mzlib::extract_vocabulary_with_count(text);
   
   ASSERT_EQ(0, words.size());
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