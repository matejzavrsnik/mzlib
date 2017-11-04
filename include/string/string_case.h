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

inline void to_lowercase(std::string& str)
{
   std::transform(str.begin(), str.end(), str.begin(), 
      [](unsigned char c) { 
         return std::tolower(c); 
      });
}

inline void to_uppercase(std::string& str)
{
   std::transform(str.begin(), str.end(), str.begin(), 
      [](unsigned char c) { 
         return std::toupper(c); 
      });
}

} // namespace

#endif // HEADER_H

#ifdef MZLIB_STRING_CASE_TESTS_H
#undef MZLIB_STRING_CASE_TESTS_H

TEST(to_lowercase, demo)
{
   std::string text("I must not fear. Fear is the mind-killer.");
   mzlib::to_lowercase(text);
   
   ASSERT_EQ("i must not fear. fear is the mind-killer.", text);
}

TEST(to_uppercase, demo)
{
   std::string text("I must not fear.");
   mzlib::to_uppercase(text);
   
   ASSERT_EQ("I MUST NOT FEAR.", text);
}

#endif // MZLIB_STRING_CASE_TESTS_H

