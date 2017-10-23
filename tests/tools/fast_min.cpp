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

#define MZLIB_FAST_MIN_TESTS_H

   #include "../../include/tools/fast_min.h"

#undef MZLIB_FAST_MIN_TESTS_H