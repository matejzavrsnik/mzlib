//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "replace.h"

TEST(replace, demo)
{
   std::string s("Igneous rock, or magmatic rock, is one of the three main rock types.");
   std::string_view rock("rock");
   std::string_view scissors("scissors");
   mzlib::string_replace(s, rock, scissors);
   ASSERT_EQ(
      "Igneous scissors, or magmatic scissors, is one of the three main scissors types.",
      s);
}
