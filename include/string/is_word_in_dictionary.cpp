//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "is_word_in_dictionary.h"

TEST(is_word_in_dictionary, basic)
{
   std::unordered_set<std::string> dictionary;
   dictionary.insert("upward");
   dictionary.insert("northward");
   
   ASSERT_TRUE(mzlib::is_word_in_dictionary("upward", dictionary));
   ASSERT_FALSE(mzlib::is_word_in_dictionary("downward", dictionary));
}

TEST(is_word_in_dictionary_partial, no_matches)
{
   std::vector<std::string> dictionary = {"upward", "not", "northward"};
   
   auto res = mzlib::is_word_in_dictionary_partial("space", dictionary.begin(), dictionary.end());
   
   ASSERT_FALSE(res.full_word);
   ASSERT_FALSE(res.beginning);
}

TEST(is_word_in_dictionary_partial, exact_match)
{
   std::vector<std::string> dictionary = {"upward", "not", "northward"};
   
   auto res = mzlib::is_word_in_dictionary_partial("upward", dictionary.begin(), dictionary.end());
   
   ASSERT_TRUE (res.full_word);
   ASSERT_FALSE(res.beginning);
}

TEST(is_word_in_dictionary_partial, start_of_word_match)
{
   std::vector<std::string> dictionary = {"upward", "not", "northward"};
   
   auto res = mzlib::is_word_in_dictionary_partial("no", dictionary.begin(), dictionary.end());
   
   ASSERT_FALSE(res.full_word);
   ASSERT_TRUE (res.beginning);
}

TEST(is_word_in_dictionary_partial, exact_and_start_of_word_match)
{
   std::vector<std::string> dictionary = {"up", "upward", "not", "northward"};
   
   auto res = mzlib::is_word_in_dictionary_partial("up", dictionary.begin(), dictionary.end());
   
   ASSERT_TRUE(res.full_word);
   ASSERT_TRUE(res.beginning);
}