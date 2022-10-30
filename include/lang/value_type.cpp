//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "value_type.h"

#include <vector>
#include <memory>
#include <optional>		
#include <iterator>

TEST(value_type, vector_iterator_int) 
{
   bool is_same = 
      std::is_same<
         mzlib::value_type<std::vector<int>::iterator>,
         int>
      ::value;
   ASSERT_TRUE(is_same);
}

TEST(value_type, shared_ptr_string) 
{
   bool is_same = 
      std::is_same<
         mzlib::value_type<std::shared_ptr<std::string>>,
         std::string>
      ::value;
   ASSERT_TRUE(is_same);
}

TEST(value_type, optional_double) 
{
   bool is_same = 
      std::is_same<
         mzlib::value_type<std::optional<double>>,
         double>
      ::value;
   ASSERT_TRUE(is_same);
}

TEST(value_type, int_pointer) 
{
   bool is_same = 
      std::is_same<
         mzlib::value_type<int*>,
         int>
      ::value;
   ASSERT_TRUE(is_same);
}

TEST(value_type, c_style_array_doubles) 
{
   bool is_same = 
      std::is_same<
         mzlib::value_type<double[3]>,
         double>
      ::value;
   ASSERT_TRUE(is_same);
}

namespace
{
   // silly function to test if it really works
   
   template<class Wrapper>
   mzlib::value_type<Wrapper> fun (
      Wrapper it, 
      mzlib::value_type<Wrapper> val)
   {
      return *it+val;
   }
}

TEST(value_type, function_using_it)
{
   double c_array[3] = {1.0, 2.0, 3.0};
   double c_array_changed = fun(std::begin(c_array), 4.0);
   ASSERT_EQ(5.0, c_array_changed);

   std::string str = "1234";
   char str_changed = fun(str.begin(), ' ');
   ASSERT_EQ('Q', str_changed);
   
   std::optional<int> optional_int = 3;
   int optional_int_changed = fun(optional_int, 2);
   ASSERT_EQ(5, optional_int_changed);
   
   std::shared_ptr<int> shared_int = std::make_shared<int>(3);
   int shared_int_changed = fun(shared_int, 2);
   ASSERT_EQ(5, shared_int_changed);
}