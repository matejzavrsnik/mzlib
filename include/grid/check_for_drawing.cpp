//
// Copyright (c) 2024 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "check_for_drawing.h"
#include <gtest/gtest.h>

TEST(check_for_drawing, basic)
{
   mzlib::grid::type<int> canvas = {
      {0,0,0,0,0,0,0},
      {0,0,2,1,3,0,0},
      {0,0,1,1,1,0,0},
      {0,0,5,1,4,0,0},
      {0,0,0,0,0,0,0}
   };

   const mzlib::grid::type<int> drawing = {
      {0,1,0},
      {1,1,1},
      {0,1,0},
   };

   ASSERT_TRUE(mzlib::grid::check_for_drawing(canvas, drawing, {2,1}, 0));
   ASSERT_FALSE(mzlib::grid::check_for_drawing(canvas, drawing, {2,2}));
}
