//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "is_end_start_of_word.h"
#include <string>
#include <string_view>

// start of word, position version

TEST(is_start_of_word, position_beginning_of_string)
{
   std::string_view str = "abcd";
   auto pos = str.find('a');
   
   ASSERT_TRUE(mzlib::is_start_of_word(pos, str));
}

TEST(is_start_of_word, position_middle_of_string)
{
   std::string_view str = "abcd efg";
   auto pos = str.find('e');
   
   ASSERT_TRUE(mzlib::is_start_of_word(pos, str));
}

TEST(is_start_of_word, position_middle_of_string_not_start_of_word)
{
   std::string_view str = "abcd efg";
   auto pos = str.find('d');
   
   ASSERT_FALSE(mzlib::is_start_of_word(pos, str));
}

TEST(is_start_of_word, position_end_of_string)
{
   std::string_view str = "abcd";
   auto pos = str.find('d');
   
   ASSERT_FALSE(mzlib::is_start_of_word(pos, str));
}

TEST(is_start_of_word, position_beyond_end_of_string)
{
   std::string_view str = "abcd";
   auto pos = str.find('d');
   pos += 2;
   
   ASSERT_FALSE(mzlib::is_start_of_word(pos, str));
}

TEST(is_start_of_word, position_substring_not_found)
{
   std::string_view str = "abcd";
   auto pos = str.find('e');
   
   ASSERT_FALSE(mzlib::is_start_of_word(pos, str));
}

// end of word, position version

TEST(is_end_of_word, position_beginning_of_string)
{
   std::string_view str = "abcd";
   auto pos = str.find('a');
   
   ASSERT_FALSE(mzlib::is_end_of_word(pos, str));
}

TEST(is_end_of_word, position_middle_of_string)
{
   std::string_view str = "abcd efg";
   auto pos = str.find('d');
   
   ASSERT_TRUE(mzlib::is_end_of_word(pos, str));
}

TEST(is_start_of_word, position_middle_of_string_not_end_of_word)
{
   std::string_view str = "abcd efg";
   auto pos = str.find('e');
   
   ASSERT_FALSE(mzlib::is_end_of_word(pos, str));
}

TEST(is_end_of_word, position_end_of_string)
{
   std::string_view str = "abcd";
   auto pos = str.find('d');
   
   ASSERT_TRUE(mzlib::is_end_of_word(pos, str));
}

TEST(is_end_of_word, position_beyond_end_of_string)
{
   std::string_view str = "abcd";
   auto pos = str.find('d');
   pos += 2;
   
   ASSERT_FALSE(mzlib::is_end_of_word(pos, str));
}

TEST(is_end_of_word, position_substring_not_found)
{
   std::string_view str = "abcd";
   auto pos = str.find('e');
   
   ASSERT_FALSE(mzlib::is_end_of_word(pos, str));
}

// start of word, iterator version

TEST(is_start_of_word, iterator_beginning_of_string)
{
   std::string_view str = "abcd";
   auto pos = str.begin(); // a
   
   ASSERT_TRUE(mzlib::is_start_of_word(pos, str.begin(), str.end()));
}

TEST(is_start_of_word, iterator_middle_of_string)
{
   std::string_view str = "abcd efg";
   auto pos = str.begin()+5; // e
   
   ASSERT_TRUE(mzlib::is_start_of_word(pos, str.begin(), str.end()));
}

TEST(is_start_of_word, iterator_middle_of_string_not_start_of_word)
{
   std::string_view str = "abcd efg";
   auto pos = str.begin()+3; // d
   
   ASSERT_FALSE(mzlib::is_start_of_word(pos, str.begin(), str.end()));
}

TEST(is_start_of_word, iterator_end_of_string)
{
   std::string_view str = "abcd";
   auto pos = str.begin()+3; // d
   
   ASSERT_FALSE(mzlib::is_start_of_word(pos, str.begin(), str.end()));
}

// end of word, iterator version

TEST(is_end_of_word, iterator_beginning_of_string)
{
   std::string_view str = "abcd";
   auto pos = str.begin(); // a
   
   ASSERT_FALSE(mzlib::is_end_of_word(pos, str.begin(), str.end()));
}

TEST(is_end_of_word, iterator_middle_of_string)
{
   std::string_view str = "abcd efg";
   auto pos = str.begin()+3; // d
   
   ASSERT_TRUE(mzlib::is_end_of_word(pos, str.begin(), str.end()));
}

TEST(is_start_of_word, iterator_middle_of_string_not_end_of_word)
{
   std::string_view str = "abcd efg";
   auto pos = str.begin()+5; // e
   
   ASSERT_FALSE(mzlib::is_end_of_word(pos, str.begin(), str.end()));
}

TEST(is_end_of_word, iterator_end_of_string)
{
   std::string_view str = "abcd";
   auto pos = str.begin()+3; // d
   
   ASSERT_TRUE(mzlib::is_end_of_word(pos, str.begin(), str.end()));
}

TEST(is_end_of_word, iterator_beyond_end_of_string)
{
   std::string_view str = "abcd";
   auto pos = str.end();
   
   ASSERT_FALSE(mzlib::is_end_of_word(pos, str.begin(), str.end()));
}