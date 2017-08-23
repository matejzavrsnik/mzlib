//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

// gtest header for obvious reasons
#include "gtest/gtest.h"

// std stuff that tests might be using
#include <map>
#include <list>
#include <unordered_set>
#include <vector>
#include <algorithm>

// mzlib headers that tests might be using
#include "include/abstract/genetic_container.h"
// why not just include once, and in testing section? Because that way it might
// become important that files are included in correct order. Why not avoid the
// pain if it is simple to do?

// include custom mocks
#include "tests/mocks/mock_sdl.h"

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
   #include "include/abstract/symbol_sequences_in_pattern.h"
   #include "include/tools/is_word_in_dictionary.h"
   #include "include/tools/number_of_decimals.h"
   #include "include/lang/optional.h"
   #include "include/twoway_streambuf.h"
   #include "include/tools/genetic.h"
   #include "include/tools/fast_min.h"
   #include "include/tools/sentence_assemblarator.h"
   #include "include/tools/equidistant_sequence.h"
   #include "include/abstract/genetic_container.h"
   #include "include/abstract/genetic_object.h"
   #include "include/lang/dbl.h"
   #include "include/image_texture.h"
#undef MZLIB_BUILDING_TESTS