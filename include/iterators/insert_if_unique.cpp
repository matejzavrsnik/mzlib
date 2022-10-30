//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "insert_if_unique.h"

#include <list>

TEST(insert_if_unique, works_on_vector_of_strings) 
{
   std::vector<std::string> v;
   mzlib::insert_if_unique(v.begin(), v.end(), std::string("test"), std::inserter(v, v.end()));
   ASSERT_EQ(1, v.size());
}

TEST(insert_if_unique, works_on_vector_of_ints) 
{
   std::vector<int> v;
   mzlib::insert_if_unique(v.begin(), v.end(), 123, std::inserter(v, v.end()));
   ASSERT_EQ(1, v.size());
}

TEST(insert_if_unique, works_on_list_of_ints) 
{
   std::list<int> l;
   mzlib::insert_if_unique(l.begin(), l.end(), 123, std::inserter(l, l.end()));
   ASSERT_EQ(1, l.size());
}

TEST(insert_if_unique, size1_does_not_insert_if_duplicate) 
{
   std::vector<int> v{11};
   mzlib::insert_if_unique(v.begin(), v.end(), 11, std::inserter(v, v.end()));
   ASSERT_EQ(v, std::vector<int>({11}));
}

TEST(insert_if_unique, size1_does_insert_if_not_duplicate) 
{
   std::vector<int> v{11};
   mzlib::insert_if_unique(v.begin(), v.end(), 12, std::inserter(v, v.end()));
   ASSERT_EQ(v, std::vector<int>({11,12}));
}

TEST(insert_if_unique, size3_does_not_insert_if_duplicate_is_last) 
{
   std::vector<int> v{11,12,13};
   mzlib::insert_if_unique(v.begin(), v.end(), 13, std::inserter(v, v.end()));
   ASSERT_EQ(v, std::vector<int>({11,12,13}));
}

TEST(insert_if_unique, size3_does_not_insert_if_duplicate_is_middle) 
{
   std::vector<int> v{11,12,13};
   mzlib::insert_if_unique(v.begin(), v.end(), 12, std::inserter(v, v.end()));
   ASSERT_EQ(v, std::vector<int>({11,12,13}));
}

TEST(insert_if_unique, size3_does_not_insert_if_duplicate_is_first) 
{
   std::vector<int> v{11,12,13};
   mzlib::insert_if_unique(v.begin(), v.end(), 11, std::inserter(v, v.end()));
   ASSERT_EQ(v, std::vector<int>({11,12,13}));
}

TEST(insert_if_unique, size3_does_insert_if_not_duplicate) 
{
   std::vector<int> v{11,12,13};
   mzlib::insert_if_unique(v.begin(), v.end(), 14, std::inserter(v, v.end()));
   ASSERT_EQ(v, std::vector<int>({11,12,13,14}));
}