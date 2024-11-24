//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "index_conversion.h"

#include <algorithm>

TEST(get_index, basic) 
{
   std::vector<int> v;
   for(int i=0; i<10; i++) {
      v.push_back(i);
   }
   // first 
   int index_0 = mzlib::get_index(v.begin(), v.begin());
   ASSERT_EQ(index_0, 0);
   // second
   int index_1 = mzlib::get_index(v.begin(), v.begin()+1);
   ASSERT_EQ(index_1, 1);
   // middle
   int index_5 = mzlib::get_index(v.begin(), v.begin()+5);
   ASSERT_EQ(index_5, 5);
   // last
   int index_9 = mzlib::get_index(v.begin(), v.begin()+9);
   ASSERT_EQ(index_9, 9);
}

TEST(get_iterator, basic) 
{
   std::vector<int> v;
   for(int i=0; i<10; i++) {
      v.push_back(i);
   }
   // first 
   auto it_0 = mzlib::get_iterator(v.begin(), 0);
   ASSERT_EQ(it_0, std::find(v.begin(), v.end(), 0));
   // second
   auto it_1 = mzlib::get_iterator(v.begin(), 1);
   ASSERT_EQ(it_1, std::find(v.begin(), v.end(), 1));
   // middle
   auto it_5 = mzlib::get_iterator(v.begin(), 5);
   ASSERT_EQ(it_5, std::find(v.begin(), v.end(), 5));
   // last
   auto it_9 = mzlib::get_iterator(v.begin(), 9);
   ASSERT_EQ(it_9, std::find(v.begin(), v.end(), 9));
}