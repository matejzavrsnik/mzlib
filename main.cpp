//
// Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"
#include "include/utils/general.h"

std::map<std::string, std::string> g_arguments;

int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv);
   g_arguments = mzlib::parse_arguments(argc, argv);
   return RUN_ALL_TESTS();
}