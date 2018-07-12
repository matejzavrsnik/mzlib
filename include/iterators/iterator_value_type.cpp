//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "iterator_value_type.h"

TEST(iterator_value_type, vector_iterator) 
{
   bool is_same = 
      std::is_same<
         mzlib::ItValueType<std::vector<int>::iterator>,
         int>
      ::value;
   ASSERT_TRUE(is_same);
}
