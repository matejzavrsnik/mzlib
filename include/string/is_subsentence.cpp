//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "is_subsentence.h"

// case sensitive, positive cases

TEST(is_subsentence, yes_empty_substring)
{
   ASSERT_TRUE(mzlib::is_subsentence(
      "Most of the people that I deal with are human",
      ""));
}

TEST(is_subsentence, yes_start_of_sentence)
{
   ASSERT_TRUE(mzlib::is_subsentence(
      "Most of the people that I deal with are human",
      "Most of"));
}

TEST(is_subsentence, yes_middle_of_sentence)
{
   ASSERT_TRUE(mzlib::is_subsentence(
      "Most of the people that I deal with are human",
      "people that"));
}

TEST(is_subsentence, yes_middle_of_sentence_with_comma_before)
{
   ASSERT_TRUE(mzlib::is_subsentence(
      "Most of the people, that I deal with, are human.",
      "that"));
}

TEST(is_subsentence, yes_middle_of_sentence_with_comma_after)
{
   ASSERT_TRUE(mzlib::is_subsentence(
      "Most of the people, that I deal with, are human.",
      "the people"));
}

TEST(is_subsentence, yes_end_of_sentence)
{
   ASSERT_TRUE(mzlib::is_subsentence(
      "Most of the people that I deal with are human",
      "are human"));
}

TEST(is_subsentence, yes_end_of_sentence_with_period)
{
   ASSERT_TRUE(mzlib::is_subsentence(
      "Most of the people that I deal with are human.",
      "are human"));
}

// case sensitive, negative cases

TEST(is_subsentence, not_found_at_all)
{
   ASSERT_FALSE(mzlib::is_subsentence(
      "Most of the people that I deal with are human",
      "The Alps"));
}

TEST(is_subsentence, no_start_of_sentence)
{
   ASSERT_FALSE(mzlib::is_subsentence(
      "Most of the people that I deal with are human",
      "Most o"));
}

TEST(is_subsentence, no_middle_of_sentence_start_not_start)
{
   ASSERT_FALSE(mzlib::is_subsentence(
      "Most of the people that I deal with are human",
      "eople that"));
}

TEST(is_subsentence, no_middle_of_sentence_end_not_end)
{
   ASSERT_FALSE(mzlib::is_subsentence(
      "Most of the people that I deal with are human",
      "people tha"));
}

TEST(is_subsentence, no_middle_of_sentence_start_not_start_with_comma_after)
{
   ASSERT_FALSE(mzlib::is_subsentence(
      "Most of the people, that I deal with, are human.",
      "eal with"));
}

TEST(is_subsentence, no_middle_of_sentence_end_not_end_with_comma_before)
{
   ASSERT_FALSE(mzlib::is_subsentence(
      "Most of the people, that I deal with, are human.",
      "that I dea"));
}

TEST(is_subsentence, no_end_of_sentence)
{
   ASSERT_FALSE(mzlib::is_subsentence(
      "Most of the people that I deal with are human",
      "re human"));
}

TEST(is_subsentence, no_end_of_sentence_with_period)
{
   ASSERT_FALSE(mzlib::is_subsentence(
      "Most of the people that I deal with are human.",
      "re human"));
}

// case insensitive, positive cases

TEST(is_subsentence_ci, yes_empty_substring)
{
   ASSERT_TRUE(mzlib::is_subsentence_ci(
      "Most of the people that I deal with are human",
      ""));
}

TEST(is_subsentence_ci, yes_start_of_sentence)
{
   ASSERT_TRUE(mzlib::is_subsentence_ci(
      "Most of the people that I deal with are human",
      "MOST OF"));
}

TEST(is_subsentence_ci, yes_middle_of_sentence)
{
   ASSERT_TRUE(mzlib::is_subsentence_ci(
      "Most of the people that I deal with are human",
      "PEOPLE THAT"));
}

TEST(is_subsentence_ci, yes_middle_of_sentence_with_comma_before)
{
   ASSERT_TRUE(mzlib::is_subsentence_ci(
      "Most of the people, that I deal with, are human.",
      "THAT"));
}

TEST(is_subsentence_ci, yes_middle_of_sentence_with_comma_after)
{
   ASSERT_TRUE(mzlib::is_subsentence_ci(
      "Most of the people, that I deal with, are human.",
      "THE PEOPLE"));
}

TEST(is_subsentence_ci, yes_end_of_sentence)
{
   ASSERT_TRUE(mzlib::is_subsentence_ci(
      "Most of the people that I deal with are human",
      "ARE HUMAN"));
}

TEST(is_subsentence_ci, yes_end_of_sentence_with_period)
{
   ASSERT_TRUE(mzlib::is_subsentence_ci(
      "Most of the people that I deal with are human.",
      "ARE HUMAN"));
}

// case insensitive, negative cases

TEST(is_subsentence_ci, not_found_at_all)
{
   ASSERT_FALSE(mzlib::is_subsentence_ci(
      "Most of the people that I deal with are human",
      "The Alps"));
}

TEST(is_subsentence_ci, no_start_of_sentence)
{
   ASSERT_FALSE(mzlib::is_subsentence_ci(
      "Most of the people that I deal with are human",
      "MOST O"));
}

TEST(is_subsentence_ci, no_middle_of_sentence_start_not_start)
{
   ASSERT_FALSE(mzlib::is_subsentence_ci(
      "Most of the people that I deal with are human",
      "EOPLE THAT"));
}

TEST(is_subsentence_ci, no_middle_of_sentence_end_not_end)
{
   ASSERT_FALSE(mzlib::is_subsentence_ci(
      "Most of the people that I deal with are human",
      "PEOPLE THA"));
}

TEST(is_subsentence_ci, no_middle_of_sentence_start_not_start_with_comma_after)
{
   ASSERT_FALSE(mzlib::is_subsentence_ci(
      "Most of the people, that I deal with, are human.",
      "EAL WITH"));
}

TEST(is_subsentence_ci, no_middle_of_sentence_end_not_end_with_comma_before)
{
   ASSERT_FALSE(mzlib::is_subsentence_ci(
      "Most of the people, that I deal with, are human.",
      "THAT I DEA"));
}

TEST(is_subsentence_ci, no_end_of_sentence)
{
   ASSERT_FALSE(mzlib::is_subsentence_ci(
      "Most of the people that I deal with are human",
      "RE HUMAN"));
}

TEST(is_subsentence_ci, no_end_of_sentence_with_period)
{
   ASSERT_FALSE(mzlib::is_subsentence_ci(
      "Most of the people that I deal with are human.",
      "RE HUMAN"));
}