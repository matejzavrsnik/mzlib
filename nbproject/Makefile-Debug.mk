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
	${OBJECTDIR}/tests/tools/equidistant_sequence.o \
	${OBJECTDIR}/tests/tools/fast_min.o \
	${OBJECTDIR}/tests/tools/genetic.o \
	${OBJECTDIR}/tests/tools/index_coordinate_conversions.o \
	${OBJECTDIR}/tests/tools/next_lex_permutation.o \
	${OBJECTDIR}/tests/tools/number_of_decimals.o \
	${OBJECTDIR}/tests/tools/parse_cli_arguments.o \
	${OBJECTDIR}/tests/tools/random.o \
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
