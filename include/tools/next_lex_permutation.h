//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_NEXT_LEX_PERMUTATION_H
#define MZLIB_NEXT_LEX_PERMUTATION_H

#include <algorithm>
#include "../iterators/conditional_find.h"

namespace mzlib {
    
// I think everybody except me has written lexical permutation function at least 
// once in their lives. Here it goes. (FYI: there is a function in std:: that
// does this and probably does it better, if you actually need one.)
template<class Iterator>
void next_lex_permutation(Iterator begin, Iterator end)
{
   auto k = last_where_value_smaller_then_next(begin, end);
   if (k==end) return; // done, this was last permutation
   
   auto l = last_where_value_larger_then_given(begin, end, *k);
   if (l==end) return; // done
   
   std::iter_swap(k, l);
   std::reverse(k+1, end);
}

} // namespace

#endif // MZLIB_NEXT_LEX_PERMUTATION_H

#ifdef MZLIB_NEXT_LEX_PERMUTATION_TESTS_H

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

#endif // MZLIB_NEXT_LEX_PERMUTATION_TESTS_H
