//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_STRING_CASE_H
#define MZLIB_STRING_CASE_H

#include <algorithm>

namespace mzlib {

inline void to_lowercase_inplace(std::string& str)
{
   std::transform(str.begin(), str.end(), str.begin(), 
      [](unsigned char c) { 
         return std::tolower(c); 
      });
}

inline void to_uppercase_inplace(std::string& str)
{
   std::transform(str.begin(), str.end(), str.begin(), 
      [](unsigned char c) { 
         return std::toupper(c); 
      });
}

inline std::string to_lowercase_copy(const std::string& str)
{
   std::string str_copy = str; // explicitely make copy
   to_lowercase_inplace(str_copy);
   return str_copy; // rely on RVO
}

inline std::string to_uppercase_copy(const std::string& str)
{
   std::string str_copy = str; // explicitely make copy
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

TEST(to_uppercase_inplace, demo)
{
   std::string text("I must not fear.");
   mzlib::to_uppercase_inplace(text);
   
   ASSERT_EQ("I MUST NOT FEAR.", text);
}

TEST(to_lowercase_copy, demo)
{
   std::string text_original("I must not fear. Fear is the mind-killer.");
   std::string text_lower = mzlib::to_lowercase_copy(text_original);
   
   ASSERT_EQ("I must not fear. Fear is the mind-killer.", text_original);
   ASSERT_EQ("i must not fear. fear is the mind-killer.", text_lower);
}

TEST(to_uppercase_copy, demo)
{
   std::string text_original("I must not fear.");
   std::string text_upper = mzlib::to_uppercase_copy(text_original);
   
   ASSERT_EQ("I must not fear.", text_original);
   ASSERT_EQ("I MUST NOT FEAR.", text_upper);
}

#endif // MZLIB_STRING_CASE_TESTS_H

