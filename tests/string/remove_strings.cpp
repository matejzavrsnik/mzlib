//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"
#include "gtest/gtest_prod.h"

// Tests are implemented where functionality is implemented so that they are 
// easier to find while developing. This switch will turn on compilation of tests.

#define MZLIB_REMOVE_STRINGS_TESTS_H

   #include "../../include/string/remove_strings.h"

#undef MZLIB_REMOVE_STRINGS_TESTS_H