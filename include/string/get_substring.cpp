//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "get_substring.h"

TEST(get_substring_between, demo)
{
   auto res = mzlib::get_substring_between(
      "value=bajillion;",
      "value=", ";");
   ASSERT_EQ("bajillion", res);
}

TEST(get_substring_between, start_missing)
{
   auto res = mzlib::get_substring_between(
      "bajillion;",
      "value=", ";");
   ASSERT_EQ("", res);
}

TEST(get_substring_between, end_missing)
{
   auto res = mzlib::get_substring_between(
      "value=bajillion",
      "value=", ";");
   ASSERT_EQ("", res);
}

TEST(get_substring_between, start_and_end_missing)
{
   auto res = mzlib::get_substring_between(
      "bajillion",
      "value=", ";");
   ASSERT_EQ("", res);
}

TEST(get_substring_between, empty_source_str)
{
   auto res = mzlib::get_substring_between(
      "",
      "value=", ";");
   ASSERT_EQ("", res);
}

TEST(get_substring_between, empty_start_str)
{
   auto res = mzlib::get_substring_between(
      "value=bajillion",
      "", ";");
   ASSERT_EQ("", res);
}

TEST(get_substring_between, empty_end_str)
{
   auto res = mzlib::get_substring_between(
      "value=bajillion",
      "value=", "");
   ASSERT_EQ("", res);
}