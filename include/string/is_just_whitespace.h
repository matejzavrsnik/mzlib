//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_IS_JUST_WHITESPACE_H
#define MZLIB_IS_JUST_WHITESPACE_H

#include <string>
#include <cctype>

namespace mzlib {
   
inline bool is_just_whitespaces(const std::string& s)
{
   for(char c : s)
      if(!std::isspace(c))
         return false;
   return true;
}

} // namespace

#endif /* MZLIB_IS_JUST_WHITESPACE_H */

#ifdef MZLIB_IS_JUST_WHITESPACE_TESTS_H
#undef MZLIB_IS_JUST_WHITESPACE_TESTS_H

TEST(is_just_whitespaces, demo_case_true)
{
   ASSERT_TRUE(mzlib::is_just_whitespaces("\t\n \r\v\f"));
}

TEST(is_just_whitespaces, demo_case_false)
{
   ASSERT_FALSE(mzlib::is_just_whitespaces("\t\nnot just whitespaces\r\v\f"));
}

#endif // MZLIB_IS_JUST_WHITESPACE_TESTS_H