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

#define MZLIB_ADD_TO_TALLY_TESTS_H

   #include "../../include/tools/add_to_tally.h"

#undef MZLIB_ADD_TO_TALLY_TESTS_H