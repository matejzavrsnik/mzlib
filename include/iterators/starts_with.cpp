//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "starts_with.h"

#include "gtest/gtest.h"
#include <vector>
#include <string_view>

TEST(starts_with, full_collection_larger_does_begin_with_sub)
{
   std::vector<int> v1 = {1,2,3,4,5,6,7};
   std::vector<int> v2 = {1,2,3};
   ASSERT_TRUE(mzlib::starts_with(v1.begin(), v1.end(), v2.begin(), v2.end()));
}

TEST(starts_with, full_collection_larger_does_not_begin_with_sub)
{
   std::vector<int> v1 = {1,2,3,4,5,6,7};
   std::vector<int> v2 = {1,2,4};
   ASSERT_FALSE(mzlib::starts_with(v1.begin(), v1.end(), v2.begin(), v2.end()));
}

TEST(starts_with, both_collection_equal_size_does_begin_with_sub)
{
   std::vector<int> v1 = {1,2,3,4,5,6,7};
   std::vector<int> v2 = {1,2,3,4,5,6,7};
   ASSERT_TRUE(mzlib::starts_with(v1.begin(), v1.end(), v2.begin(), v2.end()));
}

TEST(starts_with, fboth_collection_equal_size_does_not_begin_with_sub)
{
   std::vector<int> v1 = {1,2,3,4,5,6,7};
   std::vector<int> v2 = {1,2,3,4,5,6,8};
   ASSERT_FALSE(mzlib::starts_with(v1.begin(), v1.end(), v2.begin(), v2.end()));
}

TEST(starts_with, sub_collection_larger)
{
   std::vector<int> v1 = {1,2,3};
   std::vector<int> v2 = {1,2,3,4,5,6,7};
   ASSERT_FALSE(mzlib::starts_with(v1.begin(), v1.end(), v2.begin(), v2.end()));
}

TEST(starts_with, works_with_constant_iterator)
{
   std::vector<int> v1 = {1,2,3,4,5,6,7};
   std::vector<int> v2 = {1,2,3};
   ASSERT_TRUE(mzlib::starts_with(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend()));
}

TEST(starts_with, full_collection_empty)
{
   std::vector<int> v1 = {};
   std::vector<int> v2 = {1,2,3};
   ASSERT_FALSE(mzlib::starts_with(v1.begin(), v1.end(), v2.begin(), v2.end()));
}

TEST(starts_with, sub_collection_empty)
{
   std::vector<int> v1 = {1,2,3,4,5,6,7};
   std::vector<int> v2 = {};
   ASSERT_TRUE(mzlib::starts_with(v1.begin(), v1.end(), v2.begin(), v2.end()));
}

TEST(starts_with, both_collections_empty)
{
   std::vector<int> v1 = {};
   std::vector<int> v2 = {};
   ASSERT_TRUE(mzlib::starts_with(v1.begin(), v1.end(), v2.begin(), v2.end()));
}

TEST(starts_with, works_on_different_types_of_iterators)
{
   std::vector<int> v1 = {1,2,3,4,5,6,7};
   std::array<int, 3> v2 = {1,2,3};
   ASSERT_TRUE(mzlib::starts_with(v1.begin(), v1.end(), v2.begin(), v2.end()));
}

TEST(starts_with, works_on_string_views)
{
   std::string_view v1 = "1234567";
   std::string_view v2 = "123";
   ASSERT_TRUE(mzlib::starts_with(v1.begin(), v1.end(), v2.begin(), v2.end()));
}

TEST(starts_with, whole_collection_convenience_does_start_with)
{
   std::vector<int> v1 = {1,2,3,4,5,6,7};
   std::vector<int> v2 = {1,2,3};
   ASSERT_TRUE(mzlib::starts_with(v1, v2));
}

TEST(starts_with, whole_collection_convenience_does_not_start_with)
{
   std::vector<int> v1 = {1,2,3,4,5,6,7};
   std::vector<int> v2 = {1,2,4};
   ASSERT_FALSE(mzlib::starts_with(v1, v2));
}

TEST(ends_with, whole_collection_convenience_does_end_with)
{
   std::vector<int> v1 = {1,2,3,4,5,6,7};
   std::vector<int> v2 = {5,6,7};
   ASSERT_TRUE(mzlib::ends_with(v1, v2));
}

TEST(ends_with, whole_collection_convenience_does_not_end_with)
{
   std::vector<int> v1 = {1,2,3,4,5,6,7};
   std::vector<int> v2 = {4,6,7};
   ASSERT_FALSE(mzlib::ends_with(v1, v2));
}

TEST(starts_with, whole_string_convenience_does_start_with)
{
   std::string_view v1 = "1234567";
   std::string_view v2 = "123";
   ASSERT_TRUE(mzlib::starts_with(v1, v2));
}

TEST(starts_with, whole_string_convenience_does_not_start_with)
{
   std::string_view v1 = "1234567";
   std::string_view v2 = "124";
   ASSERT_FALSE(mzlib::starts_with(v1, v2));
}

TEST(ends_with, whole_string_convenience_does_end_with)
{
   std::string_view v1 = "1234567";
   std::string_view v2 = "567";
   ASSERT_TRUE(mzlib::ends_with(v1, v2));
}

TEST(ends_with, whole_string_convenience_does_not_end_with)
{
   std::string_view v1 = "1234567";
   std::string_view v2 = "467";
   ASSERT_FALSE(mzlib::ends_with(v1, v2));
}

TEST(ends_with, whole_string_convenience_equal_size_does_begin_with_sub)
{
   std::string_view v1 = "467";
   std::string_view v2 = "467";
   ASSERT_TRUE(mzlib::ends_with(v1, v2));
}
