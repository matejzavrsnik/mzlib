//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_GET_SUBSTRING_H
#define MZLIB_GET_SUBSTRING_H

namespace mzlib {

inline std::string get_substring_between (const std::string& str, const std::string& start, const std::string& end)
{
   std::string result;
   
   size_t pos_start = str.find(start);
   if (pos_start != std::string::npos)
      pos_start += start.length();
   
   size_t pos_end = str.find(end, pos_start);
   
   if (pos_start != std::string::npos && 
       pos_end   != std::string::npos) 
   {
      if (pos_end < pos_start) {
         std::swap(pos_start, pos_end);
      }
      result = str.substr(pos_start, pos_end-pos_start);
   }
   return result;
}

} // namespace

#endif // MZLIB_GET_SUBSTRING_H

#ifdef MZLIB_GET_SUBSTRING_TESTS_H
#undef MZLIB_GET_SUBSTRING_TESTS_H

TEST(get_substring_between, demo)
{
   auto res = mzlib::get_substring_between(
      "value=bajillion;",
      "value=", ";");
   ASSERT_EQ("bajillion", res);
}

TEST(get_substring_between, start_missing)
{
   auto res = mzlib::get_substring_between(
      "bajillion;",
      "value=", ";");
   ASSERT_EQ("", res);
}

TEST(get_substring_between, end_missing)
{
   auto res = mzlib::get_substring_between(
      "value=bajillion",
      "value=", ";");
   ASSERT_EQ("", res);
}

TEST(get_substring_between, start_and_end_missing)
{
   auto res = mzlib::get_substring_between(
      "bajillion",
      "value=", ";");
   ASSERT_EQ("", res);
}

TEST(get_substring_between, empty_source_str)
{
   auto res = mzlib::get_substring_between(
      "",
      "value=", ";");
   ASSERT_EQ("", res);
}

TEST(get_substring_between, empty_start_str)
{
   auto res = mzlib::get_substring_between(
      "value=bajillion",
      "", ";");
   ASSERT_EQ("", res);
}

TEST(get_substring_between, empty_end_str)
{
   auto res = mzlib::get_substring_between(
      "value=bajillion",
      "value=", "");
   ASSERT_EQ("", res);
}

#endif // MZLIB_GET_SUBSTRING_TESTS_H

