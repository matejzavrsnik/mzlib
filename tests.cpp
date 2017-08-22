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
#include "include/lang/optional.h"
#include "include/abstract/genetic_container.h"

// the main thing: tests themselves
// tests are implemented where functionality is implemented so that they are 
// easier to find while developing
#define MZLIB_BUILDING_TESTS
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
#undef MZLIB_BUILDING_TESTS