//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "to.h"
#include "gtest/gtest.h"

TEST(to, vector_strings_to_unordered_set)
{
   std::vector<std::string> v{"one", "two", "three", "four"};
   std::unordered_set<std::string> s = mzlib::to<std::unordered_set>(v);

   ASSERT_EQ(4, s.size());
}

TEST(to, vector_ints_to_unordered_set)
{
   std::vector<int> v{1, 2, 3, 4};
   std::unordered_set<int> s = mzlib::to<std::unordered_set>(v);

   ASSERT_EQ(4, s.size());
}

TEST(to, array_ints_to_unordered_set)
{
   std::array<int, 4> a{1, 2, 3, 4};
   std::unordered_set<int> s = mzlib::to<std::unordered_set>(a);

   ASSERT_EQ(4, s.size());
}

TEST(to, set_strings_to_vector)
{
   std::set<std::string> s{"one", "two", "three", "four"};
   std::vector<std::string> v = mzlib::to<std::vector>(s);

   ASSERT_EQ(4, v.size());
}

TEST(to, set_ints_to_vector)
{
   std::set<int> s{1, 2, 3, 4};
   std::vector<int> v = mzlib::to<std::vector>(s);

   ASSERT_EQ(4, v.size());
}

TEST(to, unordered_set_ints_to_vector)
{
   std::unordered_set<int> s{1, 2, 3, 4};
   std::vector<int> v = mzlib::to<std::vector>(s);

   ASSERT_EQ(4, v.size());
}