//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "all_words_appear.h"

TEST(all_words_appear, all_appear)
{
   std::string in = "\"There was a button,\" Holden said. \"I pushed it.\"";
   std::string from = "There was a button,\" Holden said.";
   ASSERT_TRUE(mzlib::all_words_appear(from, in));
}

TEST(all_words_appear, not_all_appear)
{
   std::string in = "\"There was a button,\" Holden said. \"I pushed it.\"";
   std::string from = "There was a red button,\" Holden said. ";
   ASSERT_FALSE(mzlib::all_words_appear(from, in));
}

TEST(all_words_appear, equal_strings)
{
   std::string in = "\"There was a button,\" Holden said. \"I pushed it.\"";
   std::string from = "There was a button,\" Holden said. \"I pushed it.\"";
   ASSERT_TRUE(mzlib::all_words_appear(from, in));
}

TEST(all_words_appear, empty_from)
{
   std::string in = "\"There was a button,\" Holden said. \"I pushed it.\"";
   std::string from = "";
   ASSERT_TRUE(mzlib::all_words_appear(from, in));
}

TEST(all_words_appear, empty_in)
{
   std::string in = "";
   std::string from = "There was a button,\" Holden said. \"I pushed it.\"";
   ASSERT_FALSE(mzlib::all_words_appear(from, in));
}

TEST(all_words_appear, small_sets_word_appears)
{
   std::string in = "There";
   std::string from = "There";
   ASSERT_TRUE(mzlib::all_words_appear(from, in));
}

TEST(all_words_appear, small_sets_word_does_not_appear)
{
   std::string in = "There";
   std::string from = "Here";
   ASSERT_FALSE(mzlib::all_words_appear(from, in));
}

TEST(all_words_appear, custom_words_separator_all_words_appear)
{
   std::string in = "one two,three four,five six seven";
   std::string from = "three four,five six seven,one two";
   ASSERT_TRUE(mzlib::all_words_appear(from, in, ","));
}

TEST(all_words_appear, custom_words_separator_not_all_words_appear)
{
   std::string in = "one two,three four,five six seven";
   std::string from = "three four,six five seven,one two";
   ASSERT_FALSE(mzlib::all_words_appear(from, in, ","));
}