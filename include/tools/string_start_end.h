//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_STRING_START_END_H
#define MZLIB_STRING_START_END_H

namespace mzlib {

inline bool string_ends_with (const std::string& str, const std::string& end) {
   if (str.length() >= end.length()) {
      const int comparisson = str.compare (str.length() - end.length(), end.length(), end);
      return (comparisson == 0);
   }
   else {
      return false;
   }
}

inline bool string_starts_with (const std::string& str, const std::string& start) {
   if (str.length() >= start.length()) {
      const int comparisson = str.compare (0, start.length(), start);
      return (comparisson == 0);
   }
   else {
      return false;
   }
}

} // namespace

#endif // MZLIB_STRING_START_END_H

#ifdef MZLIB_BUILDING_TESTS

#ifndef MZLIB_STRING_START_END_TESTS_H
#define MZLIB_STRING_START_END_TESTS_H

TEST(string_ends_with, demo)
{
   std::string test_string = "Fear is the little-death that brings total obliteration.";
   ASSERT_TRUE (mzlib::string_ends_with(test_string, "obliteration."));
   ASSERT_FALSE(mzlib::string_ends_with(test_string, "bliss."));
}

TEST(string_starts_with, demo)
{
   std::string test_string = "Fear is the little-death that brings total obliteration.";
   ASSERT_TRUE (mzlib::string_starts_with(test_string, "Fear"));
   ASSERT_FALSE(mzlib::string_starts_with(test_string, "Courage"));
}

#endif // MZLIB_STRING_START_END_TESTS_H

#endif // MZLIB_BUILDING_TESTS
