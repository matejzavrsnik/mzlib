//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "all_equal.h"

#include "gtest/gtest.h"

TEST(all_equal, are) 
{
   std::vector<std::string> words{"nana", "nana", "nana", "nana"};
   ASSERT_TRUE(mzlib::all_equal(words, "nana"));
}

TEST(all_equal, arent) 
{
   std::vector<std::string> words{"nana", "nana", "nana", "batman"};
   ASSERT_FALSE(mzlib::all_equal(words, "nana"));
}