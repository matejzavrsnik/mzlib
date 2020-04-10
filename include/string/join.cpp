//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "join.h"

#include <string>
#include <vector>
#include <set>

TEST(join, vector_delimiter_space)
{
   std::vector<std::string> tokens{"a", "b", "c", "d"};
   ASSERT_EQ("a b c d", mzlib::join(tokens, " "));
}

TEST(join, vector_delimiter_dash)
{
   std::vector<std::string> tokens{"a", "b", "c", "d"};
   ASSERT_EQ("a-b-c-d", mzlib::join(tokens, "-"));
}

TEST(join, vector_delimiter_empty)
{
   std::vector<std::string> tokens{"a", "b", "c", "d"};
   ASSERT_EQ("abcd", mzlib::join(tokens, ""));
}

TEST(join, empty_vector_delimiter_dash)
{
   std::vector<std::string> tokens{};
   ASSERT_EQ("", mzlib::join(tokens, "-"));
}

TEST(join, vector_of_stringviews_delimiter_dash)
{
   std::vector<std::string_view> tokens{"a", "b", "c", "d"};
   ASSERT_EQ("a-b-c-d", mzlib::join(tokens, "-"));
}

TEST(join, vector_of_stringviews_delimiter_char_dash)
{
   std::vector<std::string_view> tokens{"a", "b", "c", "d"};
   ASSERT_EQ("a-b-c-d", mzlib::join(tokens, '-'));
}

TEST(join, set_of_stringviews_delimiter_char_dash)
{
   std::set<std::string_view> tokens{"a", "b", "c", "d"};
   ASSERT_EQ("a-b-c-d", mzlib::join(tokens, '-'));
}

TEST(join, set_of_wstrings_delimiter_char_dash)
{
   std::set<std::wstring> tokens{L"a", L"b", L"c", L"d"};
   ASSERT_EQ(L"a-b-c-d", mzlib::wjoin(tokens, '-'));
}

TEST(join, set_of_u16strings_delimiter_char_dash)
{
   std::set<std::u16string> tokens{u"a", u"b", u"c", u"d"};
   ASSERT_EQ(u"a-b-c-d", mzlib::u16join(tokens, '-'));
}

TEST(join, set_of_u32strings_delimiter_char_dash)
{
   std::set<std::u32string> tokens{U"a", U"b", U"c", U"d"};
   ASSERT_EQ(U"a-b-c-d", mzlib::u32join(tokens, '-'));
}

TEST(join, set_of_wstringsviews_delimiter_char_dash)
{
   std::set<std::wstring_view> tokens{L"a", L"b", L"c", L"d"};
   ASSERT_EQ(L"a-b-c-d", mzlib::wjoin(tokens, '-'));
}

TEST(join, set_of_u16stringviews_delimiter_char_dash)
{
   std::set<std::u16string_view> tokens{u"a", u"b", u"c", u"d"};
   ASSERT_EQ(u"a-b-c-d", mzlib::u16join(tokens, '-'));
}

TEST(join, set_of_u32stringviews_delimiter_char_dash)
{
   std::set<std::u32string_view> tokens{U"a", U"b", U"c", U"d"};
   ASSERT_EQ(U"a-b-c-d", mzlib::u32join(tokens, '-'));
}