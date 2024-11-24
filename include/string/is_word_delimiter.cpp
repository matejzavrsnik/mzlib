//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "is_word_delimiter.h"

TEST(is_word_delimiter, delimiters)
{
   ASSERT_TRUE(mzlib::is_word_delimiter(' '));
   ASSERT_TRUE(mzlib::is_word_delimiter('!'));
   ASSERT_TRUE(mzlib::is_word_delimiter('?'));
   ASSERT_TRUE(mzlib::is_word_delimiter('.'));
   ASSERT_TRUE(mzlib::is_word_delimiter(','));
   ASSERT_TRUE(mzlib::is_word_delimiter(';'));
   ASSERT_TRUE(mzlib::is_word_delimiter(':'));
   ASSERT_TRUE(mzlib::is_word_delimiter('\"'));
   ASSERT_TRUE(mzlib::is_word_delimiter('('));
   ASSERT_TRUE(mzlib::is_word_delimiter(')'));
   ASSERT_TRUE(mzlib::is_word_delimiter('\n'));
}

TEST(is_word_delimiter, hyphen_and_apostrophe)
{
   ASSERT_FALSE(mzlib::is_word_delimiter('-'));
   ASSERT_FALSE(mzlib::is_word_delimiter('\''));
}
