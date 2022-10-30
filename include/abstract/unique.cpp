//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "unique.h"

TEST(unique, demo) 
{
   mzlib::unique a;
   mzlib::unique b;
   ASSERT_NE(a.id(), b.id()); 
}

TEST(unique, unique_on_copy) 
{
   mzlib::unique a;
   mzlib::unique b;
   mzlib::unique c(a);
   mzlib::unique d = a;
   ASSERT_NE(a.id(), b.id());
   ASSERT_EQ(a.id(), c.id());
   ASSERT_EQ(a.id(), d.id());
}