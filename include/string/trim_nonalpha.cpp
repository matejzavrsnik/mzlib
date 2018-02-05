//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "trim_nonalpha.h"

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
   std::string trimmed = mzlib::trim_nonalpha_whole(text);
   
   ASSERT_EQ("ImustnotfearFearisthemindkiller", trimmed);
}