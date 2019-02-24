//
// Copyright (c) 2019 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "trim.h"

#include <string_view>
#include <cctype>

TEST(trim_from_end, demo)
{
   using sv = std::string_view;
   
   ASSERT_EQ("", mzlib::trim_from_end(sv{""}, isspace));
   ASSERT_EQ("", mzlib::trim_from_end(sv{" "}, isspace));
   ASSERT_EQ("", mzlib::trim_from_end(sv{"     "}, isspace));
   ASSERT_EQ("   I must not fear", mzlib::trim_from_end(sv{"   I must not fear  "}, isspace)); 
   ASSERT_EQ("I must not fear", mzlib::trim_from_end(sv{"I must not fear  "}, isspace)); 
   ASSERT_EQ("   I must not fear", mzlib::trim_from_end(sv{"   I must not fear"}, isspace)); 
   ASSERT_EQ("I must not fear", mzlib::trim_from_end(sv{"I must not fear"}, isspace)); 
   ASSERT_EQ("  I must not fear", mzlib::trim_from_end(sv{"  I must not fear  "}, isspace)); 
}

TEST(trim_from_start, demo)
{
   using sv = std::string_view;
   
   ASSERT_EQ("", mzlib::trim_from_start(sv{""}, isspace));
   ASSERT_EQ("", mzlib::trim_from_start(sv{" "}, isspace));
   ASSERT_EQ("", mzlib::trim_from_start(sv{"     "}, isspace));
   ASSERT_EQ("I must not fear  ", mzlib::trim_from_start(sv{"   I must not fear  "}, isspace)); 
   ASSERT_EQ("I must not fear  ", mzlib::trim_from_start(sv{"I must not fear  "}, isspace)); 
   ASSERT_EQ("I must not fear", mzlib::trim_from_start(sv{"   I must not fear"}, isspace)); 
   ASSERT_EQ("I must not fear", mzlib::trim_from_start(sv{"I must not fear"}, isspace)); 
   ASSERT_EQ("I must not fear  ", mzlib::trim_from_start(sv{"  I must not fear  "}, isspace)); 
}

TEST(trim, demo)
{
   using sv = std::string_view;
   
   ASSERT_EQ("", mzlib::trim(sv{""}, isspace));
   ASSERT_EQ("", mzlib::trim(sv{" "}, isspace));
   ASSERT_EQ("", mzlib::trim(sv{"     "}, isspace));
   ASSERT_EQ("I must not fear", mzlib::trim(sv{"   I must not fear  "}, isspace)); 
   ASSERT_EQ("I must not fear", mzlib::trim(sv{"I must not fear  "}, isspace)); 
   ASSERT_EQ("I must not fear", mzlib::trim(sv{"   I must not fear"}, isspace)); 
   ASSERT_EQ("I must not fear", mzlib::trim(sv{"I must not fear"}, isspace)); 
   ASSERT_EQ("I must not fear", mzlib::trim(sv{"  I must not fear  "}, isspace)); 
}