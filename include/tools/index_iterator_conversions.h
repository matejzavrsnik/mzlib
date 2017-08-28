//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_INDEX_ITERATOR_CONVERSIONS_H
#define MZLIB_INDEX_ITERATOR_CONVERSIONS_H

#include <string>
#include <iomanip> // std::setprecision
#include <sstream>
#include <vector>
#include <functional> // std::function
#include <limits> // std::numeric_limits
#include <algorithm> // std::find
#include <map>
#include <cstring>
#include <numeric> // std::accumulate
#include <cassert>
#include <unordered_set>

#include "../lang/binary_options.h"
#include "../nature/vector.h"
#include "../lang/exceptions.h"
#include "../lang/optional.h"

namespace mzlib {
    
// converts iterator to index
template<class Iterator> 
size_t get_index (Iterator begin, Iterator it) 
{
   return std::distance(begin, it);
}

// useful when representing a matrix with one-dimensional array
// conversion function, that will convert from coordinates to array index
inline uint get_index_from_coordinates(std::array<uint,2> const coordinates, uint const row_size)
{
   return (coordinates[0] + row_size*coordinates[1]);
}

// useful when representing a matrix with one-dimensional array
// conversion function, that will convert from array index to coordinates
inline std::array<uint,2> get_coordinates_from_index(uint const index, uint const row_size)
{
   return {
      index % row_size,
      index / row_size
   };
}

} // namespace

#endif // MZLIB_INDEX_ITERATOR_CONVERSIONS_H

#ifdef MZLIB_BUILDING_TESTS

#ifndef MZLIB_INDEX_ITERATOR_CONVERSIONS_TESTS_H
#define MZLIB_INDEX_ITERATOR_CONVERSIONS_TESTS_H

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

TEST(get_index_from_coordinates, basic)
{
   ASSERT_EQ(0, mzlib::get_index_from_coordinates({0,0}, 3));
   ASSERT_EQ(1, mzlib::get_index_from_coordinates({1,0}, 3));
   ASSERT_EQ(2, mzlib::get_index_from_coordinates({2,0}, 3));
   ASSERT_EQ(3, mzlib::get_index_from_coordinates({0,1}, 3));
   
   ASSERT_EQ(4, mzlib::get_index_from_coordinates({0,1}, 4));
   ASSERT_EQ(5, mzlib::get_index_from_coordinates({0,1}, 5));
   
   ASSERT_EQ(24, mzlib::get_index_from_coordinates({4,4}, 5));
}

TEST(get_coordinates_from_index, basic)
{
   using coor = std::array<uint,2>;
   ASSERT_EQ(coor({0,0}), mzlib::get_coordinates_from_index(0,3));
   ASSERT_EQ(coor({1,0}), mzlib::get_coordinates_from_index(1,3));
   ASSERT_EQ(coor({2,0}), mzlib::get_coordinates_from_index(2,3));
   ASSERT_EQ(coor({0,1}), mzlib::get_coordinates_from_index(3,3));

   ASSERT_EQ(coor({0,1}), mzlib::get_coordinates_from_index(4, 4));
   ASSERT_EQ(coor({0,1}), mzlib::get_coordinates_from_index(5, 5));
   
   ASSERT_EQ(coor({4,4}), mzlib::get_coordinates_from_index(24, 5));
}

#endif // MZLIB_INDEX_ITERATOR_CONVERSIONS_TESTS_H

#endif // MZLIB_BUILDING_TESTS
