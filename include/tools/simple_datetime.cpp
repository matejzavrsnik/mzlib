//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "simple_datetime.h"

#include "gtest/gtest.h"

TEST(simple_datetime, demo) 
{
   mzlib::simple_datetime today{2020, 12, 12, 12, 12, 12};
   mzlib::simple_datetime lunar_eclipse{2024, 3, 13, 13, 13, 13};
   
   
   auto time_till_eclipse = lunar_eclipse - today;
   auto expected = mzlib::simple_datetime{3, 3, 1, 1, 1, 1};

   ASSERT_EQ(time_till_eclipse, expected);
}
