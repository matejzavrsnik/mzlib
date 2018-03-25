//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "set_intersection.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace ::testing;

TEST(set_intersection, demo_returns_set)
{
   std::vector<int> a = {1,2,3,4,5};
   std::vector<int> b = {4,5,6,7,8};
   
   std::set<int> c = 
      mzlib::set_intersection(
         a.begin(), a.end(),
         b.begin(), b.end());
   
   ASSERT_THAT(c, UnorderedElementsAre(4,5));
}

TEST(set_intersection, demo_with_insert_iterator)
{
   std::vector<int> a = {1,2,3,4,5};
   std::vector<int> b = {4,5,6,7,8};
   
   std::set<int> c;
   
   mzlib::set_intersection(
      a.begin(), a.end(),
      b.begin(), b.end(),
      std::inserter(c, c.end()));
   
   ASSERT_THAT(c, UnorderedElementsAre(4,5));
}

TEST(set_intersection, element_is_present_in_other_set)
{
   std::vector<int> a = {1};
   std::vector<int> b = {1,2};
   
   std::set<int> c = 
      mzlib::set_intersection(
         a.begin(), a.end(),
         b.begin(), b.end());
   
   ASSERT_THAT(c, Contains(1));
}

TEST(set_intersection, doesnt_stop_on_first_find)
{
   std::vector<int> a = {1,3};
   std::vector<int> b = {1,2,3};
   
   std::set<int> c = 
      mzlib::set_intersection(
         a.begin(), a.end(),
         b.begin(), b.end());
   
   ASSERT_THAT(c, UnorderedElementsAre(1,3));
}

TEST(set_intersection, element_is_not_present_in_other_set)
{
   std::vector<int> a = {4};
   std::vector<int> b = {1,2,3};
   
   std::set<int> c = 
      mzlib::set_intersection(
         a.begin(), a.end(),
         b.begin(), b.end());
   
   ASSERT_THAT(c, IsEmpty());
}

TEST(set_intersection, second_set_is_smaller)
{
   std::vector<int> a = {1,2,3,4};
   std::vector<int> b = {4};
   
   std::set<int> c = 
      mzlib::set_intersection(
         a.begin(), a.end(),
         b.begin(), b.end());
   
   ASSERT_THAT(c, Contains(4));
}

