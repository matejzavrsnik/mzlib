//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_TRIM_PUNCTUATION_H
#define MZLIB_TRIM_PUNCTUATION_H

#include <algorithm>

namespace mzlib {

// strips all non-letter characters from end of string
inline std::string 
trim_nonalpha_from_end(const std::string& word)
{
   auto last = std::find_if(word.rbegin(), word.rend(), isalpha);
   std::string stripped;
   if (last != word.rend()) {
      stripped.assign(word.begin(), last.base());
   }
   return stripped;
}

// strips all non-letter characters from beginning string
inline std::string 
trim_nonalpha_from_start(const std::string& word)
{
   auto first = std::find_if(word.begin(), word.end(), isalpha);
   std::string stripped;
   if (first != word.end()) {
      stripped.assign(first, word.end());
   }
   return stripped;
}

// strips all non-letter characters from beginning and end of string
inline std::string 
trim_nonalpha(const std::string& word)
{
   std::string stripped = trim_nonalpha_from_end(word);
   stripped = trim_nonalpha_from_start(stripped);
   //auto first = std::find_if(word.begin(), word.end(), isalpha);
   //auto last = std::find_if(word.rbegin(), word.rend(), isalpha);
   //std::string stripped;
   //if (first != word.end() && last != word.rend()) {
   //   stripped.assign(first, last.base());
   //}
   return stripped;
}

// strips all non-letter characters from whole string
inline std::string 
trim_punctuation_whole(const std::string& word)
{
   std::string trimmed;
   for(auto ch : word) {
      if(std::isalpha(ch))
         trimmed.push_back(ch);
   }
   return trimmed;
}

} // namespace

#endif // MZLIB_TRIM_PUNCTUATION_H

#ifdef MZLIB_TRIM_PUNCTUATION_TESTS_H
#undef MZLIB_TRIM_PUNCTUATION_TESTS_H

TEST(trim_nonalpha_from_end, demo)
{
   ASSERT_EQ("", mzlib::trim_nonalpha_from_end(""));
   ASSERT_EQ("", mzlib::trim_nonalpha_from_end("."));
   ASSERT_EQ("", mzlib::trim_nonalpha_from_end(".!#$%"));
   ASSERT_EQ(".!#I must not fear", mzlib::trim_nonalpha_from_end(".!#I must not fear$%")); 
   ASSERT_EQ("I must not fear", mzlib::trim_nonalpha_from_end("I must not fear$%")); 
   ASSERT_EQ(".!#I must not fear", mzlib::trim_nonalpha_from_end(".!#I must not fear")); 
   ASSERT_EQ("I must not fear", mzlib::trim_nonalpha_from_end("I must not fear")); 
   ASSERT_EQ("", mzlib::trim_nonalpha_from_end("123"));
   ASSERT_EQ("11I must not fear", mzlib::trim_nonalpha_from_end("11I must not fear11")); 
}

TEST(trim_nonalpha_from_start, demo)
{
   ASSERT_EQ("", mzlib::trim_nonalpha_from_start(""));
   ASSERT_EQ("", mzlib::trim_nonalpha_from_start("."));
   ASSERT_EQ("", mzlib::trim_nonalpha_from_start(".!#$%"));
   ASSERT_EQ("I must not fear$%", mzlib::trim_nonalpha_from_start(".!#I must not fear$%")); 
   ASSERT_EQ("I must not fear$%", mzlib::trim_nonalpha_from_start("I must not fear$%")); 
   ASSERT_EQ("I must not fear", mzlib::trim_nonalpha_from_start(".!#I must not fear")); 
   ASSERT_EQ("I must not fear", mzlib::trim_nonalpha_from_start("I must not fear")); 
   ASSERT_EQ("", mzlib::trim_nonalpha_from_start("123"));
   ASSERT_EQ("I must not fear11", mzlib::trim_nonalpha_from_start("11I must not fear11")); 
}

TEST(trim_nonalpha, demo)
{
   ASSERT_EQ("", mzlib::trim_nonalpha(""));
   ASSERT_EQ("", mzlib::trim_nonalpha("."));
   ASSERT_EQ("", mzlib::trim_nonalpha(".!#$%"));
   ASSERT_EQ("I must not fear", mzlib::trim_nonalpha(".!#I must not fear$%")); 
   ASSERT_EQ("I must not fear", mzlib::trim_nonalpha("I must not fear$%")); 
   ASSERT_EQ("I must not fear", mzlib::trim_nonalpha(".!#I must not fear")); 
   ASSERT_EQ("I must not fear", mzlib::trim_nonalpha("I must not fear")); 
   ASSERT_EQ("", mzlib::trim_nonalpha("123"));
   ASSERT_EQ("I must not fear", mzlib::trim_nonalpha("11I must not fear11")); 
}

TEST(trim_punctiation_whole, demo)
{
   std::string text(" !?I must not fear.,: Fear is the mind-killer.,* ");
   std::string trimmed = mzlib::trim_punctuation_whole(text);
   
   ASSERT_EQ("ImustnotfearFearisthemindkiller", trimmed);
}

#endif // MZLIB_TRIM_PUNCTUATION_TESTS_H

