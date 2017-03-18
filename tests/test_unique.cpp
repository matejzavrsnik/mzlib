//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "../include/abstract/unique.h"
#include "gtest/gtest.h"

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
   mzlib::unique a;
   mzlib::unique b;
   ASSERT_NE(a.id(), b.id()); 
}

TEST_F(fixture_unique, unique_on_copy) 
{
   mzlib::unique a;
   mzlib::unique b;
   mzlib::unique c(a);
   mzlib::unique d = a;
   ASSERT_NE(a.id(), b.id());
   ASSERT_EQ(a.id(), c.id());
   ASSERT_EQ(a.id(), d.id());
}