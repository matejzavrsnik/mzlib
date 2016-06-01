//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "../include/utils_random.h"
#include "gtest/gtest.h"

using namespace mzlib::util;
    
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
   unsigned int a = get_random_integer();
   unsigned int b = get_random_integer();
   unsigned int c = get_random_integer();
   unsigned int d = get_random_integer();
   ASSERT_NE(a, b);
   ASSERT_NE(b, c);
   ASSERT_NE(c, d);
}

TEST_F(fixture_utils_random, get_random_double_between_0_1) 
{
   double a = get_random_double_between_0_1();
   double b = get_random_double_between_0_1();
   double c = get_random_double_between_0_1();
   double d = get_random_double_between_0_1();
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
   std::map<int,int>::iterator does_it_work = get_random_element(example);
   ASSERT_TRUE(true);
}
