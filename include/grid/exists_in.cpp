//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "exists_in.h"
#include "../lang/equal_to.h"
#include <gtest/gtest.h>

TEST(exists_in, middle)
{
   const mzlib::grid::type<int> g = {
      {0,0,0},
      {0,3,0},
      {0,0,0},
   };

   ASSERT_TRUE(mzlib::grid::exists_in(g, mzlib::equal_to(3)));
}

TEST(exists_in, tl)
{
   const mzlib::grid::type<int> g = {
      {1,0,0},
      {0,3,0},
      {0,0,0},
   };

   ASSERT_TRUE(mzlib::grid::exists_in(g, mzlib::equal_to(1)));
}

TEST(exists_in, tr)
{
   const mzlib::grid::type<int> g = {
      {1,0,200},
      {0,3,0},
      {0,0,0},
   };

   ASSERT_TRUE(mzlib::grid::exists_in(g, mzlib::equal_to(200)));
}

TEST(exists_in, bl)
{
   const mzlib::grid::type<int> g = {
      {1,0,200},
      {0,3,0},
      {201,0,0},
   };

   ASSERT_TRUE(mzlib::grid::exists_in(g, mzlib::equal_to(201)));
}

TEST(exists_in, br)
{
   const mzlib::grid::type<int> g = {
      {1,0,200},
      {0,3,0},
      {201,0,-1},
   };

   ASSERT_TRUE(mzlib::grid::exists_in(g, mzlib::equal_to(-1)));
}
