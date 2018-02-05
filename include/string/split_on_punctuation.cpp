//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "split_on_punctuation.h"

TEST(split_on_puctuation, basic) 
{
   std::string test = ",word!)";
   std::vector<std::string> result = mzlib::split_on_puctuation(test);
   ASSERT_EQ(result.size(), 4);
   ASSERT_EQ(result[0], ",");
   ASSERT_EQ(result[1], "word");
   ASSERT_EQ(result[2], "!");
   ASSERT_EQ(result[3], ")");
}

TEST(split_on_puctuation, just_one_at_the_end) 
{
   std::string test = "word.";
   std::vector<std::string> result = mzlib::split_on_puctuation(test);
   ASSERT_EQ(result.size(), 2);
   ASSERT_EQ(result[0], "word");
   ASSERT_EQ(result[1], ".");
}

TEST(split_on_puctuation, no_punctuations) 
{
   std::string test = "word";
   std::vector<std::string> result = mzlib::split_on_puctuation(test);
   ASSERT_EQ(result.size(), 1);
   ASSERT_EQ(result[0], "word");
}

TEST(split_on_puctuation, no_punctuations_at_beginning) 
{
   std::string test = "word).";
   std::vector<std::string> result = mzlib::split_on_puctuation(test);
   ASSERT_EQ(result.size(), 3);
   ASSERT_EQ(result[0], "word");
   ASSERT_EQ(result[1], ")");
   ASSERT_EQ(result[2], ".");
}

TEST(split_on_puctuation, no_punctuations_at_end) 
{
   std::string test = "\",word";
   std::vector<std::string> result = mzlib::split_on_puctuation(test);
   ASSERT_EQ(result.size(), 3);
   ASSERT_EQ(result[0], "\"");
   ASSERT_EQ(result[1], ",");
   ASSERT_EQ(result[2], "word");
}

TEST(split_on_puctuation, all_punctuations) 
{
   std::string test = "!?.,;:-\"()\n";
   std::vector<std::string> result = mzlib::split_on_puctuation(test);
   ASSERT_EQ(result.size(), 11);
   ASSERT_EQ(result[0], "!");
   ASSERT_EQ(result[1], "?");
   ASSERT_EQ(result[2], ".");
   ASSERT_EQ(result[3], ",");
   ASSERT_EQ(result[4], ";");
   ASSERT_EQ(result[5], ":");
   ASSERT_EQ(result[6], "-");
   ASSERT_EQ(result[7], "\"");
   ASSERT_EQ(result[8], "(");
   ASSERT_EQ(result[9], ")");
   ASSERT_EQ(result[10], "\n");
}

TEST(split_on_puctuation, skips_apostrophe_in_contractions) 
{
   std::string test = "isn't";
   std::vector<std::string> result = mzlib::split_on_puctuation(test);
   ASSERT_EQ(result.size(), 1);
   ASSERT_EQ(result[0], "isn't");
}

TEST(split_on_puctuation, skips_hyphen_in_compounds) 
{
   std::string test = "mind-killer";
   std::vector<std::string> result = mzlib::split_on_puctuation(test);
   ASSERT_EQ(result.size(), 1);
   ASSERT_EQ(result[0], "mind-killer");
}