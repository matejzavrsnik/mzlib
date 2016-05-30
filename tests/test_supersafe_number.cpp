//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"
#include "../include/cpucycle.h"

#define private public
#define protected public

#include "../include/supersafe_number.h"

    
class fixture_supersafe_number : public ::testing::Test 
{

protected:
   
   fixture_supersafe_number() {}
   virtual ~fixture_supersafe_number() {}

   virtual void SetUp() {}
   virtual void TearDown() {}
  
   typedef mzlib::csupersafe_number<int>    s_int;    // supersafe int
   typedef mzlib::csupersafe_number<double> s_double; // supersafe double

};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
TEST_F(fixture_supersafe_number, demo_test)
{
   s_int i_number = 12; // store number on creation, after that can't change
   //i_number = 13; because assignment doesn't compile
   s_int i_number2 = 13;
   //i_number = i_number2; and copy constructor doesn't compile
    
   s_int i_number3 = i_number + 2; // can do math operations though
   ASSERT_EQ(14, i_number3);
    
   // but if anyone or anything changed the original value ...
    
   // Though even if you hack access modifiers to get access to private member, it is still const
   // i_number.m_number = 14; might not even compile

   // will take some creativity
   int i;
   int* number_address = (int*)&i_number;
   number_address += sizeof(std::vector<double>) / sizeof(int); // get access to the protected number
   ASSERT_NO_THROW(i = i_number);
   *number_address = 14; // modify it outside the class that protects it
   ASSERT_THROW(i = i_number, mzlib::compromised_number); // on access, it will detect the modification and throw
}
#pragma GCC diagnostic pop

TEST_F(fixture_supersafe_number, construction) 
{
   // assignment does not change the value it was initialised with
   s_int i_number(12);
   ASSERT_EQ(12, i_number);
   s_double d_number = 12.12;
   ASSERT_DOUBLE_EQ(12.12, d_number);
}

TEST_F(fixture_supersafe_number, keys_are_different) 
{
   // each instantiation has different key to calculate check code
   s_int number1 = 13;
   s_int number2 = 130;
   s_int number3 = 1300;
    
   ASSERT_NE(number1.m_keys[0], number1.m_keys[1]);
   ASSERT_NE(number2.m_keys[0], number2.m_keys[1]);
   ASSERT_NE(number3.m_keys[0], number3.m_keys[1]);
    
   ASSERT_NE(number1.m_keys[0], number2.m_keys[0]);
   ASSERT_NE(number2.m_keys[0], number3.m_keys[0]);
   ASSERT_NE(number3.m_keys[0], number1.m_keys[0]);
    
   ASSERT_NE(number1.m_keys[1], number2.m_keys[1]);
   ASSERT_NE(number2.m_keys[1], number3.m_keys[1]);
   ASSERT_NE(number3.m_keys[1], number1.m_keys[1]);
    
   s_double dnumber1 = 13.3;
   s_double dnumber2 = 130.3;
   s_double dnumber3 = 1300.3;
    
   ASSERT_NE(dnumber1.m_keys[0], dnumber1.m_keys[1]);
   ASSERT_NE(dnumber2.m_keys[0], dnumber2.m_keys[1]);
   ASSERT_NE(dnumber3.m_keys[0], dnumber3.m_keys[1]);
    
   ASSERT_NE(dnumber1.m_keys[0], dnumber2.m_keys[0]);
   ASSERT_NE(dnumber2.m_keys[0], dnumber3.m_keys[0]);
   ASSERT_NE(dnumber3.m_keys[0], dnumber1.m_keys[0]);
    
   ASSERT_NE(dnumber1.m_keys[1], dnumber2.m_keys[1]);
   ASSERT_NE(dnumber2.m_keys[1], dnumber3.m_keys[1]);
   ASSERT_NE(dnumber3.m_keys[1], dnumber1.m_keys[1]);
}

TEST_F(fixture_supersafe_number, conversion_to_raw_number) 
{
   s_int number = 13;
   int stored = number;
   ASSERT_EQ(13, stored);
    
   s_double dnumber = 13.13;
   double dstored = dnumber;
   ASSERT_DOUBLE_EQ(13.13, dstored);
}

TEST_F(fixture_supersafe_number, computation) 
{
   s_int number1 = 13;
   s_int number2 = number1 + 1; // with raw integer
   s_int number3 = number1 + number2; // with another safe integer
    
   ASSERT_EQ(13, number1);
   ASSERT_EQ(14, number2);
   ASSERT_EQ(27, number3);
    
   s_double dnumber1 = 13.13;
   s_double dnumber2 = dnumber1 + 1.01; // with raw integer
   s_double dnumber3 = dnumber1 + dnumber2; // with another safe integer
    
   ASSERT_DOUBLE_EQ(13.13, dnumber1);
   ASSERT_DOUBLE_EQ(14.14, dnumber2);
   ASSERT_DOUBLE_EQ(27.27, dnumber3);
}
