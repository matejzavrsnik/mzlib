//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "median_maintenance.h"

TEST(median_maintenance, no_elements) 
{
   mzlib::median_maintenance<int> mm;
   ASSERT_THROW(mm.get_median(), mzlib::exception::is_empty);
}

TEST(median_maintenance, one_element) 
{
   mzlib::median_maintenance<int> mm{ 1 };
   ASSERT_EQ(1, mm.get_median());
}

TEST(median_maintenance, two_elements) 
{
   mzlib::median_maintenance<int> mm{ 1, 3 };
   ASSERT_EQ(2, mm.get_median());
}

TEST(median_maintenance, three_elements) 
{
   mzlib::median_maintenance<int> mm{ 1, 2, 3 };
   ASSERT_EQ(2, mm.get_median());
}

TEST(median_maintenance, three_elements_order_doesnt_matter) 
{
   mzlib::median_maintenance<int> mm{ 2, 3, 1 };
   ASSERT_EQ(2, mm.get_median());
}

TEST(median_maintenance, can_remove) 
{
   mzlib::median_maintenance<int> mm{ 1, 3 };
   mm.remove(3);
   ASSERT_EQ(1, mm.get_median());
}