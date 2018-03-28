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

TEST(set_intersection, element_is_present_in_second_set)
{
   std::vector<int> a = {4};
   std::vector<int> b = {1,2,3,4};
   std::set<int> c;
   
   mzlib::set_intersection(
      a.begin(), a.end(),
      b.begin(), b.end(),
      std::inserter(c, c.end()));
   
   ASSERT_THAT(c, UnorderedElementsAre(4));
}

TEST(set_intersection, element_is_not_present_in_second_set)
{
   std::vector<int> a = {5};
   std::vector<int> b = {1,2,3,4};
   std::set<int> c;
   
   mzlib::set_intersection(
      a.begin(), a.end(),
      b.begin(), b.end(),
      std::inserter(c, c.end()));
   
   ASSERT_THAT(c, IsEmpty());
}

TEST(set_intersection, many_elements_present_in_second_set)
{
   std::vector<int> a = {1,3,5};
   std::vector<int> b = {1,2,3,4,5};
   std::set<int> c;
   
   mzlib::set_intersection(
      a.begin(), a.end(),
      b.begin(), b.end(),
      std::inserter(c, c.end()));
   
   ASSERT_THAT(c, UnorderedElementsAre(1,3,5));
}

TEST(set_intersection, all_elements_present_in_second_set)
{
   std::vector<int> a = {1,2,3,4,5};
   std::vector<int> b = {1,2,3,4,5};
   std::set<int> c;
   
   mzlib::set_intersection(
      a.begin(), a.end(),
      b.begin(), b.end(),
      std::inserter(c, c.end()));
   
   ASSERT_THAT(c, UnorderedElementsAre(1,2,3,4,5));
}

TEST(set_intersection, many_elements_not_present_in_second_set)
{
   std::vector<int> a = {6,7,8};
   std::vector<int> b = {1,2,3,4,5};
   std::set<int> c;
   
   mzlib::set_intersection(
      a.begin(), a.end(),
      b.begin(), b.end(),
      std::inserter(c, c.end()));
   
   ASSERT_THAT(c, IsEmpty());
}

TEST(set_intersection, element_is_present_in_smaller_set)
{
   std::vector<int> a = {1,2,3,4};
   std::vector<int> b = {4};
   std::set<int> c;
   
   mzlib::set_intersection(
      a.begin(), a.end(),
      b.begin(), b.end(),
      std::inserter(c, c.end()));
   
   ASSERT_THAT(c, UnorderedElementsAre(4));
}


TEST(set_intersection, first_set_empty)
{
   std::vector<int> a = {};
   std::vector<int> b = {1,2,3,4};
   std::set<int> c;
   
   mzlib::set_intersection(
      a.begin(), a.end(),
      b.begin(), b.end(),
      std::inserter(c, c.end()));
   
   ASSERT_THAT(c, IsEmpty());
}

TEST(set_intersection, second_set_empty)
{
   std::vector<int> a = {1,2,3,4};
   std::vector<int> b = {};
   std::set<int> c;
   
   mzlib::set_intersection(
      a.begin(), a.end(),
      b.begin(), b.end(),
      std::inserter(c, c.end()));
   
   ASSERT_THAT(c, IsEmpty());
}

TEST(set_intersection, both_sets_empty)
{
   std::vector<int> a = {};
   std::vector<int> b = {};
   std::set<int> c;
   
   mzlib::set_intersection(
      a.begin(), a.end(),
      b.begin(), b.end(),
      std::inserter(c, c.end()));
   
   ASSERT_THAT(c, IsEmpty());
}

TEST(set_intersection, works_with_custom_equality)
{
   std::vector<int> a = {1,2,3,4,5};
   std::vector<int> b = {4,5,6,7,8};
   std::set<int> c;
   
   mzlib::set_intersection_if(
      a.begin(), a.end(),
      b.begin(), b.end(),
      std::inserter(c, c.end()),
      // custom equals: 3 == 6 as well as normal equalities
      [](const int& i1, const int& i2) -> bool {
         if (i1==3 && i2==6) return true;
         return (i1==i2);
      });
   
   ASSERT_THAT(c, UnorderedElementsAre(3,4,5));
}








