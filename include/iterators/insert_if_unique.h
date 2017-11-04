//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_INSERT_IF_UNIQUE_H
#define MZLIB_INSERT_IF_UNIQUE_H

#include <algorithm> // std::find

namespace mzlib {
    
// adds to container, unless the element is already in
// returns iterator to element in the container
template<class Iterator, class T, class InsertIt> 
void insert_if_unique (Iterator begin, Iterator end, const T& element, InsertIt inserter) 
{
   auto sought_element = std::find(begin, end, element);
   if (sought_element == end) {
      *inserter++ = element;
   }
}
    
} // namespace

#endif /* MZLIB_INSERT_IF_UNIQUE_H */

#ifdef MZLIB_INSERT_IF_UNIQUE_TESTS_H
#undef MZLIB_INSERT_IF_UNIQUE_TESTS_H

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

#endif // MZLIB_INSERT_IF_UNIQUE_TESTS_H

