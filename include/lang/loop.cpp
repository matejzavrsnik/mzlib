//
// Copyright (c) 2019 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "loop.h"
#include "../mocks/mock_methods.h"

class fixture_loop : public ::testing::Test 
{

protected:

   fixture_loop () {}
   virtual ~fixture_loop () {}
   virtual void SetUp () {}
   virtual void TearDown () {}

   mock_methods mock_object;
   
   int arg1 = 3;
   int arg2 = 7;

   int from = 5;
   int to = from + 4;
   
   void set_up_void_int_to_expect_from_to_calls()
   {
      ::testing::InSequence _;
      for(int arg = from; arg <= to; ++arg)
      {
         EXPECT_CALL(mock_object, void_int(arg)).Times(1);
      }
   }
};

TEST_F(fixture_loop, times_function_zero_parameters) 
{
   EXPECT_CALL(mock_object, void_void()).Times(7);
   
   mzlib::loop::times(7)
      (free_void_void);
}

TEST_F(fixture_loop, times_function_one_parameter) 
{
   EXPECT_CALL(mock_object, void_int(arg1)).Times(7);
   
   mzlib::loop::times(7)
      (free_void_int, arg1);
}

TEST_F(fixture_loop, times_function_two_parameters) 
{
   EXPECT_CALL(mock_object, void_int_int(arg1, arg2)).Times(7);
   
   mzlib::loop::times(7)
      (free_void_int_int, arg1, arg2);
}

TEST_F(fixture_loop, times_member_zero_parameters) 
{
   EXPECT_CALL(mock_object, void_void()).Times(7);
   
   mzlib::loop::times(7)
      (&mock_methods::void_void, mock_object);
}

TEST_F(fixture_loop, times_member_one_parameters) 
{
   EXPECT_CALL(mock_object, void_int(arg1)).Times(7);
   
   mzlib::loop::times(7)
      (&mock_methods::void_int, mock_object, arg1);
}

TEST_F(fixture_loop, times_member_two_parameters) 
{
   EXPECT_CALL(mock_object, void_int_int(arg1, arg2)).Times(7);
   
   mzlib::loop::times(7)
      (&mock_methods::void_int_int, mock_object, arg1, arg2);
}

// currently unsupported
//TEST_F(fixture_loop, times_bind) 
//{
//   EXPECT_CALL(mock_object, void_int(arg1)).Times(7);
//
//   using namespace std::placeholders;
//   mzlib::loop::times(7)
//      (std::bind(&mock_methods::void_int, &mock_object, _1, arg1));
//}

TEST_F(fixture_loop, times_lambda_zero_parameters) 
{
   EXPECT_CALL(mock_object, void_int(arg1)).Times(7);
   
   mzlib::loop::times(7)
      ([this]() 
      { 
         mock_object.void_int(arg1); 
      });
}

TEST_F(fixture_loop, times_lambda_one_parameter) 
{
   EXPECT_CALL(mock_object, void_int(arg1)).Times(7);
   
   mzlib::loop::times(7)
      ([this](int i) 
      { 
         mock_object.void_int(i); 
      },
      arg1);
}

TEST_F(fixture_loop, times_lambda_two_parameters) 
{
   EXPECT_CALL(mock_object, void_int_int(arg1, arg2)).Times(7);
   
   mzlib::loop::times(7)
      ([this](int i, int j) 
      { 
         mock_object.void_int_int(i, j); 
      },
      arg1, arg2);
}

TEST_F(fixture_loop, from_to_function_one_parameter) 
{
   {
      ::testing::InSequence _;
      for(int arg = from; arg <= to; ++arg)
      {
         EXPECT_CALL(mock_object, void_int(arg)).Times(1);
      }
   }
   
   mzlib::loop::from_to(from, to)
      (free_void_int);
}

TEST_F(fixture_loop, from_to_lambda_one_parameter) 
{
   {
      ::testing::InSequence _;
      for(int arg = from; arg <= to; ++arg)
      {
         EXPECT_CALL(mock_object, void_int(arg)).Times(1);
      }
   }
   
   mzlib::loop::from_to(from, to)
      ([this](int& arg) 
      { 
         mock_object.void_int(arg); 
      });
}

TEST_F(fixture_loop, from_to_function_two_parameters_bind_one)
{
   const int bound_value = 16;
   
   {
      ::testing::InSequence _;
      for(int arg = from; arg <= to; ++arg)
      {
         EXPECT_CALL(mock_object, void_int_int(arg, bound_value)).Times(1);
      }
   }

   using namespace std::placeholders;
   mzlib::loop::from_to(from, to)
      (std::bind(free_void_int_int, _1, bound_value));
}

TEST_F(fixture_loop, from_to_function_three_parameters_bind_two)
{
   const int bound1 = 16;
   const int bound2 = 17;
   
   {
      ::testing::InSequence _;
      for(int arg = from; arg <= to; ++arg)
      {
         EXPECT_CALL(mock_object, void_int_int_int(bound1, arg, bound2)).Times(1);
      }
   }

   using namespace std::placeholders;
   mzlib::loop::from_to(from, to)
      (std::bind(free_void_int_int_int, bound1, _1, bound2));
}

TEST_F(fixture_loop, from_to_member_two_parameters_bind_one)
{
   const int bound_value = 16;
   
   {
      ::testing::InSequence _;
      for(int arg = from; arg <= to; ++arg)
      {
         EXPECT_CALL(mock_object, void_int_int(arg, bound_value)).Times(1);
      }
   }

   using namespace std::placeholders;
   mzlib::loop::from_to(from, to)
      (std::bind(&mock_methods::void_int_int, &mock_object, _1, bound_value));
}

TEST_F(fixture_loop, from_to_member_three_parameters_bind_two)
{
   const int bound1 = 16;
   const int bound2 = 17;
   
   {
      ::testing::InSequence _;
      for(int arg = from; arg <= to; ++arg)
      {
         EXPECT_CALL(mock_object, void_int_int_int(bound1, arg, bound2)).Times(1);
      }
   }

   using namespace std::placeholders;
   mzlib::loop::from_to(from, to)
      (std::bind(&mock_methods::void_int_int_int, &mock_object, bound1, _1, bound2));
}
