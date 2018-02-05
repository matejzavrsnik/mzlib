//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "optional.h"

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
TEST(optional, throws_when_not_set) 
{
   mzlib::optional<int> optional;
   ASSERT_THROW(optional.get(), mzlib::exception::not_set);
}

TEST(optional, throws_not_when_set) 
{
   mzlib::optional<int> optional = 5;
   ASSERT_NO_THROW(optional.get());
}

TEST(optional, reports_when_not_set) 
{
   mzlib::optional<int> optional;
   ASSERT_FALSE(optional.is_set());
}

TEST(optional, reports_when_set) 
{
   mzlib::optional<int> optional = 5;
   ASSERT_TRUE(optional.is_set());
}

TEST(optional, gets_value_when_set) 
{
   mzlib::optional<int> optional = 5;
   ASSERT_EQ(5, optional.get());
}

TEST(optional, can_unset) 
{
   mzlib::optional<int> optional = 5;
   optional.unset();
   ASSERT_FALSE(optional.is_set());
}
#pragma GCC diagnostic warning "-Wdeprecated-declarations"