//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "string_case.h"

TEST(to_lowercase_inplace, demo)
{
   std::string text("I must not fear. Fear is the mind-killer.");
   mzlib::to_lowercase_inplace(text);
   
   ASSERT_EQ("i must not fear. fear is the mind-killer.", text);
}

TEST(to_lowercase_inplace, works_on_wide_string)
{
   std::wstring text(L"I must not fear. Fear is the mind-killer.");
   mzlib::to_lowercase_inplace(text);
   
   ASSERT_EQ(L"i must not fear. fear is the mind-killer.", text);
}

TEST(to_uppercase_inplace, demo)
{
   std::string text("I must not fear.");
   mzlib::to_uppercase_inplace(text);
   
   ASSERT_EQ("I MUST NOT FEAR.", text);
}

TEST(to_uppercase_inplace, works_on_wide_strings)
{
   std::wstring text(L"I must not fear.");
   mzlib::to_uppercase_inplace(text);
   
   ASSERT_EQ(L"I MUST NOT FEAR.", text);
}

TEST(to_lowercase_copy, demo)
{
   std::string text_original("I must not fear. Fear is the mind-killer.");
   std::string text_lower = mzlib::to_lowercase_copy(text_original);
   
   ASSERT_EQ("I must not fear. Fear is the mind-killer.", text_original);
   ASSERT_EQ("i must not fear. fear is the mind-killer.", text_lower);
}

TEST(to_lowercase_copy, works_on_wide_strings)
{
   std::wstring text_original(L"I must not fear. Fear is the mind-killer.");
   std::wstring text_lower = mzlib::to_lowercase_copy(text_original);
   
   ASSERT_EQ(L"I must not fear. Fear is the mind-killer.", text_original);
   ASSERT_EQ(L"i must not fear. fear is the mind-killer.", text_lower);
}

TEST(to_uppercase_copy, demo)
{
   std::string text_original("I must not fear.");
   std::string text_upper = mzlib::to_uppercase_copy(text_original);
   
   ASSERT_EQ("I must not fear.", text_original);
   ASSERT_EQ("I MUST NOT FEAR.", text_upper);
}

TEST(to_uppercase_copy, works_on_wide_strings)
{
   std::wstring text_original(L"I must not fear.");
   std::wstring text_upper = mzlib::to_uppercase_copy(text_original);
   
   ASSERT_EQ(L"I must not fear.", text_original);
   ASSERT_EQ(L"I MUST NOT FEAR.", text_upper);
}