//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "set_intersection.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <list>

using namespace ::testing;

namespace {
   
int test_helper_converter(std::string_view s)
{
   if (s=="one") return 1;
   if (s=="two") return 2;
   if (s=="three") return 3;
   if (s=="four") return 4;
   if (s=="five") return 5;
   return 0;
}

}

TEST(set_intersection, demo)
{
   // Finds intersection even though it's about two different containers with
   // incompatible data types, values unsorted and a custom equal function where
   // we tell the algo when the value from first set is considered to "be" in 
   // the second set
   
   std::vector<int> a = {1,3,5,4,2};
   std::list<std::string> b = {"three", "five", "four"};
   std::set<int> c;
   
   mzlib::set_intersection_if(
      a.begin(), a.end(),
      b.begin(), b.end(),
      std::inserter(c, c.end()),
      [](const int& int_num, const std::string& str_num) {
         return (int_num == test_helper_converter(str_num));
      });
   
   ASSERT_THAT(c, UnorderedElementsAre(3,4,5));
}

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

TEST(set_intersection, many_elements_present_in_second_set_not_sorted)
{
   std::vector<int> a = {5,1,3};
   std::vector<int> b = {4,5,2,1,3};
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

TEST(set_intersection, works_with_different_containers)
{
   std::vector<int> a = {1,3,5};
   std::list<int> b = {1,2,3,4,5};
   std::set<int> c;
   
   mzlib::set_intersection(
      a.begin(), a.end(),
      b.begin(), b.end(),
      std::inserter(c, c.end()));
   
   ASSERT_THAT(c, UnorderedElementsAre(1,3,5));
}

TEST(set_intersection, works_with_different_contained_types)
{
   std::vector<int> a = {1,3,5};
   std::vector<double> b = {1,2,3,4,5};
   std::set<int> c;
   
   mzlib::set_intersection(
      a.begin(), a.end(),
      b.begin(), b.end(),
      std::inserter(c, c.end()));
   
   ASSERT_THAT(c, UnorderedElementsAre(1,3,5));
}
