#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/tests.o \
	${OBJECTDIR}/tests/abstract/genetic_base.o \
	${OBJECTDIR}/tests/abstract/genetic_container.o \
	${OBJECTDIR}/tests/abstract/genetic_object.o \
	${OBJECTDIR}/tests/abstract/markov_chain.o \
	${OBJECTDIR}/tests/abstract/probabilator.o \
	${OBJECTDIR}/tests/abstract/quadtree.o \
	${OBJECTDIR}/tests/abstract/quadtree_it_bodies.o \
	${OBJECTDIR}/tests/abstract/quadtree_it_masscentres.o \
	${OBJECTDIR}/tests/abstract/symbol_sequences_in_pattern.o \
	${OBJECTDIR}/tests/abstract/unique.o \
	${OBJECTDIR}/tests/apps/aggregated_file_monitor.o \
	${OBJECTDIR}/tests/apps/killer_sudoku.o \
	${OBJECTDIR}/tests/apps/sentence_o_matic.o \
	${OBJECTDIR}/tests/apps/sudoku.o \
	${OBJECTDIR}/tests/filesystem/extract_filename.o \
	${OBJECTDIR}/tests/filesystem/filenamearise.o \
	${OBJECTDIR}/tests/filesystem/find_eof_position.o \
	${OBJECTDIR}/tests/filesystem/is_meta_directory.o \
	${OBJECTDIR}/tests/filesystem/list_files.o \
	${OBJECTDIR}/tests/filesystem/read_write_file.o \
	${OBJECTDIR}/tests/iterators/average.o \
	${OBJECTDIR}/tests/iterators/circular_next.o \
	${OBJECTDIR}/tests/iterators/conditional_find.o \
	${OBJECTDIR}/tests/iterators/copy.o \
	${OBJECTDIR}/tests/iterators/distance_comparison.o \
	${OBJECTDIR}/tests/iterators/fast_forward.o \
	${OBJECTDIR}/tests/iterators/get_random.o \
	${OBJECTDIR}/tests/iterators/index_conversion.o \
	${OBJECTDIR}/tests/iterators/insert_if_unique.o \
	${OBJECTDIR}/tests/iterators/is_last.o \
	${OBJECTDIR}/tests/lang/c64_basic_for.o \
	${OBJECTDIR}/tests/lang/dbl.o \
	${OBJECTDIR}/tests/lang/optional.o \
	${OBJECTDIR}/tests/laws/acceleration.o \
	${OBJECTDIR}/tests/laws/constant_linear_acceleration.o \
	${OBJECTDIR}/tests/laws/gravitation.o \
	${OBJECTDIR}/tests/laws/screen_rectangles.o \
	${OBJECTDIR}/tests/laws/vector_operations.o \
	${OBJECTDIR}/tests/nature/mass_centre.o \
	${OBJECTDIR}/tests/nature/units_strong_definitions.o \
	${OBJECTDIR}/tests/nature/universe.o \
	${OBJECTDIR}/tests/nature/vector.o \
	${OBJECTDIR}/tests/string/extract_vocabulary.o \
	${OBJECTDIR}/tests/string/get_substring.o \
	${OBJECTDIR}/tests/string/is_word_in_dictionary.o \
	${OBJECTDIR}/tests/string/remove_strings.o \
	${OBJECTDIR}/tests/string/sentence_assemblarator.o \
	${OBJECTDIR}/tests/string/split_on_delimiter.o \
	${OBJECTDIR}/tests/string/split_on_punctuation.o \
	${OBJECTDIR}/tests/string/string_case.o \
	${OBJECTDIR}/tests/string/string_replace.o \
	${OBJECTDIR}/tests/string/string_start_end.o \
	${OBJECTDIR}/tests/string/trim_punctuation.o \
	${OBJECTDIR}/tests/test_universe_performance.o \
	${OBJECTDIR}/tests/tools/add_to_tally.o \
	${OBJECTDIR}/tests/tools/copy_first_n_over_rest.o \
	${OBJECTDIR}/tests/tools/count_bits.o \
	${OBJECTDIR}/tests/tools/equidistant_sequence.o \
	${OBJECTDIR}/tests/tools/fast_min.o \
	${OBJECTDIR}/tests/tools/genetic.o \
	${OBJECTDIR}/tests/tools/index_coordinate_conversions.o \
	${OBJECTDIR}/tests/tools/next_lex_permutation.o \
	${OBJECTDIR}/tests/tools/number_of_decimals.o \
	${OBJECTDIR}/tests/tools/parse_cli_arguments.o \
	${OBJECTDIR}/tests/tools/random.o \
	${OBJECTDIR}/tests/tools/some_long_operation.o \
	${OBJECTDIR}/tests/tools/sort_map_by_value.o \
	${OBJECTDIR}/tests/tools/twoway_streambuf.o \
	${OBJECTDIR}/tests/tools/wagner_fischer_distance.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-std=c++1z
CXXFLAGS=-std=c++1z

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lgtest -lgtest_main -lgmock -lpthread

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mzlib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mzlib: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mzlib ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/tests.o: tests.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests.o tests.cpp

${OBJECTDIR}/tests/abstract/genetic_base.o: tests/abstract/genetic_base.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/abstract
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/abstract/genetic_base.o tests/abstract/genetic_base.cpp

${OBJECTDIR}/tests/abstract/genetic_container.o: tests/abstract/genetic_container.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/abstract
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/abstract/genetic_container.o tests/abstract/genetic_container.cpp

${OBJECTDIR}/tests/abstract/genetic_object.o: tests/abstract/genetic_object.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/abstract
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/abstract/genetic_object.o tests/abstract/genetic_object.cpp

${OBJECTDIR}/tests/abstract/markov_chain.o: tests/abstract/markov_chain.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/abstract
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/abstract/markov_chain.o tests/abstract/markov_chain.cpp

${OBJECTDIR}/tests/abstract/probabilator.o: tests/abstract/probabilator.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/abstract
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/abstract/probabilator.o tests/abstract/probabilator.cpp

${OBJECTDIR}/tests/abstract/quadtree.o: tests/abstract/quadtree.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/abstract
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/abstract/quadtree.o tests/abstract/quadtree.cpp

${OBJECTDIR}/tests/abstract/quadtree_it_bodies.o: tests/abstract/quadtree_it_bodies.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/abstract
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/abstract/quadtree_it_bodies.o tests/abstract/quadtree_it_bodies.cpp

${OBJECTDIR}/tests/abstract/quadtree_it_masscentres.o: tests/abstract/quadtree_it_masscentres.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/abstract
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/abstract/quadtree_it_masscentres.o tests/abstract/quadtree_it_masscentres.cpp

${OBJECTDIR}/tests/abstract/symbol_sequences_in_pattern.o: tests/abstract/symbol_sequences_in_pattern.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/abstract
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/abstract/symbol_sequences_in_pattern.o tests/abstract/symbol_sequences_in_pattern.cpp

${OBJECTDIR}/tests/abstract/unique.o: tests/abstract/unique.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/abstract
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/abstract/unique.o tests/abstract/unique.cpp

${OBJECTDIR}/tests/apps/aggregated_file_monitor.o: tests/apps/aggregated_file_monitor.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/apps
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/apps/aggregated_file_monitor.o tests/apps/aggregated_file_monitor.cpp

${OBJECTDIR}/tests/apps/killer_sudoku.o: tests/apps/killer_sudoku.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/apps
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/apps/killer_sudoku.o tests/apps/killer_sudoku.cpp

${OBJECTDIR}/tests/apps/sentence_o_matic.o: tests/apps/sentence_o_matic.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/apps
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/apps/sentence_o_matic.o tests/apps/sentence_o_matic.cpp

${OBJECTDIR}/tests/apps/sudoku.o: tests/apps/sudoku.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/apps
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/apps/sudoku.o tests/apps/sudoku.cpp

${OBJECTDIR}/tests/filesystem/extract_filename.o: tests/filesystem/extract_filename.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/filesystem
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/filesystem/extract_filename.o tests/filesystem/extract_filename.cpp

${OBJECTDIR}/tests/filesystem/filenamearise.o: tests/filesystem/filenamearise.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/filesystem
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/filesystem/filenamearise.o tests/filesystem/filenamearise.cpp

${OBJECTDIR}/tests/filesystem/find_eof_position.o: tests/filesystem/find_eof_position.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/filesystem
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/filesystem/find_eof_position.o tests/filesystem/find_eof_position.cpp

${OBJECTDIR}/tests/filesystem/is_meta_directory.o: tests/filesystem/is_meta_directory.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/filesystem
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/filesystem/is_meta_directory.o tests/filesystem/is_meta_directory.cpp

${OBJECTDIR}/tests/filesystem/list_files.o: tests/filesystem/list_files.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/filesystem
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/filesystem/list_files.o tests/filesystem/list_files.cpp

${OBJECTDIR}/tests/filesystem/read_write_file.o: tests/filesystem/read_write_file.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/filesystem
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/filesystem/read_write_file.o tests/filesystem/read_write_file.cpp

${OBJECTDIR}/tests/iterators/average.o: tests/iterators/average.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/iterators
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/iterators/average.o tests/iterators/average.cpp

${OBJECTDIR}/tests/iterators/circular_next.o: tests/iterators/circular_next.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/iterators
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/iterators/circular_next.o tests/iterators/circular_next.cpp

${OBJECTDIR}/tests/iterators/conditional_find.o: tests/iterators/conditional_find.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/iterators
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/iterators/conditional_find.o tests/iterators/conditional_find.cpp

${OBJECTDIR}/tests/iterators/copy.o: tests/iterators/copy.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/iterators
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/iterators/copy.o tests/iterators/copy.cpp

${OBJECTDIR}/tests/iterators/distance_comparison.o: tests/iterators/distance_comparison.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/iterators
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/iterators/distance_comparison.o tests/iterators/distance_comparison.cpp

${OBJECTDIR}/tests/iterators/fast_forward.o: tests/iterators/fast_forward.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/iterators
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/iterators/fast_forward.o tests/iterators/fast_forward.cpp

${OBJECTDIR}/tests/iterators/get_random.o: tests/iterators/get_random.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/iterators
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/iterators/get_random.o tests/iterators/get_random.cpp

${OBJECTDIR}/tests/iterators/index_conversion.o: tests/iterators/index_conversion.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/iterators
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/iterators/index_conversion.o tests/iterators/index_conversion.cpp

${OBJECTDIR}/tests/iterators/insert_if_unique.o: tests/iterators/insert_if_unique.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/iterators
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/iterators/insert_if_unique.o tests/iterators/insert_if_unique.cpp

${OBJECTDIR}/tests/iterators/is_last.o: tests/iterators/is_last.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/iterators
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/iterators/is_last.o tests/iterators/is_last.cpp

${OBJECTDIR}/tests/lang/c64_basic_for.o: tests/lang/c64_basic_for.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/lang
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/lang/c64_basic_for.o tests/lang/c64_basic_for.cpp

${OBJECTDIR}/tests/lang/dbl.o: tests/lang/dbl.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/lang
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/lang/dbl.o tests/lang/dbl.cpp

${OBJECTDIR}/tests/lang/optional.o: tests/lang/optional.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/lang
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/lang/optional.o tests/lang/optional.cpp

${OBJECTDIR}/tests/laws/acceleration.o: tests/laws/acceleration.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/laws
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/laws/acceleration.o tests/laws/acceleration.cpp

${OBJECTDIR}/tests/laws/constant_linear_acceleration.o: tests/laws/constant_linear_acceleration.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/laws
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/laws/constant_linear_acceleration.o tests/laws/constant_linear_acceleration.cpp

${OBJECTDIR}/tests/laws/gravitation.o: tests/laws/gravitation.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/laws
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/laws/gravitation.o tests/laws/gravitation.cpp

${OBJECTDIR}/tests/laws/screen_rectangles.o: tests/laws/screen_rectangles.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/laws
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/laws/screen_rectangles.o tests/laws/screen_rectangles.cpp

${OBJECTDIR}/tests/laws/vector_operations.o: tests/laws/vector_operations.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/laws
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/laws/vector_operations.o tests/laws/vector_operations.cpp

${OBJECTDIR}/tests/nature/mass_centre.o: tests/nature/mass_centre.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/nature
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/nature/mass_centre.o tests/nature/mass_centre.cpp

${OBJECTDIR}/tests/nature/units_strong_definitions.o: tests/nature/units_strong_definitions.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/nature
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/nature/units_strong_definitions.o tests/nature/units_strong_definitions.cpp

${OBJECTDIR}/tests/nature/universe.o: tests/nature/universe.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/nature
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/nature/universe.o tests/nature/universe.cpp

${OBJECTDIR}/tests/nature/vector.o: tests/nature/vector.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/nature
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/nature/vector.o tests/nature/vector.cpp

${OBJECTDIR}/tests/string/extract_vocabulary.o: tests/string/extract_vocabulary.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/string/extract_vocabulary.o tests/string/extract_vocabulary.cpp

${OBJECTDIR}/tests/string/get_substring.o: tests/string/get_substring.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/string/get_substring.o tests/string/get_substring.cpp

${OBJECTDIR}/tests/string/is_word_in_dictionary.o: tests/string/is_word_in_dictionary.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/string/is_word_in_dictionary.o tests/string/is_word_in_dictionary.cpp

${OBJECTDIR}/tests/string/remove_strings.o: tests/string/remove_strings.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/string/remove_strings.o tests/string/remove_strings.cpp

${OBJECTDIR}/tests/string/sentence_assemblarator.o: tests/string/sentence_assemblarator.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/string/sentence_assemblarator.o tests/string/sentence_assemblarator.cpp

${OBJECTDIR}/tests/string/split_on_delimiter.o: tests/string/split_on_delimiter.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/string/split_on_delimiter.o tests/string/split_on_delimiter.cpp

${OBJECTDIR}/tests/string/split_on_punctuation.o: tests/string/split_on_punctuation.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/string/split_on_punctuation.o tests/string/split_on_punctuation.cpp

${OBJECTDIR}/tests/string/string_case.o: tests/string/string_case.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/string/string_case.o tests/string/string_case.cpp

${OBJECTDIR}/tests/string/string_replace.o: tests/string/string_replace.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/string/string_replace.o tests/string/string_replace.cpp

${OBJECTDIR}/tests/string/string_start_end.o: tests/string/string_start_end.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/string/string_start_end.o tests/string/string_start_end.cpp

${OBJECTDIR}/tests/string/trim_punctuation.o: tests/string/trim_punctuation.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/string/trim_punctuation.o tests/string/trim_punctuation.cpp

${OBJECTDIR}/tests/test_universe_performance.o: tests/test_universe_performance.cpp
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/test_universe_performance.o tests/test_universe_performance.cpp

${OBJECTDIR}/tests/tools/add_to_tally.o: tests/tools/add_to_tally.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/tools/add_to_tally.o tests/tools/add_to_tally.cpp

${OBJECTDIR}/tests/tools/copy_first_n_over_rest.o: tests/tools/copy_first_n_over_rest.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/tools/copy_first_n_over_rest.o tests/tools/copy_first_n_over_rest.cpp

${OBJECTDIR}/tests/tools/count_bits.o: tests/tools/count_bits.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/tools/count_bits.o tests/tools/count_bits.cpp

${OBJECTDIR}/tests/tools/equidistant_sequence.o: tests/tools/equidistant_sequence.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/tools/equidistant_sequence.o tests/tools/equidistant_sequence.cpp

${OBJECTDIR}/tests/tools/fast_min.o: tests/tools/fast_min.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/tools/fast_min.o tests/tools/fast_min.cpp

${OBJECTDIR}/tests/tools/genetic.o: tests/tools/genetic.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/tools/genetic.o tests/tools/genetic.cpp

${OBJECTDIR}/tests/tools/index_coordinate_conversions.o: tests/tools/index_coordinate_conversions.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/tools/index_coordinate_conversions.o tests/tools/index_coordinate_conversions.cpp

${OBJECTDIR}/tests/tools/next_lex_permutation.o: tests/tools/next_lex_permutation.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/tools/next_lex_permutation.o tests/tools/next_lex_permutation.cpp

${OBJECTDIR}/tests/tools/number_of_decimals.o: tests/tools/number_of_decimals.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/tools/number_of_decimals.o tests/tools/number_of_decimals.cpp

${OBJECTDIR}/tests/tools/parse_cli_arguments.o: tests/tools/parse_cli_arguments.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/tools/parse_cli_arguments.o tests/tools/parse_cli_arguments.cpp

${OBJECTDIR}/tests/tools/random.o: tests/tools/random.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/tools/random.o tests/tools/random.cpp

${OBJECTDIR}/tests/tools/some_long_operation.o: tests/tools/some_long_operation.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/tools/some_long_operation.o tests/tools/some_long_operation.cpp

${OBJECTDIR}/tests/tools/sort_map_by_value.o: tests/tools/sort_map_by_value.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/tools/sort_map_by_value.o tests/tools/sort_map_by_value.cpp

${OBJECTDIR}/tests/tools/twoway_streambuf.o: tests/tools/twoway_streambuf.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/tools/twoway_streambuf.o tests/tools/twoway_streambuf.cpp

${OBJECTDIR}/tests/tools/wagner_fischer_distance.o: tests/tools/wagner_fischer_distance.cpp
	${MKDIR} -p ${OBJECTDIR}/tests/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/tools/wagner_fischer_distance.o tests/tools/wagner_fischer_distance.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
