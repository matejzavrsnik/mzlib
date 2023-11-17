//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "converter_to_unordered_set.h"
#include "gtest/gtest.h"

TEST(to_unordered_set, vector_strings)
{
   std::vector<std::string> v{"one", "two", "three", "four"};
   std::unordered_set<std::string> s = mzlib::to_unordered_set(v);

   ASSERT_EQ(4, s.size());
}

TEST(to_unordered_set, vector_ints)
{
   std::vector<int> v{1, 2, 3, 4};
   std::unordered_set<int> s = mzlib::to_unordered_set(v);

   ASSERT_EQ(4, s.size());
}

TEST(to_unordered_set, array_ints)
{
   std::array<int, 4> a{1, 2, 3, 4};
   std::unordered_set<int> s = mzlib::to_unordered_set(a);

   ASSERT_EQ(4, s.size());
}
