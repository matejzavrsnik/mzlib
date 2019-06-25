//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "average.h"

TEST(average_iterator, demo)
{
   std::vector<int> v{1,2,3,4,5};
   ASSERT_EQ(3.0, mzlib::average(v.begin(),   v.end()));
   ASSERT_EQ(3.5, mzlib::average(v.begin()+1, v.end()));
   ASSERT_EQ(2.5, mzlib::average(v.begin(),   v.end()-1));
}

TEST(average_iterator, doubles)
{
   std::vector<double> v{2,2.95,2.23301};
   ASSERT_DOUBLE_EQ(2.3943366666666668, mzlib::average(v.begin(), v.end()));
}