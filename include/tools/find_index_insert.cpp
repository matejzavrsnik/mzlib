//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "find_index_insert.h"

#include "gtest/gtest.h"

TEST(find_index_insert, is_in) 
{
   std::vector<char> v{'a', 'b', 'c'};
   
   int index = mzlib::find_index_insert(v, 'b');
   
   ASSERT_EQ(1, index);
}

TEST(find_index_insert, is_not_in) 
{
   std::vector<char> v{'a', 'b', 'c'};
   
   int index = mzlib::find_index_insert(v, 'd');
   
   ASSERT_EQ(3, index);
}