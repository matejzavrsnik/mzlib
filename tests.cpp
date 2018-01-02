//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

// gtest header for obvious reasons
#include "gtest/gtest.h"
#include "gtest/gtest_prod.h"

// command line options
#include "options.h"

// std stuff that tests might be using
#include <map>
#include <list>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <fstream>

// mzlib headers that tests might be using
// two reasons for files to be here:
//   - headers have circular dependencies and can't just be included in correct
//     order in section where tests are included
//   - functionality is used in tests, but has no tests itself *alarm sounds*
#include "include/abstract/genetic_container.h"
#include "include/nature/units.h"
#include "include/abstract/quadtree.h"

using namespace mzlib::units;

// why not just include once, and in testing section? Because that way it might
// become important that files are included in correct order. Why not avoid the
// pain if it is simple to do?

// include custom mocks


// the main thing: tests themselves
// tests are implemented where functionality is implemented so that they are 
// easier to find while developing
#define MZLIB_BUILDING_TESTS
// Idea I got as well is to just use the include guards from gtest.h header
// instead of inventing MZLIB_BUILDING_TESTS. That would to automatically determine 
// if code is compiled in the context of tests or production code. I decided against 
// that because you might want to use mzlib headers in tests for something else 
// that is merely using mzlib. You would be surprised to see mzlib tests themselves
// suddenly appear amongst the tests you wrote for that thing only.

   #include "include/joke/supersafe_number.h"

#undef MZLIB_BUILDING_TESTS