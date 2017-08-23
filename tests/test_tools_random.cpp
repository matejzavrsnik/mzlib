//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "../include/tools/random.h"
#include "gtest/gtest.h"
    
class fixture_tools_random : public ::testing::Test 
{

protected:

   fixture_tools_random() {}
   virtual ~fixture_tools_random() {}
   virtual void SetUp() {}
   virtual void TearDown() {}
   
};

TEST_F(fixture_tools_random, get_random_integer) 
{
   unsigned int a = mzlib::get_random_integer();
   unsigned int b = mzlib::get_random_integer();
   unsigned int c = mzlib::get_random_integer();
   unsigned int d = mzlib::get_random_integer();
   ASSERT_NE(a, b);
   ASSERT_NE(b, c);
   ASSERT_NE(c, d);
}

TEST_F(fixture_tools_random, get_random_double_between_0_1) 
{
   double a = mzlib::get_random_double_between_0_1();
   double b = mzlib::get_random_double_between_0_1();
   double c = mzlib::get_random_double_between_0_1();
   double d = mzlib::get_random_double_between_0_1();
   ASSERT_NE(a, b);
   ASSERT_NE(b, c);
   ASSERT_NE(c, d);
}

TEST_F(fixture_tools_random, get_random_element) 
{
   std::map<int,int> example;
   example[0] = 0;
   example[1] = 2;
   example[2] = 3;
   std::map<int,int>::iterator random_element = mzlib::get_random_element(example);
   // how test if really random? :) I'll test instead if it returns any valid.
   ASSERT_TRUE(
      random_element->second == 0 ||
      random_element->second == 2 ||
      random_element->second == 3
   );
}
