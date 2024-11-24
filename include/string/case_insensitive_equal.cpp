//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "case_insensitive_equal.h"

TEST(case_insensitive_equal, literal_equals_different_case)
{
   ASSERT_TRUE(mzlib::case_insensitive_equal('a','A'));
}

TEST(case_insensitive_equal, literal_equals_same_case)
{
   ASSERT_TRUE(mzlib::case_insensitive_equal('a','a'));
}

TEST(case_insensitive_equal, literal_doesnt_equal)
{
   ASSERT_FALSE(mzlib::case_insensitive_equal('a','B'));
}

TEST(case_insensitive_equal, from_string_equals)
{
   std::string str = "aA";
   ASSERT_TRUE(mzlib::case_insensitive_equal(str[0],str[1]));
}

TEST(case_insensitive_equal, from_string_doesnt_equal)
{
   std::string str = "aB";
   ASSERT_FALSE(mzlib::case_insensitive_equal(str[0],str[1]));
}

TEST(case_insensitive_equal, from_wstring_equals)
{
   std::wstring str = L"aA";
   ASSERT_TRUE(mzlib::case_insensitive_equal(str[0],str[1]));
}

TEST(case_insensitive_equal, from_wstring_doesnt_equal)
{
   std::wstring str = L"aB";
   ASSERT_FALSE(mzlib::case_insensitive_equal(str[0],str[1]));
}

TEST(case_insensitive_equal, from_string_view_equals)
{
   std::string_view str = "aA";
   ASSERT_TRUE(mzlib::case_insensitive_equal(str[0],str[1]));
}

TEST(case_insensitive_equal, from_string_view_doesnt_equal)
{
   std::string_view str = "aB";
   ASSERT_FALSE(mzlib::case_insensitive_equal(str[0],str[1]));
}

TEST(case_insensitive_equal, from_wstring_view_equals)
{
   std::wstring_view str = L"aA";
   ASSERT_TRUE(mzlib::case_insensitive_equal(str[0],str[1]));
}

TEST(case_insensitive_equal, from_wstring_view_doesnt_equal)
{
   std::wstring_view str = L"aB";
   ASSERT_FALSE(mzlib::case_insensitive_equal(str[0],str[1]));
}