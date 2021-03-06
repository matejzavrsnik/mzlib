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
	${OBJECTDIR}/include/abstract/probabilator.o \
	${OBJECTDIR}/include/abstract/symbol_sequences_in_pattern.o \
	${OBJECTDIR}/include/abstract/unique.o \
	${OBJECTDIR}/include/apps/aggregated_file_monitor.o \
	${OBJECTDIR}/include/apps/filter_haikus.o \
	${OBJECTDIR}/include/apps/killer_sudoku.o \
	${OBJECTDIR}/include/apps/necklace_splitting.o \
	${OBJECTDIR}/include/apps/sentence_o_matic.o \
	${OBJECTDIR}/include/apps/sudoku.o \
	${OBJECTDIR}/include/apps/syllables.o \
	${OBJECTDIR}/include/extension/libxmlpp/libxmlpp.o \
	${OBJECTDIR}/include/extension/libxmlpp/libxmlpp_datashelf.o \
	${OBJECTDIR}/include/extension/sdl/sdl_image_texture.o \
	${OBJECTDIR}/include/filesystem/extract_filename.o \
	${OBJECTDIR}/include/filesystem/filenamearise.o \
	${OBJECTDIR}/include/filesystem/find_eof_position.o \
	${OBJECTDIR}/include/filesystem/is_meta_directory.o \
	${OBJECTDIR}/include/filesystem/list_files.o \
	${OBJECTDIR}/include/filesystem/read_write_file.o \
	${OBJECTDIR}/include/greatest_hits/genetic_base.o \
	${OBJECTDIR}/include/greatest_hits/genetic_container.o \
	${OBJECTDIR}/include/greatest_hits/genetic_object.o \
	${OBJECTDIR}/include/greatest_hits/longest_common_subsequence.o \
	${OBJECTDIR}/include/greatest_hits/markov_chain.o \
	${OBJECTDIR}/include/greatest_hits/median_maintenance.o \
	${OBJECTDIR}/include/greatest_hits/next_lex_permutation.o \
	${OBJECTDIR}/include/greatest_hits/quadtree.o \
	${OBJECTDIR}/include/greatest_hits/quadtree_it_bodies.o \
	${OBJECTDIR}/include/greatest_hits/quadtree_it_masscentres.o \
	${OBJECTDIR}/include/greatest_hits/travelling_salesman_problem.o \
	${OBJECTDIR}/include/greatest_hits/wagner_fischer_distance.o \
	${OBJECTDIR}/include/iterators/average.o \
	${OBJECTDIR}/include/iterators/circular_next.o \
	${OBJECTDIR}/include/iterators/contains_range.o \
	${OBJECTDIR}/include/iterators/copy.o \
	${OBJECTDIR}/include/iterators/copy_to_nested.o \
	${OBJECTDIR}/include/iterators/distance_comparison.o \
	${OBJECTDIR}/include/iterators/fast_forward.o \
	${OBJECTDIR}/include/iterators/find_in.o \
	${OBJECTDIR}/include/iterators/find_subsequence.o \
	${OBJECTDIR}/include/iterators/get_random.o \
	${OBJECTDIR}/include/iterators/index_conversion.o \
	${OBJECTDIR}/include/iterators/insert_if_unique.o \
	${OBJECTDIR}/include/iterators/is_last.o \
	${OBJECTDIR}/include/iterators/is_trivial_repetition.o \
	${OBJECTDIR}/include/iterators/nested_iteration.o \
	${OBJECTDIR}/include/iterators/range.o \
	${OBJECTDIR}/include/iterators/range_is_within.o \
	${OBJECTDIR}/include/iterators/range_iterator.o \
	${OBJECTDIR}/include/iterators/remove_element.o \
	${OBJECTDIR}/include/iterators/remove_from.o \
	${OBJECTDIR}/include/iterators/repeated_ranges.o \
	${OBJECTDIR}/include/iterators/starts_with.o \
	${OBJECTDIR}/include/joke/supersafe_number.o \
	${OBJECTDIR}/include/lang/c64_basic_for.o \
	${OBJECTDIR}/include/lang/concepts.o \
	${OBJECTDIR}/include/lang/dbl.o \
	${OBJECTDIR}/include/lang/loop.o \
	${OBJECTDIR}/include/lang/optional.o \
	${OBJECTDIR}/include/lang/optionally_functional.o \
	${OBJECTDIR}/include/lang/value_type.o \
	${OBJECTDIR}/include/laws/acceleration.o \
	${OBJECTDIR}/include/laws/constant_linear_acceleration.o \
	${OBJECTDIR}/include/laws/gravitation.o \
	${OBJECTDIR}/include/laws/linear_interpolation.o \
	${OBJECTDIR}/include/laws/matrix_operations.o \
	${OBJECTDIR}/include/laws/matrix_operations_alternative.o \
	${OBJECTDIR}/include/laws/screen_rectangles.o \
	${OBJECTDIR}/include/laws/set_difference.o \
	${OBJECTDIR}/include/laws/set_intersection.o \
	${OBJECTDIR}/include/laws/vector_operations.o \
	${OBJECTDIR}/include/nature/average_plot.o \
	${OBJECTDIR}/include/nature/mass_centre.o \
	${OBJECTDIR}/include/nature/matrix.o \
	${OBJECTDIR}/include/nature/parity.o \
	${OBJECTDIR}/include/nature/plot_operations.o \
	${OBJECTDIR}/include/nature/units_strong_definitions.o \
	${OBJECTDIR}/include/nature/universe.o \
	${OBJECTDIR}/include/nature/vector.o \
	${OBJECTDIR}/include/string/all_words_appear.o \
	${OBJECTDIR}/include/string/are_subsentences.o \
	${OBJECTDIR}/include/string/are_substrings.o \
	${OBJECTDIR}/include/string/case.o \
	${OBJECTDIR}/include/string/case_insensitive_equal.o \
	${OBJECTDIR}/include/string/extract_vocabulary.o \
	${OBJECTDIR}/include/string/get_substring.o \
	${OBJECTDIR}/include/string/is_end_start_of_the_word.o \
	${OBJECTDIR}/include/string/is_just_whitespace.o \
	${OBJECTDIR}/include/string/is_subsentence.o \
	${OBJECTDIR}/include/string/is_substring.o \
	${OBJECTDIR}/include/string/is_word_delimiter.o \
	${OBJECTDIR}/include/string/is_word_in_dictionary.o \
	${OBJECTDIR}/include/string/join.o \
	${OBJECTDIR}/include/string/remove_substrings.o \
	${OBJECTDIR}/include/string/remove_words.o \
	${OBJECTDIR}/include/string/replace.o \
	${OBJECTDIR}/include/string/replace_all_between.o \
	${OBJECTDIR}/include/string/sentence_assemblarator.o \
	${OBJECTDIR}/include/string/split.o \
	${OBJECTDIR}/include/string/split_on_punctuation.o \
	${OBJECTDIR}/include/string/string_view_find.o \
	${OBJECTDIR}/include/string/trim.o \
	${OBJECTDIR}/include/string/trim_nonalpha.o \
	${OBJECTDIR}/include/tools/add_to_tally.o \
	${OBJECTDIR}/include/tools/all_equal.o \
	${OBJECTDIR}/include/tools/copy_first_n_over_rest.o \
	${OBJECTDIR}/include/tools/count_bits.o \
	${OBJECTDIR}/include/tools/datashelf_extended.o \
	${OBJECTDIR}/include/tools/datashelf_foundation.o \
	${OBJECTDIR}/include/tools/equidistant_sequence.o \
	${OBJECTDIR}/include/tools/fast_min.o \
	${OBJECTDIR}/include/tools/find_index_insert.o \
	${OBJECTDIR}/include/tools/fluent_datashelf.o \
	${OBJECTDIR}/include/tools/genetic.o \
	${OBJECTDIR}/include/tools/get_if_exists.o \
	${OBJECTDIR}/include/tools/index_coordinate_conversions.o \
	${OBJECTDIR}/include/tools/nested_vector.o \
	${OBJECTDIR}/include/tools/number_of_decimals.o \
	${OBJECTDIR}/include/tools/parse_cli_arguments.o \
	${OBJECTDIR}/include/tools/random.o \
	${OBJECTDIR}/include/tools/random_with_parity.o \
	${OBJECTDIR}/include/tools/relocate.o \
	${OBJECTDIR}/include/tools/rememberator.o \
	${OBJECTDIR}/include/tools/simple_datetime.o \
	${OBJECTDIR}/include/tools/some_long_operation.o \
	${OBJECTDIR}/include/tools/sort_map_by_value.o \
	${OBJECTDIR}/include/tools/time_operations.o \
	${OBJECTDIR}/include/tools/twoway_streambuf.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/tests/matrix_operations_performance.o \
	${OBJECTDIR}/tests/std_maps_performance.o \
	${OBJECTDIR}/tests/test_repeated_ranges_performance.o \
	${OBJECTDIR}/tests/test_universe_performance.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-std=c++2a -fconcepts
CXXFLAGS=-std=c++2a -fconcepts

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lpthread -lgtest -lgtest_main -lgmock -lglib-2.0 -lglibmm-2.4 -lxml++-3.0

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mzlib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mzlib: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mzlib ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/include/abstract/probabilator.o: include/abstract/probabilator.cpp
	${MKDIR} -p ${OBJECTDIR}/include/abstract
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/abstract/probabilator.o include/abstract/probabilator.cpp

${OBJECTDIR}/include/abstract/symbol_sequences_in_pattern.o: include/abstract/symbol_sequences_in_pattern.cpp
	${MKDIR} -p ${OBJECTDIR}/include/abstract
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/abstract/symbol_sequences_in_pattern.o include/abstract/symbol_sequences_in_pattern.cpp

${OBJECTDIR}/include/abstract/unique.o: include/abstract/unique.cpp
	${MKDIR} -p ${OBJECTDIR}/include/abstract
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/abstract/unique.o include/abstract/unique.cpp

${OBJECTDIR}/include/apps/aggregated_file_monitor.o: include/apps/aggregated_file_monitor.cpp
	${MKDIR} -p ${OBJECTDIR}/include/apps
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/apps/aggregated_file_monitor.o include/apps/aggregated_file_monitor.cpp

${OBJECTDIR}/include/apps/filter_haikus.o: include/apps/filter_haikus.cpp
	${MKDIR} -p ${OBJECTDIR}/include/apps
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/apps/filter_haikus.o include/apps/filter_haikus.cpp

${OBJECTDIR}/include/apps/killer_sudoku.o: include/apps/killer_sudoku.cpp
	${MKDIR} -p ${OBJECTDIR}/include/apps
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/apps/killer_sudoku.o include/apps/killer_sudoku.cpp

${OBJECTDIR}/include/apps/necklace_splitting.o: include/apps/necklace_splitting.cpp
	${MKDIR} -p ${OBJECTDIR}/include/apps
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/apps/necklace_splitting.o include/apps/necklace_splitting.cpp

${OBJECTDIR}/include/apps/sentence_o_matic.o: include/apps/sentence_o_matic.cpp
	${MKDIR} -p ${OBJECTDIR}/include/apps
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/apps/sentence_o_matic.o include/apps/sentence_o_matic.cpp

${OBJECTDIR}/include/apps/sudoku.o: include/apps/sudoku.cpp
	${MKDIR} -p ${OBJECTDIR}/include/apps
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/apps/sudoku.o include/apps/sudoku.cpp

${OBJECTDIR}/include/apps/syllables.o: include/apps/syllables.cpp
	${MKDIR} -p ${OBJECTDIR}/include/apps
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/apps/syllables.o include/apps/syllables.cpp

${OBJECTDIR}/include/extension/libxmlpp/libxmlpp.o: include/extension/libxmlpp/libxmlpp.cpp
	${MKDIR} -p ${OBJECTDIR}/include/extension/libxmlpp
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/extension/libxmlpp/libxmlpp.o include/extension/libxmlpp/libxmlpp.cpp

${OBJECTDIR}/include/extension/libxmlpp/libxmlpp_datashelf.o: include/extension/libxmlpp/libxmlpp_datashelf.cpp
	${MKDIR} -p ${OBJECTDIR}/include/extension/libxmlpp
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/extension/libxmlpp/libxmlpp_datashelf.o include/extension/libxmlpp/libxmlpp_datashelf.cpp

${OBJECTDIR}/include/extension/sdl/sdl_image_texture.o: include/extension/sdl/sdl_image_texture.cpp
	${MKDIR} -p ${OBJECTDIR}/include/extension/sdl
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/extension/sdl/sdl_image_texture.o include/extension/sdl/sdl_image_texture.cpp

${OBJECTDIR}/include/filesystem/extract_filename.o: include/filesystem/extract_filename.cpp
	${MKDIR} -p ${OBJECTDIR}/include/filesystem
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/filesystem/extract_filename.o include/filesystem/extract_filename.cpp

${OBJECTDIR}/include/filesystem/filenamearise.o: include/filesystem/filenamearise.cpp
	${MKDIR} -p ${OBJECTDIR}/include/filesystem
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/filesystem/filenamearise.o include/filesystem/filenamearise.cpp

${OBJECTDIR}/include/filesystem/find_eof_position.o: include/filesystem/find_eof_position.cpp
	${MKDIR} -p ${OBJECTDIR}/include/filesystem
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/filesystem/find_eof_position.o include/filesystem/find_eof_position.cpp

${OBJECTDIR}/include/filesystem/is_meta_directory.o: include/filesystem/is_meta_directory.cpp
	${MKDIR} -p ${OBJECTDIR}/include/filesystem
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/filesystem/is_meta_directory.o include/filesystem/is_meta_directory.cpp

${OBJECTDIR}/include/filesystem/list_files.o: include/filesystem/list_files.cpp
	${MKDIR} -p ${OBJECTDIR}/include/filesystem
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/filesystem/list_files.o include/filesystem/list_files.cpp

${OBJECTDIR}/include/filesystem/read_write_file.o: include/filesystem/read_write_file.cpp
	${MKDIR} -p ${OBJECTDIR}/include/filesystem
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/filesystem/read_write_file.o include/filesystem/read_write_file.cpp

${OBJECTDIR}/include/greatest_hits/genetic_base.o: include/greatest_hits/genetic_base.cpp
	${MKDIR} -p ${OBJECTDIR}/include/greatest_hits
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/greatest_hits/genetic_base.o include/greatest_hits/genetic_base.cpp

${OBJECTDIR}/include/greatest_hits/genetic_container.o: include/greatest_hits/genetic_container.cpp
	${MKDIR} -p ${OBJECTDIR}/include/greatest_hits
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/greatest_hits/genetic_container.o include/greatest_hits/genetic_container.cpp

${OBJECTDIR}/include/greatest_hits/genetic_object.o: include/greatest_hits/genetic_object.cpp
	${MKDIR} -p ${OBJECTDIR}/include/greatest_hits
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/greatest_hits/genetic_object.o include/greatest_hits/genetic_object.cpp

${OBJECTDIR}/include/greatest_hits/longest_common_subsequence.o: include/greatest_hits/longest_common_subsequence.cpp
	${MKDIR} -p ${OBJECTDIR}/include/greatest_hits
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/greatest_hits/longest_common_subsequence.o include/greatest_hits/longest_common_subsequence.cpp

${OBJECTDIR}/include/greatest_hits/markov_chain.o: include/greatest_hits/markov_chain.cpp
	${MKDIR} -p ${OBJECTDIR}/include/greatest_hits
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/greatest_hits/markov_chain.o include/greatest_hits/markov_chain.cpp

${OBJECTDIR}/include/greatest_hits/median_maintenance.o: include/greatest_hits/median_maintenance.cpp
	${MKDIR} -p ${OBJECTDIR}/include/greatest_hits
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/greatest_hits/median_maintenance.o include/greatest_hits/median_maintenance.cpp

${OBJECTDIR}/include/greatest_hits/next_lex_permutation.o: include/greatest_hits/next_lex_permutation.cpp
	${MKDIR} -p ${OBJECTDIR}/include/greatest_hits
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/greatest_hits/next_lex_permutation.o include/greatest_hits/next_lex_permutation.cpp

${OBJECTDIR}/include/greatest_hits/quadtree.o: include/greatest_hits/quadtree.cpp
	${MKDIR} -p ${OBJECTDIR}/include/greatest_hits
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/greatest_hits/quadtree.o include/greatest_hits/quadtree.cpp

${OBJECTDIR}/include/greatest_hits/quadtree_it_bodies.o: include/greatest_hits/quadtree_it_bodies.cpp
	${MKDIR} -p ${OBJECTDIR}/include/greatest_hits
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/greatest_hits/quadtree_it_bodies.o include/greatest_hits/quadtree_it_bodies.cpp

${OBJECTDIR}/include/greatest_hits/quadtree_it_masscentres.o: include/greatest_hits/quadtree_it_masscentres.cpp
	${MKDIR} -p ${OBJECTDIR}/include/greatest_hits
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/greatest_hits/quadtree_it_masscentres.o include/greatest_hits/quadtree_it_masscentres.cpp

${OBJECTDIR}/include/greatest_hits/travelling_salesman_problem.o: include/greatest_hits/travelling_salesman_problem.cpp
	${MKDIR} -p ${OBJECTDIR}/include/greatest_hits
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/greatest_hits/travelling_salesman_problem.o include/greatest_hits/travelling_salesman_problem.cpp

${OBJECTDIR}/include/greatest_hits/wagner_fischer_distance.o: include/greatest_hits/wagner_fischer_distance.cpp
	${MKDIR} -p ${OBJECTDIR}/include/greatest_hits
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/greatest_hits/wagner_fischer_distance.o include/greatest_hits/wagner_fischer_distance.cpp

${OBJECTDIR}/include/iterators/average.o: include/iterators/average.cpp
	${MKDIR} -p ${OBJECTDIR}/include/iterators
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/iterators/average.o include/iterators/average.cpp

${OBJECTDIR}/include/iterators/circular_next.o: include/iterators/circular_next.cpp
	${MKDIR} -p ${OBJECTDIR}/include/iterators
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/iterators/circular_next.o include/iterators/circular_next.cpp

${OBJECTDIR}/include/iterators/contains_range.o: include/iterators/contains_range.cpp
	${MKDIR} -p ${OBJECTDIR}/include/iterators
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/iterators/contains_range.o include/iterators/contains_range.cpp

${OBJECTDIR}/include/iterators/copy.o: include/iterators/copy.cpp
	${MKDIR} -p ${OBJECTDIR}/include/iterators
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/iterators/copy.o include/iterators/copy.cpp

${OBJECTDIR}/include/iterators/copy_to_nested.o: include/iterators/copy_to_nested.cpp
	${MKDIR} -p ${OBJECTDIR}/include/iterators
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/iterators/copy_to_nested.o include/iterators/copy_to_nested.cpp

${OBJECTDIR}/include/iterators/distance_comparison.o: include/iterators/distance_comparison.cpp
	${MKDIR} -p ${OBJECTDIR}/include/iterators
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/iterators/distance_comparison.o include/iterators/distance_comparison.cpp

${OBJECTDIR}/include/iterators/fast_forward.o: include/iterators/fast_forward.cpp
	${MKDIR} -p ${OBJECTDIR}/include/iterators
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/iterators/fast_forward.o include/iterators/fast_forward.cpp

${OBJECTDIR}/include/iterators/find_in.o: include/iterators/find_in.cpp
	${MKDIR} -p ${OBJECTDIR}/include/iterators
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/iterators/find_in.o include/iterators/find_in.cpp

${OBJECTDIR}/include/iterators/find_subsequence.o: include/iterators/find_subsequence.cpp
	${MKDIR} -p ${OBJECTDIR}/include/iterators
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/iterators/find_subsequence.o include/iterators/find_subsequence.cpp

${OBJECTDIR}/include/iterators/get_random.o: include/iterators/get_random.cpp
	${MKDIR} -p ${OBJECTDIR}/include/iterators
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/iterators/get_random.o include/iterators/get_random.cpp

${OBJECTDIR}/include/iterators/index_conversion.o: include/iterators/index_conversion.cpp
	${MKDIR} -p ${OBJECTDIR}/include/iterators
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/iterators/index_conversion.o include/iterators/index_conversion.cpp

${OBJECTDIR}/include/iterators/insert_if_unique.o: include/iterators/insert_if_unique.cpp
	${MKDIR} -p ${OBJECTDIR}/include/iterators
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/iterators/insert_if_unique.o include/iterators/insert_if_unique.cpp

${OBJECTDIR}/include/iterators/is_last.o: include/iterators/is_last.cpp
	${MKDIR} -p ${OBJECTDIR}/include/iterators
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/iterators/is_last.o include/iterators/is_last.cpp

${OBJECTDIR}/include/iterators/is_trivial_repetition.o: include/iterators/is_trivial_repetition.cpp
	${MKDIR} -p ${OBJECTDIR}/include/iterators
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/iterators/is_trivial_repetition.o include/iterators/is_trivial_repetition.cpp

${OBJECTDIR}/include/iterators/nested_iteration.o: include/iterators/nested_iteration.cpp
	${MKDIR} -p ${OBJECTDIR}/include/iterators
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/iterators/nested_iteration.o include/iterators/nested_iteration.cpp

${OBJECTDIR}/include/iterators/range.o: include/iterators/range.cpp
	${MKDIR} -p ${OBJECTDIR}/include/iterators
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/iterators/range.o include/iterators/range.cpp

${OBJECTDIR}/include/iterators/range_is_within.o: include/iterators/range_is_within.cpp
	${MKDIR} -p ${OBJECTDIR}/include/iterators
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/iterators/range_is_within.o include/iterators/range_is_within.cpp

${OBJECTDIR}/include/iterators/range_iterator.o: include/iterators/range_iterator.cpp
	${MKDIR} -p ${OBJECTDIR}/include/iterators
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/iterators/range_iterator.o include/iterators/range_iterator.cpp

${OBJECTDIR}/include/iterators/remove_element.o: include/iterators/remove_element.cpp
	${MKDIR} -p ${OBJECTDIR}/include/iterators
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/iterators/remove_element.o include/iterators/remove_element.cpp

${OBJECTDIR}/include/iterators/remove_from.o: include/iterators/remove_from.cpp
	${MKDIR} -p ${OBJECTDIR}/include/iterators
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/iterators/remove_from.o include/iterators/remove_from.cpp

${OBJECTDIR}/include/iterators/repeated_ranges.o: include/iterators/repeated_ranges.cpp
	${MKDIR} -p ${OBJECTDIR}/include/iterators
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/iterators/repeated_ranges.o include/iterators/repeated_ranges.cpp

${OBJECTDIR}/include/iterators/starts_with.o: include/iterators/starts_with.cpp
	${MKDIR} -p ${OBJECTDIR}/include/iterators
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/iterators/starts_with.o include/iterators/starts_with.cpp

${OBJECTDIR}/include/joke/supersafe_number.o: include/joke/supersafe_number.cpp
	${MKDIR} -p ${OBJECTDIR}/include/joke
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/joke/supersafe_number.o include/joke/supersafe_number.cpp

${OBJECTDIR}/include/lang/c64_basic_for.o: include/lang/c64_basic_for.cpp
	${MKDIR} -p ${OBJECTDIR}/include/lang
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/lang/c64_basic_for.o include/lang/c64_basic_for.cpp

${OBJECTDIR}/include/lang/concepts.o: include/lang/concepts.cpp
	${MKDIR} -p ${OBJECTDIR}/include/lang
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/lang/concepts.o include/lang/concepts.cpp

${OBJECTDIR}/include/lang/dbl.o: include/lang/dbl.cpp
	${MKDIR} -p ${OBJECTDIR}/include/lang
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/lang/dbl.o include/lang/dbl.cpp

${OBJECTDIR}/include/lang/loop.o: include/lang/loop.cpp
	${MKDIR} -p ${OBJECTDIR}/include/lang
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/lang/loop.o include/lang/loop.cpp

${OBJECTDIR}/include/lang/optional.o: include/lang/optional.cpp
	${MKDIR} -p ${OBJECTDIR}/include/lang
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/lang/optional.o include/lang/optional.cpp

${OBJECTDIR}/include/lang/optionally_functional.o: include/lang/optionally_functional.cpp
	${MKDIR} -p ${OBJECTDIR}/include/lang
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/lang/optionally_functional.o include/lang/optionally_functional.cpp

${OBJECTDIR}/include/lang/value_type.o: include/lang/value_type.cpp
	${MKDIR} -p ${OBJECTDIR}/include/lang
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/lang/value_type.o include/lang/value_type.cpp

${OBJECTDIR}/include/laws/acceleration.o: include/laws/acceleration.cpp
	${MKDIR} -p ${OBJECTDIR}/include/laws
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/laws/acceleration.o include/laws/acceleration.cpp

${OBJECTDIR}/include/laws/constant_linear_acceleration.o: include/laws/constant_linear_acceleration.cpp
	${MKDIR} -p ${OBJECTDIR}/include/laws
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/laws/constant_linear_acceleration.o include/laws/constant_linear_acceleration.cpp

${OBJECTDIR}/include/laws/gravitation.o: include/laws/gravitation.cpp
	${MKDIR} -p ${OBJECTDIR}/include/laws
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/laws/gravitation.o include/laws/gravitation.cpp

${OBJECTDIR}/include/laws/linear_interpolation.o: include/laws/linear_interpolation.cpp
	${MKDIR} -p ${OBJECTDIR}/include/laws
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/laws/linear_interpolation.o include/laws/linear_interpolation.cpp

${OBJECTDIR}/include/laws/matrix_operations.o: include/laws/matrix_operations.cpp
	${MKDIR} -p ${OBJECTDIR}/include/laws
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/laws/matrix_operations.o include/laws/matrix_operations.cpp

${OBJECTDIR}/include/laws/matrix_operations_alternative.o: include/laws/matrix_operations_alternative.cpp
	${MKDIR} -p ${OBJECTDIR}/include/laws
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/laws/matrix_operations_alternative.o include/laws/matrix_operations_alternative.cpp

${OBJECTDIR}/include/laws/screen_rectangles.o: include/laws/screen_rectangles.cpp
	${MKDIR} -p ${OBJECTDIR}/include/laws
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/laws/screen_rectangles.o include/laws/screen_rectangles.cpp

${OBJECTDIR}/include/laws/set_difference.o: include/laws/set_difference.cpp
	${MKDIR} -p ${OBJECTDIR}/include/laws
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/laws/set_difference.o include/laws/set_difference.cpp

${OBJECTDIR}/include/laws/set_intersection.o: include/laws/set_intersection.cpp
	${MKDIR} -p ${OBJECTDIR}/include/laws
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/laws/set_intersection.o include/laws/set_intersection.cpp

${OBJECTDIR}/include/laws/vector_operations.o: include/laws/vector_operations.cpp
	${MKDIR} -p ${OBJECTDIR}/include/laws
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/laws/vector_operations.o include/laws/vector_operations.cpp

${OBJECTDIR}/include/nature/average_plot.o: include/nature/average_plot.cpp
	${MKDIR} -p ${OBJECTDIR}/include/nature
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/nature/average_plot.o include/nature/average_plot.cpp

${OBJECTDIR}/include/nature/mass_centre.o: include/nature/mass_centre.cpp
	${MKDIR} -p ${OBJECTDIR}/include/nature
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/nature/mass_centre.o include/nature/mass_centre.cpp

${OBJECTDIR}/include/nature/matrix.o: include/nature/matrix.cpp
	${MKDIR} -p ${OBJECTDIR}/include/nature
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/nature/matrix.o include/nature/matrix.cpp

${OBJECTDIR}/include/nature/parity.o: include/nature/parity.cpp
	${MKDIR} -p ${OBJECTDIR}/include/nature
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/nature/parity.o include/nature/parity.cpp

${OBJECTDIR}/include/nature/plot_operations.o: include/nature/plot_operations.cpp
	${MKDIR} -p ${OBJECTDIR}/include/nature
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/nature/plot_operations.o include/nature/plot_operations.cpp

${OBJECTDIR}/include/nature/units_strong_definitions.o: include/nature/units_strong_definitions.cpp
	${MKDIR} -p ${OBJECTDIR}/include/nature
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/nature/units_strong_definitions.o include/nature/units_strong_definitions.cpp

${OBJECTDIR}/include/nature/universe.o: include/nature/universe.cpp
	${MKDIR} -p ${OBJECTDIR}/include/nature
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/nature/universe.o include/nature/universe.cpp

${OBJECTDIR}/include/nature/vector.o: include/nature/vector.cpp
	${MKDIR} -p ${OBJECTDIR}/include/nature
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/nature/vector.o include/nature/vector.cpp

${OBJECTDIR}/include/string/all_words_appear.o: include/string/all_words_appear.cpp
	${MKDIR} -p ${OBJECTDIR}/include/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/string/all_words_appear.o include/string/all_words_appear.cpp

${OBJECTDIR}/include/string/are_subsentences.o: include/string/are_subsentences.cpp
	${MKDIR} -p ${OBJECTDIR}/include/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/string/are_subsentences.o include/string/are_subsentences.cpp

${OBJECTDIR}/include/string/are_substrings.o: include/string/are_substrings.cpp
	${MKDIR} -p ${OBJECTDIR}/include/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/string/are_substrings.o include/string/are_substrings.cpp

${OBJECTDIR}/include/string/case.o: include/string/case.cpp
	${MKDIR} -p ${OBJECTDIR}/include/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/string/case.o include/string/case.cpp

${OBJECTDIR}/include/string/case_insensitive_equal.o: include/string/case_insensitive_equal.cpp
	${MKDIR} -p ${OBJECTDIR}/include/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/string/case_insensitive_equal.o include/string/case_insensitive_equal.cpp

${OBJECTDIR}/include/string/extract_vocabulary.o: include/string/extract_vocabulary.cpp
	${MKDIR} -p ${OBJECTDIR}/include/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/string/extract_vocabulary.o include/string/extract_vocabulary.cpp

${OBJECTDIR}/include/string/get_substring.o: include/string/get_substring.cpp
	${MKDIR} -p ${OBJECTDIR}/include/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/string/get_substring.o include/string/get_substring.cpp

${OBJECTDIR}/include/string/is_end_start_of_the_word.o: include/string/is_end_start_of_the_word.cpp
	${MKDIR} -p ${OBJECTDIR}/include/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/string/is_end_start_of_the_word.o include/string/is_end_start_of_the_word.cpp

${OBJECTDIR}/include/string/is_just_whitespace.o: include/string/is_just_whitespace.cpp
	${MKDIR} -p ${OBJECTDIR}/include/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/string/is_just_whitespace.o include/string/is_just_whitespace.cpp

${OBJECTDIR}/include/string/is_subsentence.o: include/string/is_subsentence.cpp
	${MKDIR} -p ${OBJECTDIR}/include/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/string/is_subsentence.o include/string/is_subsentence.cpp

${OBJECTDIR}/include/string/is_substring.o: include/string/is_substring.cpp
	${MKDIR} -p ${OBJECTDIR}/include/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/string/is_substring.o include/string/is_substring.cpp

${OBJECTDIR}/include/string/is_word_delimiter.o: include/string/is_word_delimiter.cpp
	${MKDIR} -p ${OBJECTDIR}/include/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/string/is_word_delimiter.o include/string/is_word_delimiter.cpp

${OBJECTDIR}/include/string/is_word_in_dictionary.o: include/string/is_word_in_dictionary.cpp
	${MKDIR} -p ${OBJECTDIR}/include/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/string/is_word_in_dictionary.o include/string/is_word_in_dictionary.cpp

${OBJECTDIR}/include/string/join.o: include/string/join.cpp
	${MKDIR} -p ${OBJECTDIR}/include/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/string/join.o include/string/join.cpp

${OBJECTDIR}/include/string/remove_substrings.o: include/string/remove_substrings.cpp
	${MKDIR} -p ${OBJECTDIR}/include/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/string/remove_substrings.o include/string/remove_substrings.cpp

${OBJECTDIR}/include/string/remove_words.o: include/string/remove_words.cpp
	${MKDIR} -p ${OBJECTDIR}/include/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/string/remove_words.o include/string/remove_words.cpp

${OBJECTDIR}/include/string/replace.o: include/string/replace.cpp
	${MKDIR} -p ${OBJECTDIR}/include/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/string/replace.o include/string/replace.cpp

${OBJECTDIR}/include/string/replace_all_between.o: include/string/replace_all_between.cpp
	${MKDIR} -p ${OBJECTDIR}/include/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/string/replace_all_between.o include/string/replace_all_between.cpp

${OBJECTDIR}/include/string/sentence_assemblarator.o: include/string/sentence_assemblarator.cpp
	${MKDIR} -p ${OBJECTDIR}/include/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/string/sentence_assemblarator.o include/string/sentence_assemblarator.cpp

${OBJECTDIR}/include/string/split.o: include/string/split.cpp
	${MKDIR} -p ${OBJECTDIR}/include/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/string/split.o include/string/split.cpp

${OBJECTDIR}/include/string/split_on_punctuation.o: include/string/split_on_punctuation.cpp
	${MKDIR} -p ${OBJECTDIR}/include/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/string/split_on_punctuation.o include/string/split_on_punctuation.cpp

${OBJECTDIR}/include/string/string_view_find.o: include/string/string_view_find.cpp
	${MKDIR} -p ${OBJECTDIR}/include/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/string/string_view_find.o include/string/string_view_find.cpp

${OBJECTDIR}/include/string/trim.o: include/string/trim.cpp
	${MKDIR} -p ${OBJECTDIR}/include/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/string/trim.o include/string/trim.cpp

${OBJECTDIR}/include/string/trim_nonalpha.o: include/string/trim_nonalpha.cpp
	${MKDIR} -p ${OBJECTDIR}/include/string
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/string/trim_nonalpha.o include/string/trim_nonalpha.cpp

${OBJECTDIR}/include/tools/add_to_tally.o: include/tools/add_to_tally.cpp
	${MKDIR} -p ${OBJECTDIR}/include/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/tools/add_to_tally.o include/tools/add_to_tally.cpp

${OBJECTDIR}/include/tools/all_equal.o: include/tools/all_equal.cpp
	${MKDIR} -p ${OBJECTDIR}/include/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/tools/all_equal.o include/tools/all_equal.cpp

${OBJECTDIR}/include/tools/copy_first_n_over_rest.o: include/tools/copy_first_n_over_rest.cpp
	${MKDIR} -p ${OBJECTDIR}/include/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/tools/copy_first_n_over_rest.o include/tools/copy_first_n_over_rest.cpp

${OBJECTDIR}/include/tools/count_bits.o: include/tools/count_bits.cpp
	${MKDIR} -p ${OBJECTDIR}/include/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/tools/count_bits.o include/tools/count_bits.cpp

${OBJECTDIR}/include/tools/datashelf_extended.o: include/tools/datashelf_extended.cpp
	${MKDIR} -p ${OBJECTDIR}/include/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/tools/datashelf_extended.o include/tools/datashelf_extended.cpp

${OBJECTDIR}/include/tools/datashelf_foundation.o: include/tools/datashelf_foundation.cpp
	${MKDIR} -p ${OBJECTDIR}/include/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/tools/datashelf_foundation.o include/tools/datashelf_foundation.cpp

${OBJECTDIR}/include/tools/equidistant_sequence.o: include/tools/equidistant_sequence.cpp
	${MKDIR} -p ${OBJECTDIR}/include/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/tools/equidistant_sequence.o include/tools/equidistant_sequence.cpp

${OBJECTDIR}/include/tools/fast_min.o: include/tools/fast_min.cpp
	${MKDIR} -p ${OBJECTDIR}/include/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/tools/fast_min.o include/tools/fast_min.cpp

${OBJECTDIR}/include/tools/find_index_insert.o: include/tools/find_index_insert.cpp
	${MKDIR} -p ${OBJECTDIR}/include/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/tools/find_index_insert.o include/tools/find_index_insert.cpp

${OBJECTDIR}/include/tools/fluent_datashelf.o: include/tools/fluent_datashelf.cpp
	${MKDIR} -p ${OBJECTDIR}/include/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/tools/fluent_datashelf.o include/tools/fluent_datashelf.cpp

${OBJECTDIR}/include/tools/genetic.o: include/tools/genetic.cpp
	${MKDIR} -p ${OBJECTDIR}/include/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/tools/genetic.o include/tools/genetic.cpp

${OBJECTDIR}/include/tools/get_if_exists.o: include/tools/get_if_exists.cpp
	${MKDIR} -p ${OBJECTDIR}/include/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/tools/get_if_exists.o include/tools/get_if_exists.cpp

${OBJECTDIR}/include/tools/index_coordinate_conversions.o: include/tools/index_coordinate_conversions.cpp
	${MKDIR} -p ${OBJECTDIR}/include/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/tools/index_coordinate_conversions.o include/tools/index_coordinate_conversions.cpp

${OBJECTDIR}/include/tools/nested_vector.o: include/tools/nested_vector.cpp
	${MKDIR} -p ${OBJECTDIR}/include/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/tools/nested_vector.o include/tools/nested_vector.cpp

${OBJECTDIR}/include/tools/number_of_decimals.o: include/tools/number_of_decimals.cpp
	${MKDIR} -p ${OBJECTDIR}/include/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/tools/number_of_decimals.o include/tools/number_of_decimals.cpp

${OBJECTDIR}/include/tools/parse_cli_arguments.o: include/tools/parse_cli_arguments.cpp
	${MKDIR} -p ${OBJECTDIR}/include/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/tools/parse_cli_arguments.o include/tools/parse_cli_arguments.cpp

${OBJECTDIR}/include/tools/random.o: include/tools/random.cpp
	${MKDIR} -p ${OBJECTDIR}/include/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/tools/random.o include/tools/random.cpp

${OBJECTDIR}/include/tools/random_with_parity.o: include/tools/random_with_parity.cpp
	${MKDIR} -p ${OBJECTDIR}/include/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/tools/random_with_parity.o include/tools/random_with_parity.cpp

${OBJECTDIR}/include/tools/relocate.o: include/tools/relocate.cpp
	${MKDIR} -p ${OBJECTDIR}/include/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/tools/relocate.o include/tools/relocate.cpp

${OBJECTDIR}/include/tools/rememberator.o: include/tools/rememberator.cpp
	${MKDIR} -p ${OBJECTDIR}/include/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/tools/rememberator.o include/tools/rememberator.cpp

${OBJECTDIR}/include/tools/simple_datetime.o: include/tools/simple_datetime.cpp
	${MKDIR} -p ${OBJECTDIR}/include/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/tools/simple_datetime.o include/tools/simple_datetime.cpp

${OBJECTDIR}/include/tools/some_long_operation.o: include/tools/some_long_operation.cpp
	${MKDIR} -p ${OBJECTDIR}/include/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/tools/some_long_operation.o include/tools/some_long_operation.cpp

${OBJECTDIR}/include/tools/sort_map_by_value.o: include/tools/sort_map_by_value.cpp
	${MKDIR} -p ${OBJECTDIR}/include/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/tools/sort_map_by_value.o include/tools/sort_map_by_value.cpp

${OBJECTDIR}/include/tools/time_operations.o: include/tools/time_operations.cpp
	${MKDIR} -p ${OBJECTDIR}/include/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/tools/time_operations.o include/tools/time_operations.cpp

${OBJECTDIR}/include/tools/twoway_streambuf.o: include/tools/twoway_streambuf.cpp
	${MKDIR} -p ${OBJECTDIR}/include/tools
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/tools/twoway_streambuf.o include/tools/twoway_streambuf.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/tests/matrix_operations_performance.o: tests/matrix_operations_performance.cpp
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/matrix_operations_performance.o tests/matrix_operations_performance.cpp

${OBJECTDIR}/tests/std_maps_performance.o: tests/std_maps_performance.cpp
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/std_maps_performance.o tests/std_maps_performance.cpp

${OBJECTDIR}/tests/test_repeated_ranges_performance.o: tests/test_repeated_ranges_performance.cpp
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/test_repeated_ranges_performance.o tests/test_repeated_ranges_performance.cpp

${OBJECTDIR}/tests/test_universe_performance.o: tests/test_universe_performance.cpp
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/gtest -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include -I/usr/include/libxml++-3.0 -I/usr/lib64/libxml++-3.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/test_universe_performance.o tests/test_universe_performance.cpp

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
