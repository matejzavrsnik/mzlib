//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "remove_words.h"

TEST(remove_words, remove_words_beginning)
{
   std::string left = mzlib::remove_words_beginning("first second third");
   ASSERT_EQ("second third", left);
}

TEST(remove_words, remove_words_beginning_one_word)
{
   std::string left = mzlib::remove_words_beginning("first");
   ASSERT_TRUE(left.empty());
}

TEST(remove_words, remove_words_beginning_empty)
{
   std::string left = mzlib::remove_words_beginning("");
   ASSERT_TRUE(left.empty());
}
