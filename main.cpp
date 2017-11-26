//
// Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "include/tools/parse_cli_arguments.h"

std::map<std::string, std::string> g_arguments;

int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv);
   ::testing::InitGoogleMock(&argc, argv);
   g_arguments = mzlib::parse_arguments(argc, argv);
   return RUN_ALL_TESTS();
}

/* TEMPLATE FOR NEW H FILES

//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_HEADER_H
#define MZLIB_HEADER_H
#include <stuff>
namespace mzlib {
} // namespace
#endif // MZLIB_HEADER_H

#ifdef MZLIB_HEADER_TESTS
#undef MZLIB_HEADER_TESTS

#endif // MZLIB_HEADER_TESTS

*/

/* TEMPLATE FOR NEW CPP FILES

//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

// Tests are implemented where functionality is implemented so that they are 
// easier to find while developing. This switch will turn on compilation of tests.

#define MZLIB_HEADER_TESTS_H
#include "include/the_thing.h"

*/