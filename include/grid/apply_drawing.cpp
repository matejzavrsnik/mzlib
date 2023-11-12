//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "apply_drawing.h"
#include <gtest/gtest.h>

TEST(reusables, apply_drawing)
{
   auto canvas = mzlib::grid::construct(40, 7, 0);

   const mzlib::grid::type<int> drawing = {
      {0,1,0},
      {1,1,1},
      {0,1,0},
   };

   mzlib::grid::apply_drawing(canvas, drawing, {2,7});

   ASSERT_EQ(std::vector<int>({0,0,0,0,0,0,0}), canvas[6]);
   ASSERT_EQ(std::vector<int>({0,0,0,1,0,0,0}), canvas[7]);
   ASSERT_EQ(std::vector<int>({0,0,1,1,1,0,0}), canvas[8]);
   ASSERT_EQ(std::vector<int>({0,0,0,1,0,0,0}), canvas[9]);
   ASSERT_EQ(std::vector<int>({0,0,0,0,0,0,0}), canvas[10]);
}
