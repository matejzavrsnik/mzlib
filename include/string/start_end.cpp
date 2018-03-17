//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "start_end.h"

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