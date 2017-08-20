//
// Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "include/tools/general.h"

std::map<std::string, std::string> g_arguments;

int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv);
   ::testing::InitGoogleMock(&argc, argv);
   g_arguments = mzlib::parse_arguments(argc, argv);
   return RUN_ALL_TESTS();
}

/* TEMPLATE FOR NEW FILES

//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef HEADER_H
#define HEADER_H
#include <stuff>
namespace mzlib {
} // namespace
#endif // HEADER_H
#ifdef MZLIB_BUILDING_TESTS
#endif // MZLIB_BUILDING_TESTS

*/