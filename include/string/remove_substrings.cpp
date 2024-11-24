//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "remove_substrings.h"

TEST(remove_all_occurences_of_substring, demo)
{
   ASSERT_EQ("", mzlib::remove_all_occurences_of_substring("", ""));
   ASSERT_EQ("", mzlib::remove_all_occurences_of_substring("aa", "aa"));
   ASSERT_EQ("bb", mzlib::remove_all_occurences_of_substring("aabb", "aa"));
   ASSERT_EQ("bb", mzlib::remove_all_occurences_of_substring("bbaa", "aa"));
   ASSERT_EQ("bb", mzlib::remove_all_occurences_of_substring("aabbaa", "aa"));
   ASSERT_EQ("bbbb", mzlib::remove_all_occurences_of_substring("bbaabb", "aa"));
   ASSERT_EQ("bbbb", mzlib::remove_all_occurences_of_substring("bbaabbaa", "aa"));
   ASSERT_EQ("bbbb", mzlib::remove_all_occurences_of_substring("aabbaabb", "aa"));
}