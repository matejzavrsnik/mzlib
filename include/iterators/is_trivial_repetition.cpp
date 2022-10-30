//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "is_trivial_repetition.h"
#include "range.h"

#include "gtest/gtest.h"

#include <string>

TEST(is_trivial_repetition, demo)
{
   std::string text = "brexit means brexit";
   
   mzlib::range brexit_rep(text.begin(), text.begin()+6);
   mzlib::range exit_rep(text.begin()+2, text.begin()+6);
   
   bool is_it = mzlib::is_trivial_repetition
      <mzlib::range<std::string::iterator>>(
      {{brexit_rep, 2}},
      {exit_rep, 2});
      
   ASSERT_TRUE(is_it);
}
