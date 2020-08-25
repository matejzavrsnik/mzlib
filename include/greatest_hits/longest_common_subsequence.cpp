//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "longest_common_subsequence.h"

TEST(longest_common_substring, strings) 
{
   std::string_view str1 = "abcbdab";
   std::string_view str2 = "bdcaba";
   ASSERT_EQ(4, mzlib::longest_common_subsequence(str1, str2));
}

TEST(longest_common_substring, sequence_of_integers) 
{
   std::vector<int> str1 = {1,2,3,2,4,1,2};
   std::vector<int> str2 = {2,4,3,1,2,1};
   ASSERT_EQ(4, mzlib::longest_common_subsequence(str1, str2));
}
