//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "overlap.h"
#include <gtest/gtest.h>

TEST(overlap, cases)
{
   ASSERT_FALSE(mzlib::interval::overlap(std::pair{1, 3}, std::pair{4, 6}));
   ASSERT_TRUE(mzlib::interval::overlap(std::pair{1, 4}, std::pair{4, 6}));
   ASSERT_TRUE(mzlib::interval::overlap(std::pair{1, 5}, std::pair{4, 6}));
   ASSERT_TRUE(mzlib::interval::overlap(std::pair{1, 6}, std::pair{4, 6}));
   ASSERT_TRUE(mzlib::interval::overlap(std::pair{1, 7}, std::pair{4, 6}));
   ASSERT_TRUE(mzlib::interval::overlap(std::pair{4, 8}, std::pair{4, 6}));
   ASSERT_TRUE(mzlib::interval::overlap(std::pair{5, 8}, std::pair{4, 6}));
   ASSERT_TRUE(mzlib::interval::overlap(std::pair{6, 8}, std::pair{4, 6}));
   ASSERT_FALSE(mzlib::interval::overlap(std::pair{7, 8}, std::pair{4, 6}));

   ASSERT_FALSE(mzlib::interval::overlap(std::pair{4, 6}, std::pair{1, 3}));
   ASSERT_TRUE(mzlib::interval::overlap(std::pair{4, 6}, std::pair{1, 4}));
   ASSERT_TRUE(mzlib::interval::overlap(std::pair{4, 6}, std::pair{1, 5}));
   ASSERT_TRUE(mzlib::interval::overlap(std::pair{4, 6}, std::pair{1, 6}));
   ASSERT_TRUE(mzlib::interval::overlap(std::pair{4, 6}, std::pair{1, 7}));
   ASSERT_TRUE(mzlib::interval::overlap(std::pair{4, 6}, std::pair{4, 8}));
   ASSERT_TRUE(mzlib::interval::overlap(std::pair{4, 6}, std::pair{5, 8}));
   ASSERT_TRUE(mzlib::interval::overlap(std::pair{4, 6}, std::pair{6, 8}));
   ASSERT_FALSE(mzlib::interval::overlap(std::pair{4, 6}, std::pair{7, 8}));
}
