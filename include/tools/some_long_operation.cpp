//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "some_long_operation.h"

using namespace std::chrono_literals;

TEST(some_long_operation, demo) 
{
   auto start_time = std::chrono::high_resolution_clock::now();
   mzlib::some_long_operation(20ms);
   auto end_time = std::chrono::high_resolution_clock::now();
   auto duration = end_time - start_time;
   ASSERT_TRUE(25ms > duration);
   ASSERT_TRUE(19ms < duration);
}