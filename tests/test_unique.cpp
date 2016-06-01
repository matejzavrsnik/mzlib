//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "../include/unique.h"
#include "gtest/gtest.h"

using namespace mzlib::util;

class fixture_unique : public ::testing::Test 
{

protected:
   
   fixture_unique () {}
   virtual ~fixture_unique () {}
   virtual void SetUp() {}
   virtual void TearDown() {}
  
};

TEST_F(fixture_unique, unique_demo) 
{
   cunique a;
   cunique b;
   ASSERT_NE(a.id(), b.id()); 
}

TEST_F(fixture_unique, unique_on_copy) 
{
   cunique a;
   cunique b;
   cunique c(a);
   cunique d = a;
   ASSERT_NE(a.id(), b.id());
   ASSERT_EQ(a.id(), c.id());
   ASSERT_EQ(a.id(), d.id());
}