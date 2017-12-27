//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_STRING_CASE_H
#define MZLIB_STRING_CASE_H

#include <algorithm>
#include <string>

namespace mzlib {

// Overloads for std converters to lower and upper case chars.
// Standard converters have different names for narrow and for
// wide chars and they can't be used in templated context. These
// functions are implemented just for that purpose.
   
inline std::string::value_type tolower(
   std::string::value_type ch) 
{
   return std::tolower(ch);
}

inline std::wstring::value_type tolower(
   std::wstring::value_type ch)
{
   return std::towlower(ch);
}

inline std::string::value_type toupper(
   std::string::value_type ch) 
{
   return std::toupper(ch);
}

inline std::wstring::value_type toupper(
   std::wstring::value_type ch)
{
   return std::towupper(ch);
}

// And now the functionality

template<class String>
void to_lowercase_inplace(String& str)
{
   std::transform(str.begin(), str.end(), str.begin(), 
      [](typename String::value_type c) { 
         return tolower(c); 
      });
}

template<class String>
void to_uppercase_inplace(String& str)
{
   std::transform(str.begin(), str.end(), str.begin(), 
      [](typename String::value_type c) { 
         return toupper(c); 
      });
}

template<class String>
String to_lowercase_copy(const String& str)
{
   String str_copy = str; // explicitely make copy
   to_lowercase_inplace(str_copy);
   return str_copy; // rely on RVO
}

template<class String>
String to_uppercase_copy(const String& str)
{
   String str_copy = str; // explicitely make copy
   to_uppercase_inplace(str_copy);
   return str_copy; // rely on RVO
}

} // namespace

#endif // HEADER_H

#ifdef MZLIB_STRING_CASE_TESTS_H
#undef MZLIB_STRING_CASE_TESTS_H

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

#endif // MZLIB_STRING_CASE_TESTS_H

