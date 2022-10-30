//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "get_if_exists.h"

TEST(get_if_exists, it_does) 
{
   std::map<int, char> a_map_o_things;
   a_map_o_things[1] = '1';
   a_map_o_things[2] = '2';
   std::optional<char> char_one = mzlib::get_if_exists(1, a_map_o_things);
   ASSERT_TRUE(char_one.has_value());
   ASSERT_EQ('1', char_one);
}

TEST(get_if_exists, it_does_not) 
{
   std::map<int, char> a_map_o_things;
   a_map_o_things[1] = '1';
   a_map_o_things[2] = '2';
   std::optional<char> char_three = mzlib::get_if_exists(3, a_map_o_things);
   ASSERT_FALSE(char_three.has_value());
}