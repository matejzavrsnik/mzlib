//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "are_touching.h"
#include <gtest/gtest.h>

TEST(are_touching, cases)
{
   //   -1 0 1 2 3
   // -1 . . . . .
   //  0 . . . . .
   //  1 . . o . .
   //  2 . . . . .
   //  3 . . . . .
   const mzlib::grid::cell pos{1,1};

   //   -1 0 1 2 3
   // -1 . . . . .
   //  0 . m . . .
   //  1 . . o . .
   //  2 . . . . .
   //  3 . . . . .
   ASSERT_TRUE(mzlib::grid::are_touching(pos, {0,0}));

   //   -1 0 1 2 3
   // -1 . . . . .
   //  0 . . . . .
   //  1 . m o . .
   //  2 . . . . .
   //  3 . . . . .
   ASSERT_TRUE(mzlib::grid::are_touching(pos, {0,1}));

   //   -1 0 1 2 3
   // -1 . . . . .
   //  0 . . . . .
   //  1 . . o . .
   //  2 . m . . .
   //  3 . . . . .
   ASSERT_TRUE(mzlib::grid::are_touching(pos, {0,2}));

   //   -1 0 1 2 3
   // -1 . . . . .
   //  0 . . m . .
   //  1 . . o . .
   //  2 . . . . .
   //  3 . . . . .
   ASSERT_TRUE(mzlib::grid::are_touching(pos, {1,0}));

   //   -1 0 1 2 3
   // -1 . . . . .
   //  0 . . . . .
   //  1 . . o . .
   //  2 . . m . .
   //  3 . . . . .
   ASSERT_TRUE(mzlib::grid::are_touching(pos, {1,2}));

   //   -1 0 1 2 3
   // -1 . . . . .
   //  0 . . . m .
   //  1 . . o . .
   //  2 . . . . .
   //  3 . . . . .
   ASSERT_TRUE(mzlib::grid::are_touching(pos, {2,0}));

   //   -1 0 1 2 3
   // -1 . . . . .
   //  0 . . . . .
   //  1 . . o m .
   //  2 . . . . .
   //  3 . . . . .
   ASSERT_TRUE(mzlib::grid::are_touching(pos, {2,1}));

   //   -1 0 1 2 3
   // -1 . . . . .
   //  0 . . . . .
   //  1 . . o . .
   //  2 . . . m .
   //  3 . . . . .
   ASSERT_TRUE(mzlib::grid::are_touching(pos, {2,2}));

   //   -1 0 1 2 3
   // -1 . . . . .
   //  0 . . . . .
   //  1 . . o . .
   //  2 . . . . .
   //  3 m . . . .
   ASSERT_FALSE(mzlib::grid::are_touching(pos, {-1,3}));

   //   -1 0 1 2 3
   // -1 . . . . .
   //  0 . . . . .
   //  1 . . o . .
   //  2 . . . . .
   //  3 . m . . .
   ASSERT_FALSE(mzlib::grid::are_touching(pos, {0,3}));

   //   -1 0 1 2 3
   // -1 . . . . .
   //  0 . . . . .
   //  1 . . o . .
   //  2 . . . . .
   //  3 . . m . .
   ASSERT_FALSE(mzlib::grid::are_touching(pos, {1,3}));

   //   -1 0 1 2 3
   // -1 . . . . .
   //  0 . . . . .
   //  1 . . o . .
   //  2 . . . . .
   //  3 . . . m .
   ASSERT_FALSE(mzlib::grid::are_touching(pos, {2,3}));

   //   -1 0 1 2 3
   // -1 . . . . .
   //  0 . . . . .
   //  1 . . o . .
   //  2 . . . . .
   //  3 . . . . m
   ASSERT_FALSE(mzlib::grid::are_touching(pos, {3,3}));

   //   -1 0 1 2 3
   // -1 . . . . .
   //  0 . . . . .
   //  1 . . o . .
   //  2 m . . . .
   //  3 . . . . .
   ASSERT_FALSE(mzlib::grid::are_touching(pos, {-1,2}));

   //   -1 0 1 2 3
   // -1 . . . . .
   //  0 . . . . .
   //  1 . . o . .
   //  2 . . . . m
   //  3 . . . . .
   ASSERT_FALSE(mzlib::grid::are_touching(pos, {3,2}));

   //   -1 0 1 2 3
   // -1 . . . . .
   //  0 . . . . .
   //  1 m . o . .
   //  2 . . . . .
   //  3 . . . . .
   ASSERT_FALSE(mzlib::grid::are_touching(pos, {-1,1}));

   //   -1 0 1 2 3
   // -1 . . . . .
   //  0 . . . . .
   //  1 . . o . m
   //  2 . . . . .
   //  3 . . . . .
   ASSERT_FALSE(mzlib::grid::are_touching(pos, {3,1}));

   //   -1 0 1 2 3
   // -1 . . . . .
   //  0 m . . . .
   //  1 . . o . .
   //  2 . . . . .
   //  3 . . . . .
   ASSERT_FALSE(mzlib::grid::are_touching(pos, {-1,0}));

   //   -1 0 1 2 3
   // -1 . . . . .
   //  0 . . . . m
   //  1 . . o . .
   //  2 . . . . .
   //  3 . . . . .
   ASSERT_FALSE(mzlib::grid::are_touching(pos, {3,0}));

   //   -1 0 1 2 3
   // -1 m . . . .
   //  0 . . . . .
   //  1 . . o . .
   //  2 . . . . .
   //  3 . . . . .
   ASSERT_FALSE(mzlib::grid::are_touching(pos, {-1,-1}));

   //   -1 0 1 2 3
   // -1 . m . . .
   //  0 . . . . .
   //  1 . . o . .
   //  2 . . . . .
   //  3 . . . . .
   ASSERT_FALSE(mzlib::grid::are_touching(pos, {0,-1}));

   //   -1 0 1 2 3
   // -1 . . m . .
   //  0 . . . . .
   //  1 . . o . .
   //  2 . . . . .
   //  3 . . . . .
   ASSERT_FALSE(mzlib::grid::are_touching(pos, {1,-1}));

   //   -1 0 1 2 3
   // -1 . . . m .
   //  0 . . . . .
   //  1 . . o . .
   //  2 . . . . .
   //  3 . . . . .
   ASSERT_FALSE(mzlib::grid::are_touching(pos, {2,-1}));

   //   -1 0 1 2 3
   // -1 . . . . m
   //  0 . . . . .
   //  1 . . o . .
   //  2 . . . . .
   //  3 . . . . .
   ASSERT_FALSE(mzlib::grid::are_touching(pos, {3,-1}));
}