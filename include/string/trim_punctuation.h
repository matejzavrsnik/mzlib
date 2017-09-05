//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_TRIM_PUNCTUATION_H
#define MZLIB_TRIM_PUNCTUATION_H

namespace mzlib {

// strips all non-letter characters from beginning and end of string
inline std::string 
trim_punctuation(const std::string& word)
{
   auto first = std::find_if(word.begin(), word.end(), isalpha);
   auto last = std::find_if(word.rbegin(), word.rend(), isalpha);
   std::string stripped;
   if (first != word.end() && last  != word.rend()) {
      stripped.assign(first, last.base());
   }
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

#ifdef MZLIB_BUILDING_TESTS

#ifndef MZLIB_TRIM_PUNCTUATION_TESTS_H
#define MZLIB_TRIM_PUNCTUATION_TESTS_H

TEST(trim_punctiation, demo)
{
   ASSERT_EQ("", mzlib::trim_punctuation(""));
   ASSERT_EQ("", mzlib::trim_punctuation("."));
   ASSERT_EQ("", mzlib::trim_punctuation(".!#$%"));
   ASSERT_EQ("I must not fear", mzlib::trim_punctuation(".!#I must not fear$%")); 
   ASSERT_EQ("I must not fear", mzlib::trim_punctuation("I must not fear$%")); 
   ASSERT_EQ("I must not fear", mzlib::trim_punctuation(".!#I must not fear")); 
   ASSERT_EQ("I must not fear", mzlib::trim_punctuation("I must not fear")); 
   ASSERT_EQ("", mzlib::trim_punctuation("123"));
   ASSERT_EQ("I must not fear", mzlib::trim_punctuation("11I must not fear11")); 
}



TEST(trim_punctiation_whole, demo)
{
   std::string text(" !?I must not fear.,: Fear is the mind-killer.,* ");
   std::string trimmed = mzlib::trim_punctuation_whole(text);
   
   ASSERT_EQ("ImustnotfearFearisthemindkiller", trimmed);
}

#endif // MZLIB_TRIM_PUNCTUATION_TESTS_H

#endif // MZLIB_BUILDING_TESTS

