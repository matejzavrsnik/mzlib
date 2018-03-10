//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "split_on_delimiter.h"

TEST(split_on_delimiter, one_delimiter_space)
{
   std::string str = "My uncle Everett plays_in_a_Beatles cover band;";
   auto split = mzlib::split_on_delimiter(str, " ");
   ASSERT_EQ(6, split.size());
   ASSERT_EQ(split[0], "My");
   ASSERT_EQ(split[1], "uncle");
   ASSERT_EQ(split[2], "Everett");
   ASSERT_EQ(split[3], "plays_in_a_Beatles");
   ASSERT_EQ(split[4], "cover");
   ASSERT_EQ(split[5], "band;");
}

TEST(split_on_delimiter, one_delimiter_comma)
{
   std::string str = "My,uncle,Everett,plays in a Beatles,cover,band;";
   auto split = mzlib::split_on_delimiter(str, ",");
   ASSERT_EQ(6, split.size());
   ASSERT_EQ(split[0], "My");
   ASSERT_EQ(split[1], "uncle");
   ASSERT_EQ(split[2], "Everett");
   ASSERT_EQ(split[3], "plays in a Beatles");
   ASSERT_EQ(split[4], "cover");
   ASSERT_EQ(split[5], "band;");
}

TEST(split_on_delimiter, works_on_literals)
{
   auto split = mzlib::split_on_delimiter(
      "My uncle Everett plays_in_a_Beatles cover band;", " ");
   ASSERT_EQ(6, split.size());
   ASSERT_EQ(split[0], "My");
   ASSERT_EQ(split[1], "uncle");
   ASSERT_EQ(split[2], "Everett");
   ASSERT_EQ(split[3], "plays_in_a_Beatles");
   ASSERT_EQ(split[4], "cover");
   ASSERT_EQ(split[5], "band;");
}

TEST(split_on_delimiter, two_delimiters_space_and_comma)
{
   std::string str = "My uncle,Everett plays_in_a_Beatles,cover band;";
   auto split = mzlib::split_on_delimiter(str, " ,");
   ASSERT_EQ(6, split.size());
   ASSERT_EQ(split[0], "My");
   ASSERT_EQ(split[1], "uncle");
   ASSERT_EQ(split[2], "Everett");
   ASSERT_EQ(split[3], "plays_in_a_Beatles");
   ASSERT_EQ(split[4], "cover");
   ASSERT_EQ(split[5], "band;");
}

TEST(split_on_delimiter, two_delimiters_space_and_comma_starts_with_delimiter)
{
   std::string str = ",My uncle,Everett plays_in_a_Beatles,cover band;";
   auto split = mzlib::split_on_delimiter(str, " ,");
   ASSERT_EQ(6, split.size());
   ASSERT_EQ(split[0], "My");
   ASSERT_EQ(split[1], "uncle");
   ASSERT_EQ(split[2], "Everett");
   ASSERT_EQ(split[3], "plays_in_a_Beatles");
   ASSERT_EQ(split[4], "cover");
   ASSERT_EQ(split[5], "band;");
}

TEST(split_on_delimiter, two_delimiters_space_and_comma_end_with_delimiter)
{
   std::string str = "My uncle,Everett plays_in_a_Beatles,cover band,";
   auto split = mzlib::split_on_delimiter(str, " ,");
   ASSERT_EQ(6, split.size());
   ASSERT_EQ(split[0], "My");
   ASSERT_EQ(split[1], "uncle");
   ASSERT_EQ(split[2], "Everett");
   ASSERT_EQ(split[3], "plays_in_a_Beatles");
   ASSERT_EQ(split[4], "cover");
   ASSERT_EQ(split[5], "band");
}

TEST(split_on_delimiter, no_delimiters)
{
   std::string str = "My uncle,Everett plays_in_a_Beatles,cover band;";
   auto split = mzlib::split_on_delimiter(str, "");
   ASSERT_EQ(1, split.size());
   ASSERT_EQ(split[0], "My uncle,Everett plays_in_a_Beatles,cover band;");
}

TEST(split_on_delimiter, no_string)
{
   auto split = mzlib::split_on_delimiter("", " ,");
   ASSERT_EQ(0, split.size());
}