//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "is_just_whitespace.h"

TEST(is_just_whitespaces, demo_case_true)
{
   ASSERT_TRUE(mzlib::is_just_whitespaces("\t\n \r\v\f"));
}

TEST(is_just_whitespaces, demo_case_false)
{
   ASSERT_FALSE(mzlib::is_just_whitespaces("\t\nnot just whitespaces\r\v\f"));
}