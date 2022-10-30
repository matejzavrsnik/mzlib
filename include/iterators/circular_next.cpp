//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "circular_next.h"

#include <list>

TEST(circular_next, vector)
{
   std::vector<int> v{1,2,3};
   auto it = v.begin();
   
   ASSERT_EQ(1, *it);
   mzlib::circular_next_iterator(it, v.begin(), v.end());
   ASSERT_EQ(2, *it);
   mzlib::circular_next_iterator(it, v.begin(), v.end());
   ASSERT_EQ(3, *it);
   mzlib::circular_next_iterator(it, v.begin(), v.end());
   ASSERT_EQ(1, *it);
   mzlib::circular_next_iterator(it, v.begin(), v.end());
   ASSERT_EQ(2, *it);
   mzlib::circular_next_iterator(it, v.begin(), v.end());
   ASSERT_EQ(3, *it);
   mzlib::circular_next_iterator(it, v.begin(), v.end());
   ASSERT_EQ(1, *it);
}

TEST(circular_next, vector_section)
{
   std::vector<int> v{1,2,3,4,5};
   auto it = v.begin();
   auto begin = v.begin()+1;
   auto end = v.begin()+3;
   
   ASSERT_EQ(1, *it);
   mzlib::circular_next_iterator(it, begin, end);
   ASSERT_EQ(2, *it);
   mzlib::circular_next_iterator(it, begin, end);
   ASSERT_EQ(3, *it);
   mzlib::circular_next_iterator(it, begin, end);
   ASSERT_EQ(2, *it);
   mzlib::circular_next_iterator(it, begin, end);
   ASSERT_EQ(3, *it);
   mzlib::circular_next_iterator(it, begin, end);
   ASSERT_EQ(2, *it);
}

TEST(circular_next, list)
{
   std::list<int> l{1,2,3};
   auto it = l.begin();
   
   ASSERT_EQ(1, *it);
   mzlib::circular_next_iterator(it, l.begin(), l.end());
   ASSERT_EQ(2, *it);
   mzlib::circular_next_iterator(it, l.begin(), l.end());
   ASSERT_EQ(3, *it);
   mzlib::circular_next_iterator(it, l.begin(), l.end());
   ASSERT_EQ(1, *it);
   mzlib::circular_next_iterator(it, l.begin(), l.end());
   ASSERT_EQ(2, *it);
   mzlib::circular_next_iterator(it, l.begin(), l.end());
   ASSERT_EQ(3, *it);
   mzlib::circular_next_iterator(it, l.begin(), l.end());
   ASSERT_EQ(1, *it);
}