//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_SORT_MAP_BY_VALUE_H
#define MZLIB_SORT_MAP_BY_VALUE_H

namespace mzlib {
    
// Map is already intrinsically sorted by keys, but what if you need items sorted
// by values instead?
template <class Key, class Value>
std::vector<std::pair<Key, Value>> sort_map_by_value(
   const std::map<Key,Value>& unsorted, 
   option::descending descending = option::descending::no)
{
   std::vector<std::pair<Key, Value>> result;
   
   std::copy (unsorted.begin(),unsorted.end(),std::back_inserter(result));
   
   std::sort(result.begin(), result.end(), 
      [&descending](const std::pair<Key, Value>& a, const std::pair<Key, Value>& b) 
      {
         return descending ? 
            b.second < a.second : 
            b.second > a.second;   
      });
   return result;
}

} // namespace

#endif // MZLIB_SORT_MAP_BY_VALUE_H

#ifdef MZLIB_BUILDING_TESTS

#ifndef MZLIB_SORT_MAP_BY_VALUE_TESTS_H
#define MZLIB_SORT_MAP_BY_VALUE_TESTS_H

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

#endif // MZLIB_SORT_MAP_BY_VALUE_TESTS_H

#endif // MZLIB_BUILDING_TESTS
