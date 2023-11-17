#include "sets_intersection.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <list>
#include <vector>

TEST(sets_intersection, works_on_two_vectors)
{
   std::vector<int> v1 = {1,2,3,4,5};
   std::vector<int> v2 = {  2,3,4,5,6};
   auto intersection = mzlib::sets_intersection(v1, v2);
   ASSERT_THAT(intersection, ::testing::ElementsAre(2, 3, 4, 5));
}

TEST(sets_intersection, works_on_three_vectors)
{
   std::vector<int> v1 = {1,2,3,4,5};
   std::vector<int> v2 = {  2,3,4,5,6};
   std::vector<int> v3 = {    3,4,5,6,7};
   auto intersection = mzlib::sets_intersection(v1, v2, v3);
   ASSERT_THAT(intersection, ::testing::ElementsAre(3, 4, 5));
}

TEST(sets_intersection, works_on_four_vectors)
{
   std::vector<int> v1 = {1,2,3,4,5};
   std::vector<int> v2 = {  2,3,4,5,6};
   std::vector<int> v3 = {    3,4,5,6,7};
   std::vector<int> v4 = {      4,5,6,7,8};
   auto intersection = mzlib::sets_intersection(v1, v2, v3, v4);
   ASSERT_THAT(intersection, ::testing::ElementsAre(4, 5));
}

TEST(sets_intersection, works_on_three_lists)
{
   std::list<int> v1 = {1,2,3,4,5};
   std::list<int> v2 = {  2,3,4,5,6};
   std::list<int> v3 = {    3,4,5,6,7};
   auto intersection = mzlib::sets_intersection(v1, v2, v3);
   ASSERT_THAT(intersection, ::testing::ElementsAre(3, 4, 5));
}

TEST(sets_intersection, works_on_three_sets)
{
   std::set<int> v1 = {1,2,3,4,5};
   std::set<int> v2 = {  2,3,4,5,6};
   std::set<int> v3 = {    3,4,5,6,7};
   auto intersection = mzlib::sets_intersection(v1, v2, v3);
   ASSERT_THAT(intersection, ::testing::ElementsAre(3, 4, 5));
}
