//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "are_substrings.h"

#include <vector>
#include <string>

TEST(all_are_substrings_ci, they_are)
{
   std::string full_string = "The Himalayas are the crowning achievement of the Indo-Australian plate.";
   std::vector<std::string> substrings =
   {
      "The Himalayas", // first
      "crowning achievement", // middle
      "plate." // last
   };
   ASSERT_TRUE(mzlib::all_are_substrings_ci(
      full_string, substrings.begin(), substrings.end()));
}

TEST(all_are_substrings_ci, one_is_not)
{
   std::string full_string = "The Himalayas are the crowning achievement of the Indo-Australian plate.";
   std::vector<std::string> substrings =
   {
      "The Himalayas",
      "crowning achievement",
      "tectonics"
   };
   ASSERT_FALSE(mzlib::all_are_substrings_ci(
      full_string, substrings.begin(), substrings.end()));
}

TEST(all_are_substrings_ci, empty_full_string)
{
   std::string full_string;
   std::vector<std::string> substrings =
   {
      "The Himalayas",
      "crowning achievement",
      "plate"
   };
   ASSERT_FALSE(mzlib::all_are_substrings_ci(
      full_string, substrings.begin(), substrings.end()));
}

TEST(all_are_substrings_ci, empty_substrings_container)
{
   std::string full_string = "The Himalayas are the crowning achievement of the Indo-Australian plate.";
   std::vector<std::string> substrings =
   {
      /*empty*/
   };
   ASSERT_TRUE(mzlib::all_are_substrings_ci(
      full_string, substrings.begin(), substrings.end()));
}

TEST(all_are_substrings_ci, empty_substrings_in_non_empty_container)
{
   std::string full_string = "The Himalayas are the crowning achievement of the Indo-Australian plate.";
   std::vector<std::string> substrings =
   {
      "",
      ""
   };
   ASSERT_TRUE(mzlib::all_are_substrings_ci(
      full_string, substrings.begin(), substrings.end()));
}

TEST(none_are_substrings_ci, they_are_not)
{
   std::string full_string = "The Himalayas are the crowning achievement of the Indo-Australian plate.";
   std::vector<std::string> substrings =
   {
      "The Alps",
      "subduction",
      "tectonics."
   };
   ASSERT_TRUE(mzlib::none_are_substrings_ci(
      full_string, substrings.begin(), substrings.end()));
}

TEST(none_are_substrings_ci, one_is)
{
   std::string full_string = "The Himalayas are the crowning achievement of the Indo-Australian plate.";
   std::vector<std::string> substrings =
   {
      "The Alps",
      "crowning achievement",
      "tectonics"
   };
   ASSERT_FALSE(mzlib::none_are_substrings_ci(
      full_string, substrings.begin(), substrings.end()));
}

TEST(none_are_substrings_ci, empty_full_string)
{
   std::string full_string;
   std::vector<std::string> substrings =
   {
      "The Himalayas",
      "crowning achievement",
      "plate"
   };
   ASSERT_TRUE(mzlib::none_are_substrings_ci(
      full_string, substrings.begin(), substrings.end()));
}

TEST(none_are_substrings_ci, empty_substrings_container)
{
   std::string full_string = "The Himalayas are the crowning achievement of the Indo-Australian plate.";
   std::vector<std::string> substrings =
   {
      /*empty*/
   };
   ASSERT_TRUE(mzlib::none_are_substrings_ci(
      full_string, substrings.begin(), substrings.end()));
}

TEST(none_are_substrings_ci, empty_substrings_in_non_empty_container)
{
   std::string full_string = "The Himalayas are the crowning achievement of the Indo-Australian plate.";
   std::vector<std::string> substrings =
   {
      "",
      ""
   };
   ASSERT_FALSE(mzlib::none_are_substrings_ci(
      full_string, substrings.begin(), substrings.end()));
}