//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "exists_in.h"
#include "../lang/equal_to.h"
#include <gtest/gtest.h>

TEST(reusables, exists_in_middle)
{
   const mzlib::grid::type<int> g = {
      {0,0,0},
      {0,3,0},
      {0,0,0},
   };

   ASSERT_TRUE(mzlib::grid::exists_in(g, mzlib::equal_to(3)));
}

TEST(reusables, exists_in_tl)
{
   const mzlib::grid::type<int> g = {
      {1,0,0},
      {0,3,0},
      {0,0,0},
   };

   ASSERT_TRUE(mzlib::grid::exists_in(g, mzlib::equal_to(1)));
}

TEST(reusables, exists_in_tr)
{
   const mzlib::grid::type<int> g = {
      {1,0,200},
      {0,3,0},
      {0,0,0},
   };

   ASSERT_TRUE(mzlib::grid::exists_in(g, mzlib::equal_to(200)));
}

TEST(reusables, exists_in_bl)
{
   const mzlib::grid::type<int> g = {
      {1,0,200},
      {0,3,0},
      {201,0,0},
   };

   ASSERT_TRUE(mzlib::grid::exists_in(g, mzlib::equal_to(201)));
}

TEST(reusables, exists_in_br)
{
   const mzlib::grid::type<int> g = {
      {1,0,200},
      {0,3,0},
      {201,0,-1},
   };

   ASSERT_TRUE(mzlib::grid::exists_in(g, mzlib::equal_to(-1)));
}
