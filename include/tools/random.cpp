//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "random.h"

TEST(get_random_integer, demo) 
{
   unsigned int a = mzlib::get_random_integer();
   unsigned int b = mzlib::get_random_integer();
   unsigned int c = mzlib::get_random_integer();
   unsigned int d = mzlib::get_random_integer();
   ASSERT_NE(a, b);
   ASSERT_NE(b, c);
   ASSERT_NE(c, d);
}

TEST(get_random_integer_between, distribution_test_whole_range) 
{
   int repetitions = 100000;
   std::vector<int> event_occurences(100, 0);
   for(int i=0; i<repetitions; ++i) {
      int event = mzlib::get_random_integer_between(0, 100);
      event_occurences[event]++;
   }

   for(int i=0; i<100; ++i)
   {
      ASSERT_NEAR(event_occurences[i], repetitions/100, repetitions*0.02);
   }
}

TEST(get_random_integer_between, distribution_test_range_without_zero) 
{
   int repetitions = 100000;
   std::vector<int> event_occurences(100, 0);
   for(int i=0; i<repetitions; ++i) {
      int event = mzlib::get_random_integer_between(50, 100);
      event_occurences[event]++;
   }
   
   for(int i=0; i<50; ++i)
   {
      ASSERT_EQ(0, event_occurences[i]);
   }
   for(int i=50; i<100; ++i)
   {
      ASSERT_NEAR(event_occurences[i], repetitions/50, repetitions*0.02);
   }
}

TEST(random, get_random_double_between_0_1) 
{
   double a = mzlib::get_random_double_between_0_1();
   double b = mzlib::get_random_double_between_0_1();
   double c = mzlib::get_random_double_between_0_1();
   double d = mzlib::get_random_double_between_0_1();
   ASSERT_NE(a, b);
   ASSERT_NE(b, c);
   ASSERT_NE(c, d);
}