//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "extract_vocabulary.h"

TEST(extract_vocabulary, demo)
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

TEST(extract_vocabulary, another_type_of_container)
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

TEST(extract_vocabulary, empty_stream)
{
   std::istringstream text("");
   std::set<std::string> words;
   mzlib::extract_vocabulary(text, std::inserter(words, words.end()));
   
   ASSERT_EQ(0, words.size());
}

TEST(extract_vocabulary_with_count, demo)
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

TEST(extract_vocabulary_with_count, empty_stream)
{
   std::istringstream text("");
   std::map<std::string, int> words = mzlib::extract_vocabulary_with_count(text);
   
   ASSERT_EQ(0, words.size());
}