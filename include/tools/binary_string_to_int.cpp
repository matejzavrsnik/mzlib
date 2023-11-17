//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "binary_string_to_int.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(binary_string_to_int, cases)
{
   ASSERT_EQ(0, mzlib::binary_string_to_int("000"));
   ASSERT_EQ(1, mzlib::binary_string_to_int("001"));
   ASSERT_EQ(2, mzlib::binary_string_to_int("010"));
   ASSERT_EQ(3, mzlib::binary_string_to_int("011"));
   ASSERT_EQ(255, mzlib::binary_string_to_int("11111111"));
}