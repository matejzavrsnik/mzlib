//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "next_lex_permutation.h"

TEST(next_lex_permutation, basic)
{
   std::vector<int> v = {1,2,3,4,5};
   
   mzlib::next_lex_permutation(v.begin(), v.end());
   ASSERT_EQ(v, std::vector<int>({1,2,3,5,4}));
   mzlib::next_lex_permutation(v.begin(), v.end());
   ASSERT_EQ(v, std::vector<int>({1,2,4,3,5}));
   mzlib::next_lex_permutation(v.begin(), v.end());
   ASSERT_EQ(v, std::vector<int>({1,2,4,5,3}));
   mzlib::next_lex_permutation(v.begin(), v.end());
   ASSERT_EQ(v, std::vector<int>({1,2,5,3,4}));
   mzlib::next_lex_permutation(v.begin(), v.end());
   ASSERT_EQ(v, std::vector<int>({1,2,5,4,3}));
}

TEST(next_lex_permutation, empty)
{
   std::vector<int> v = {};
   
   mzlib::next_lex_permutation(v.begin(), v.end());
   ASSERT_EQ(v, std::vector<int>({}));
}

TEST(next_lex_permutation, one)
{
   std::vector<int> v = {1};
   
   mzlib::next_lex_permutation(v.begin(), v.end());
   ASSERT_EQ(v, std::vector<int>({1}));
}

TEST(next_lex_permutation, two)
{
   std::vector<int> v = {1,2};
   
   mzlib::next_lex_permutation(v.begin(), v.end());
   ASSERT_EQ(v, std::vector<int>({2,1}));
}

TEST(next_lex_permutation, end)
{
   std::vector<int> v = {2,1};
   
   mzlib::next_lex_permutation(v.begin(), v.end());
   ASSERT_EQ(v, std::vector<int>({2,1}));
}