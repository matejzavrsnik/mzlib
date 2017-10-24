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
   #include "include/abstract/genetic_container.h"
   #include "include/abstract/genetic_object.h"
   #include "include/abstract/probabilator.h"
   #include "include/abstract/quadtree_it_bodies.h"
   #include "include/abstract/quadtree_it_masscentres.h"
   #include "include/abstract/markov_chain.h"
   #include "include/abstract/unique.h"
   #include "include/abstract/quadtree.h"

   #include "include/apps/aggregated_file_monitor.h"
   #include "include/apps/sentence_o_matic.h"
   #include "include/apps/sudoku.h"
   #include "include/apps/killer_sudoku.h"

   #include "include/filesystem/read_write_file.h"
   #include "include/filesystem/list_files.h"
   #include "include/filesystem/find_eof_position.h"
   #include "include/filesystem/is_meta_directory.h"
   #include "include/filesystem/filenamearise.h"
   #include "include/filesystem/extract_filename.h"

   #include "include/iterators/circular_next.h"
   #include "include/iterators/average.h"
   #include "include/iterators/distance_comparison.h"
   #include "include/iterators/conditional_find.h"
   #include "include/iterators/insert_if_unique.h"
   #include "include/iterators/fast_forward.h"
   #include "include/iterators/copy.h"
   #include "include/iterators/index_conversion.h"
   #include "include/iterators/is_last.h"
   #include "include/iterators/get_random.h"

   #include "include/joke/supersafe_number.h"

   #include "include/lang/optional.h"
   #include "include/lang/dbl.h"
   #include "include/lang/c64_basic_for.h"

   #include "include/laws/screen_rectangles.h"
   #include "include/laws/acceleration.h"
   #include "include/laws/constant_linear_acceleration.h"
   #include "include/laws/gravitation.h"
   #include "include/laws/vector_operations.h"

   #include "include/image_texture.h"

#undef MZLIB_BUILDING_TESTS