//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_REMOVE_SUBSTRINGS_H
#define MZLIB_REMOVE_SUBSTRINGS_H

namespace mzlib {

inline std::string 
remove_all_occurences_of_substring(const std::string& str, const std::string& substring)
{
   if (str.length() == 0 || substring.length() == 0) 
      return str;
   
   std::string washed = str;
   size_t substring_start;
   
   substring_start = washed.find(substring);
   
   while (substring_start != std::string::npos) {
      washed.erase(substring_start, substring.length());
      substring_start = washed.find(substring);
   }
     
   
   return washed;
}


} // namespace

#endif // MZLIB_REMOVE_SUBSTRINGS_H

#ifdef MZLIB_REMOVE_SUBSTRINGS_TESTS_H
#undef MZLIB_REMOVE_SUBSTRINGS_TESTS_H

TEST(remove_all_occurences_of_substring, demo)
{
   ASSERT_EQ("", mzlib::remove_all_occurences_of_substring("", ""));
   ASSERT_EQ("", mzlib::remove_all_occurences_of_substring("aa", "aa"));
   ASSERT_EQ("bb", mzlib::remove_all_occurences_of_substring("aabb", "aa"));
   ASSERT_EQ("bb", mzlib::remove_all_occurences_of_substring("bbaa", "aa"));
   ASSERT_EQ("bb", mzlib::remove_all_occurences_of_substring("aabbaa", "aa"));
   ASSERT_EQ("bbbb", mzlib::remove_all_occurences_of_substring("bbaabb", "aa"));
   ASSERT_EQ("bbbb", mzlib::remove_all_occurences_of_substring("bbaabbaa", "aa"));
   ASSERT_EQ("bbbb", mzlib::remove_all_occurences_of_substring("aabbaabb", "aa"));
}

#endif // MZLIB_REMOVE_SUBSTRINGS_TESTS_H


