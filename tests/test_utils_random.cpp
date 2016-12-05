//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "../include/utils/random.h"
#include "gtest/gtest.h"
    
class fixture_utils_random : public ::testing::Test 
{

protected:

   fixture_utils_random() {}
   virtual ~fixture_utils_random() {}
   virtual void SetUp() {}
   virtual void TearDown() {}
   
};

TEST_F(fixture_utils_random, get_random_integer) 
{
   unsigned int a = mzlib::get_random_integer();
   unsigned int b = mzlib::get_random_integer();
   unsigned int c = mzlib::get_random_integer();
   unsigned int d = mzlib::get_random_integer();
   ASSERT_NE(a, b);
   ASSERT_NE(b, c);
   ASSERT_NE(c, d);
}

TEST_F(fixture_utils_random, get_random_double_between_0_1) 
{
   double a = mzlib::get_random_double_between_0_1();
   double b = mzlib::get_random_double_between_0_1();
   double c = mzlib::get_random_double_between_0_1();
   double d = mzlib::get_random_double_between_0_1();
   ASSERT_NE(a, b);
   ASSERT_NE(b, c);
   ASSERT_NE(c, d);
}

TEST_F(fixture_utils_random, get_random_element) 
{
   std::map<int,int> example;
   example[0] = 0;
   example[1] = 2;
   example[2] = 3;
   std::map<int,int>::iterator does_it_work = mzlib::get_random_element(example);
   ASSERT_TRUE(true);
}
