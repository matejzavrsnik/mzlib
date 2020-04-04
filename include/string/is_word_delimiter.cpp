//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "is_word_delimiter.h"

TEST(is_word_delimiter, letter_then_delimiter)
{
   ASSERT_TRUE(mzlib::is_word_delimiter('a', ' '));
   ASSERT_TRUE(mzlib::is_word_delimiter('a', '!'));
   ASSERT_TRUE(mzlib::is_word_delimiter('a', '?'));
   ASSERT_TRUE(mzlib::is_word_delimiter('a', '.'));
   ASSERT_TRUE(mzlib::is_word_delimiter('a', ','));
   ASSERT_TRUE(mzlib::is_word_delimiter('a', ';'));
   ASSERT_TRUE(mzlib::is_word_delimiter('a', ':'));
   ASSERT_TRUE(mzlib::is_word_delimiter('a', '\"'));
   ASSERT_TRUE(mzlib::is_word_delimiter('a', '('));
   ASSERT_TRUE(mzlib::is_word_delimiter('a', ')'));
   ASSERT_TRUE(mzlib::is_word_delimiter('a', '\n'));
}

TEST(is_word_delimiter, space_then_delimiter)
{
   ASSERT_TRUE(mzlib::is_word_delimiter(' ', ' '));
   ASSERT_TRUE(mzlib::is_word_delimiter(' ', '!'));
   ASSERT_TRUE(mzlib::is_word_delimiter(' ', '?'));
   ASSERT_TRUE(mzlib::is_word_delimiter(' ', '.'));
   ASSERT_TRUE(mzlib::is_word_delimiter(' ', ','));
   ASSERT_TRUE(mzlib::is_word_delimiter(' ', ';'));
   ASSERT_TRUE(mzlib::is_word_delimiter(' ', ':'));
   ASSERT_TRUE(mzlib::is_word_delimiter(' ', '\"'));
   ASSERT_TRUE(mzlib::is_word_delimiter(' ', '('));
   ASSERT_TRUE(mzlib::is_word_delimiter(' ', ')'));
   ASSERT_TRUE(mzlib::is_word_delimiter(' ', '\n'));
}

TEST(is_word_delimiter, delimiter_then_delimiter)
{
   ASSERT_TRUE(mzlib::is_word_delimiter(',', ' '));
   ASSERT_TRUE(mzlib::is_word_delimiter(',', '!'));
   ASSERT_TRUE(mzlib::is_word_delimiter(',', '?'));
   ASSERT_TRUE(mzlib::is_word_delimiter(',', '.'));
   ASSERT_TRUE(mzlib::is_word_delimiter(',', ','));
   ASSERT_TRUE(mzlib::is_word_delimiter(',', ';'));
   ASSERT_TRUE(mzlib::is_word_delimiter(',', ':'));
   ASSERT_TRUE(mzlib::is_word_delimiter(',', '\"'));
   ASSERT_TRUE(mzlib::is_word_delimiter(',', '('));
   ASSERT_TRUE(mzlib::is_word_delimiter(',', ')'));
   ASSERT_TRUE(mzlib::is_word_delimiter(',', '\n'));
}

TEST(is_word_delimiter, hyphen)
{
   // after letter
   ASSERT_FALSE(mzlib::is_word_delimiter('a', '-'));
   // before letter
   ASSERT_FALSE(mzlib::is_word_delimiter('-', 'a'));
   // after space
   ASSERT_TRUE(mzlib::is_word_delimiter(' ', '-'));
}

TEST(is_word_delimiter, apostrophe)
{
   // after letter
   ASSERT_FALSE(mzlib::is_word_delimiter('a', '\''));
   // before letter
   ASSERT_FALSE(mzlib::is_word_delimiter('\'', 'a'));
   // after space
   ASSERT_FALSE(mzlib::is_word_delimiter(' ', '\''));
}