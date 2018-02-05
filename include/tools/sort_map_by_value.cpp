//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "sort_map_by_value.h"

TEST(sort_map_by_value, ascending) 
{
   std::map<int, std::string> map;
   map[1] = "ddd";
   map[2] = "ccc";
   map[3] = "bbb";
   map[4] = "aaa";
   
   // If map was iterated here, it would come out sorted by key.
   // We need it sorted by values instead;
   
   std::vector<std::pair<int, std::string>> sorted = 
      mzlib::sort_map_by_value(map, mzlib::option::descending::no);
   
   ASSERT_EQ("aaa", sorted[0].second);
   ASSERT_EQ("bbb", sorted[1].second);
   ASSERT_EQ("ccc", sorted[2].second);
   ASSERT_EQ("ddd", sorted[3].second);
}

TEST(sort_map_by_value, descending) 
{
   std::map<int, std::string> map;
   map[1] = "ddd";
   map[2] = "ccc";
   map[3] = "bbb";
   map[4] = "aaa";
   
   // If map was iterated here, it would come out sorted by key.
   // We need it sorted by values instead;
   
   std::vector<std::pair<int, std::string>> sorted = 
      mzlib::sort_map_by_value(map, mzlib::option::descending::yes);
   
   ASSERT_EQ("ddd", sorted[0].second);
   ASSERT_EQ("ccc", sorted[1].second);
   ASSERT_EQ("bbb", sorted[2].second);
   ASSERT_EQ("aaa", sorted[3].second);
}