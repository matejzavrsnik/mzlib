//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "converter_to_vector.h"
#include "gtest/gtest.h"
#include <set>
#include <unordered_set>

TEST(to_vector, set_strings)
{
   std::set<std::string> s{"one", "two", "three", "four"};
   std::vector<std::string> v = mzlib::to_vector(s);

   ASSERT_EQ(4, v.size());
}

TEST(to_vector, set_ints)
{
   std::set<int> s{1, 2, 3, 4};
   std::vector<int> v = mzlib::to_vector(s);

   ASSERT_EQ(4, v.size());
}

TEST(to_vector, unordered_set_ints)
{
   std::unordered_set<int> s{1, 2, 3, 4};
   std::vector<int> v = mzlib::to_vector(s);

   ASSERT_EQ(4, v.size());
}
