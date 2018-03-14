//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "is_substring.h"

TEST(is_substring, yes)
{
   ASSERT_TRUE(mzlib::is_substring(
      "Most of the people that I deal with are human.",
      "people"));
}

TEST(is_substring, no)
{
   ASSERT_FALSE(mzlib::is_substring(
      "Most of the people that I deal with are human.",
      "animals"));
}

TEST(is_substring, full_empty)
{
   ASSERT_FALSE(mzlib::is_substring(
      "",
      "people"));
}

TEST(is_substring, sub_empty)
{
   ASSERT_TRUE(mzlib::is_substring(
      "Most of the people that I deal with are human.",
      ""));
}

TEST(is_substring_ci, yes)
{
   ASSERT_TRUE(mzlib::is_substring_ci(
      "Most of the people that I deal with are human.",
      "PEOPLE"));
}

TEST(is_substring_ci, no)
{
   ASSERT_FALSE(mzlib::is_substring_ci(
      "Most of the people that I deal with are human.",
      "ANIMALS"));
}

TEST(is_substring_ci, full_empty)
{
   ASSERT_FALSE(mzlib::is_substring_ci(
      "",
      "PEOPLE"));
}

TEST(is_substring_ci, sub_empty)
{
   ASSERT_TRUE(mzlib::is_substring_ci(
      "Most of the people that I deal with are human.",
      ""));
}