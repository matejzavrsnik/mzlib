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

TEST(value_type, vector_iterator_int) 
{
   bool is_same = 
      std::is_same<
         mzlib::ValueType<std::vector<int>::iterator>,
         int>
      ::value;
   ASSERT_TRUE(is_same);
}

TEST(value_type, shared_ptr_string) 
{
   bool is_same = 
      std::is_same<
         mzlib::ValueType<std::shared_ptr<std::string>>,
         std::string>
      ::value;
   ASSERT_TRUE(is_same);
}

TEST(value_type, optional_double) 
{
   bool is_same = 
      std::is_same<
         mzlib::ValueType<std::optional<double>>,
         double>
      ::value;
   ASSERT_TRUE(is_same);
}
