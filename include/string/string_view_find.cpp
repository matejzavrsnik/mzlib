//
// Copyright (c) 2019 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "string_view_find.h"

#include <string_view>
#include <cctype>

TEST(find_first_of, demo)
{
   const auto npos = std::string_view::npos;
   using sv = std::string_view;
   using wsv = std::wstring_view;
   
   ASSERT_EQ(npos, mzlib::find_first_of(sv{""}, isspace));
   ASSERT_EQ(0,    mzlib::find_first_of(sv{" "}, isspace));
   ASSERT_EQ(0,    mzlib::find_first_of(sv{"     "}, isspace));
   ASSERT_EQ(0,    mzlib::find_first_of(sv{"   I must not fear  "}, isspace)); 
   ASSERT_EQ(1,    mzlib::find_first_of(sv{"I must not fear  "}, isspace)); 
   ASSERT_EQ(0,    mzlib::find_first_of(sv{"   I must not fear"}, isspace)); 
   ASSERT_EQ(1,    mzlib::find_first_of(sv{"I must not fear"}, isspace));
   ASSERT_EQ(1,    mzlib::find_first_of(sv{"I must not fear"}, isspace, 1));
   ASSERT_EQ(6,    mzlib::find_first_of(sv{"I must not fear"}, isspace, 2));
   ASSERT_EQ(15,   mzlib::find_first_of(sv{"I must not fear$$"}, ispunct));
   ASSERT_EQ(15,   mzlib::find_first_of(wsv{L"I must not fear$$"}, iswpunct));
}

TEST(rfind_first_of, demo)
{
   const auto npos = std::string_view::npos;
   using sv = std::string_view;
   using wsv = std::wstring_view;
   
   ASSERT_EQ(npos, mzlib::rfind_first_of(sv{""}, isspace));
   ASSERT_EQ(0,    mzlib::rfind_first_of(sv{" "}, isspace));
   ASSERT_EQ(4,    mzlib::rfind_first_of(sv{"     "}, isspace));
   ASSERT_EQ(19,   mzlib::rfind_first_of(sv{"   I must not fear  "}, isspace)); 
   ASSERT_EQ(16,   mzlib::rfind_first_of(sv{"I must not fear  "}, isspace)); 
   ASSERT_EQ(13,   mzlib::rfind_first_of(sv{"   I must not fear"}, isspace)); 
   ASSERT_EQ(10,   mzlib::rfind_first_of(sv{"I must not fear"}, isspace));
   ASSERT_EQ(6,    mzlib::rfind_first_of(sv{"I must not fear"}, isspace, 9)); 
   ASSERT_EQ(2,    mzlib::rfind_first_of(sv{"$$$I must not fear"}, ispunct));
   ASSERT_EQ(2,    mzlib::rfind_first_of(wsv{L"$$$I must not fear"}, iswpunct));
}

TEST(find_first_not_of, demo)
{
   const auto npos = std::string_view::npos;
   using sv = std::string_view;
   using wsv = std::wstring_view;
   
   ASSERT_EQ(npos, mzlib::find_first_not_of(sv{""}, isspace));
   ASSERT_EQ(npos, mzlib::find_first_not_of(sv{" "}, isspace));
   ASSERT_EQ(npos, mzlib::find_first_not_of(sv{"     "}, isspace));
   ASSERT_EQ(3,    mzlib::find_first_not_of(sv{"   I must not fear  "}, isspace)); 
   ASSERT_EQ(0,    mzlib::find_first_not_of(sv{"I must not fear  "}, isspace)); 
   ASSERT_EQ(3,    mzlib::find_first_not_of(sv{"   I must not fear"}, isspace)); 
   ASSERT_EQ(0,    mzlib::find_first_not_of(sv{"I must not fear"}, isspace));
   ASSERT_EQ(2,    mzlib::find_first_not_of(sv{"I must not fear"}, isspace, 1));
   ASSERT_EQ(2,    mzlib::find_first_not_of(sv{"I must not fear"}, isspace, 2));
   ASSERT_EQ(3,    mzlib::find_first_not_of(sv{"$$$I must not fear$$"}, ispunct));
   ASSERT_EQ(3,    mzlib::find_first_not_of(wsv{L"$$$I must not fear$$"}, iswpunct));
}

TEST(rfind_first_not_of, demo)
{
   const auto npos = std::string_view::npos;
   using sv = std::string_view;
   using wsv = std::wstring_view;
   
   ASSERT_EQ(npos, mzlib::rfind_first_not_of(sv{""}, isspace));
   ASSERT_EQ(npos, mzlib::rfind_first_not_of(sv{" "}, isspace));
   ASSERT_EQ(npos, mzlib::rfind_first_not_of(sv{"     "}, isspace));
   ASSERT_EQ(17,   mzlib::rfind_first_not_of(sv{"   I must not fear  "}, isspace)); 
   ASSERT_EQ(14,   mzlib::rfind_first_not_of(sv{"I must not fear  "}, isspace)); 
   ASSERT_EQ(17,   mzlib::rfind_first_not_of(sv{"   I must not fear"}, isspace)); 
   ASSERT_EQ(14,   mzlib::rfind_first_not_of(sv{"I must not fear"}, isspace));
   ASSERT_EQ(9,    mzlib::rfind_first_not_of(sv{"I must not fear"}, isspace, 10)); 
   ASSERT_EQ(9,    mzlib::rfind_first_not_of(sv{"I must not fear"}, isspace, 9)); 
   ASSERT_EQ(17,    mzlib::rfind_first_not_of(sv{"$$$I must not fear$$"}, ispunct));
   ASSERT_EQ(17,    mzlib::rfind_first_not_of(wsv{L"$$$I must not fear$$"}, iswpunct));
}
