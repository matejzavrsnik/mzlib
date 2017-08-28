//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_SUPERSAFE_NUMBER_H
#define MZLIB_SUPERSAFE_NUMBER_H

#include <vector>
#include <exception>

#include "../tools/random.h"
#include "../lang/dbl.h"

namespace mzlib {

class compromised_number : public std::exception {};

template <typename T>
class supersafe_number
{

private:

   const std::vector<double> m_keys;
   // not the first data in memory layout
   const T m_number; // important value
   const std::vector<double> m_controls;

   double calculate_control_value (const unsigned short index) const 
   {
       return (m_number + m_keys[index]);
   }

public:

   supersafe_number (const T number) :
      m_keys{
         get_random_double(),
         get_random_double()},
      m_number{number},
      m_controls{
         calculate_control_value(0),
         calculate_control_value(1)}
   {
   }

   operator T () const
   {
      if (dbl(calculate_control_value(0)).equals(m_controls[0]) &&
          dbl(calculate_control_value(1)).equals(m_controls[1]))
      {
         // passed integrity control!
         return m_number;
      }
      else {
         // Didn't pass integrity control!
         // Nice try, Illuminati! HHAHAahha!!!11
         throw compromised_number(); // Abort the mission!
      }
   }
   
#ifdef FRIEND_TEST
   FRIEND_TEST(supersafe_number, keys_are_different);
#endif

};

} // namespace

#endif /* MZLIB_SUPERSAFE_NUMBER_H */

#ifdef MZLIB_BUILDING_TESTS

#ifndef MZLIB_SUPERSAFE_NUMBER_TESTS_H
#define MZLIB_SUPERSAFE_NUMBER_TESTS_H

namespace mzlib {

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
TEST(supersafe_number, demo_test)
{
   mzlib::supersafe_number<int> i_number = 12; // store number on creation, after that can't change
   //i_number = 13; because assignment doesn't compile
   mzlib::supersafe_number<int> i_number2 = 13;
   //i_number = i_number2; and copy constructor doesn't compile
    
   mzlib::supersafe_number<int> i_number3 = i_number + 2; // can do math operations though
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

TEST(supersafe_number, construction) 
{
   // assignment does not change the value it was initialised with
   mzlib::supersafe_number<int> i_number(12);
   ASSERT_EQ(12, i_number);
   mzlib::supersafe_number<double> d_number = 12.12;
   ASSERT_DOUBLE_EQ(12.12, d_number);
}

TEST(supersafe_number, keys_are_different) 
{
   // each instantiation has different key to calculate check code
   mzlib::supersafe_number<int> number1 = 13;
   mzlib::supersafe_number<int> number2 = 130;
   mzlib::supersafe_number<int> number3 = 1300;
    
   ASSERT_NE(number1.m_keys[0], number1.m_keys[1]);
   ASSERT_NE(number2.m_keys[0], number2.m_keys[1]);
   ASSERT_NE(number3.m_keys[0], number3.m_keys[1]);
    
   ASSERT_NE(number1.m_keys[0], number2.m_keys[0]);
   ASSERT_NE(number2.m_keys[0], number3.m_keys[0]);
   ASSERT_NE(number3.m_keys[0], number1.m_keys[0]);
    
   ASSERT_NE(number1.m_keys[1], number2.m_keys[1]);
   ASSERT_NE(number2.m_keys[1], number3.m_keys[1]);
   ASSERT_NE(number3.m_keys[1], number1.m_keys[1]);
    
   mzlib::supersafe_number<double> dnumber1 = 13.3;
   mzlib::supersafe_number<double> dnumber2 = 130.3;
   mzlib::supersafe_number<double> dnumber3 = 1300.3;
    
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

TEST(supersafe_number, conversion_to_raw_number) 
{
   mzlib::supersafe_number<int> number = 13;
   int stored = number;
   ASSERT_EQ(13, stored);
    
   mzlib::supersafe_number<double> dnumber = 13.13;
   double dstored = dnumber;
   ASSERT_DOUBLE_EQ(13.13, dstored);
}

TEST(supersafe_number, computation) 
{
   mzlib::supersafe_number<int> number1 = 13;
   mzlib::supersafe_number<int> number2 = number1 + 1; // with raw integer
   mzlib::supersafe_number<int> number3 = number1 + number2; // with another safe integer
    
   ASSERT_EQ(13, number1);
   ASSERT_EQ(14, number2);
   ASSERT_EQ(27, number3);
    
   mzlib::supersafe_number<double> dnumber1 = 13.13;
   mzlib::supersafe_number<double> dnumber2 = dnumber1 + 1.01; // with raw integer
   mzlib::supersafe_number<double> dnumber3 = dnumber1 + dnumber2; // with another safe integer
    
   ASSERT_DOUBLE_EQ(13.13, dnumber1);
   ASSERT_DOUBLE_EQ(14.14, dnumber2);
   ASSERT_DOUBLE_EQ(27.27, dnumber3);
}

} // namespace

#endif // MZLIB_SUPERSAFE_NUMBER_TESTS_H

#endif // MZLIB_BUILDING_TESTS
