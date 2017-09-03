//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_CONDITIONAL_FIND_ITERATOR_H
#define MZLIB_CONDITIONAL_FIND_ITERATOR_H

#include "distance_comparison.h"

namespace mzlib {
    
template<class Iterator>
Iterator last_where_value_smaller_then_next(Iterator begin, Iterator end)
{
   if (mzlib::is_distance_smaller(begin, end, 2)) 
      return end; // nothing to find
   
   auto next = end;
   auto prev = next-1;
   
   while(prev != begin) 
      if (*(--prev) < *(--next)) 
         return prev;
   
   return end; // not found
}

template<class Iterator, class T>
Iterator last_where_value_larger_then_given(Iterator begin, Iterator end, T value_given)
{
   auto last = end;
   
   while(last != begin) 
      if (*(--last) > value_given) 
         return last;
   
   return end; // not found
}

} // namespace

#endif // MZLIB_CONDITIONAL_FIND_ITERATOR_H

#ifdef MZLIB_BUILDING_TESTS

#ifndef MZLIB_CONDITIONAL_FIND_ITERATOR_TESTS_H
#define MZLIB_CONDITIONAL_FIND_ITERATOR_TESTS_H

TEST(last_where_value_larger_then_given, basic)
{
   std::vector<int> v = {1,2,3,4,5};
   
   auto res = mzlib::last_where_value_larger_then_given(v.begin(), v.end(), 3);
   ASSERT_EQ(*res, 5);
}

TEST(last_where_value_larger_then_given, empty)
{
   std::vector<int> v = {};
   
   auto res = mzlib::last_where_value_larger_then_given(v.begin(), v.end(), 3);
   ASSERT_EQ(res, v.end());
}

TEST(last_where_value_larger_then_given, one_is_larger)
{
   std::vector<int> v = {5};
   
   auto res = mzlib::last_where_value_larger_then_given(v.begin(), v.end(), 3);
   ASSERT_EQ(*res, 5);
}

TEST(last_where_value_larger_then_given, one_is_smaller)
{
   std::vector<int> v = {2};
   
   auto res = mzlib::last_where_value_larger_then_given(v.begin(), v.end(), 3);
   ASSERT_EQ(res, v.end());
}

TEST(last_where_value_smaller_then_next, basic)
{
   std::vector<int> v = {1,4,6,1,2,3};
   // Smaller then nexts ^ ^   ^ ^ 
   
   auto res = mzlib::last_where_value_smaller_then_next(v.begin(), v.end());
   ASSERT_EQ(*res, 2);
}

TEST(last_where_value_smaller_then_next, empty)
{
   std::vector<int> v = {};
   
   auto res = mzlib::last_where_value_smaller_then_next(v.begin(), v.end());
   ASSERT_EQ(res, v.end());
}

TEST(last_where_value_smaller_then_next, one)
{
   std::vector<int> v = {1};
   
   auto res = mzlib::last_where_value_smaller_then_next(v.begin(), v.end());
   ASSERT_EQ(res, v.end());
}

TEST(last_where_value_smaller_then_next, two_equals)
{
   std::vector<int> v = {1,1};
   
   auto res = mzlib::last_where_value_smaller_then_next(v.begin(), v.end());
   ASSERT_EQ(res, v.end());
}

TEST(last_where_value_smaller_then_next, two)
{
   std::vector<int> v = {1,2};
   
   auto res = mzlib::last_where_value_smaller_then_next(v.begin(), v.end());
   ASSERT_EQ(*res, 1);
}

#endif // MZLIB_CONDITIONAL_FIND_ITERATOR_TESTS_H

#endif // MZLIB_BUILDING_TESTS
