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
	${OBJECTDIR}/tests/test_dbl.o \
	${OBJECTDIR}/tests/test_genetic.o \
	${OBJECTDIR}/tests/test_image_texture.o \
	${OBJECTDIR}/tests/test_law_screen_rectangle.o \
	${OBJECTDIR}/tests/test_laws.o \
	${OBJECTDIR}/tests/test_markov_chain.o \
	${OBJECTDIR}/tests/test_masscentre.o \
	${OBJECTDIR}/tests/test_probabilator.o \
	${OBJECTDIR}/tests/test_quadtree.o \
	${OBJECTDIR}/tests/test_relentless_file_reader.o \
	${OBJECTDIR}/tests/test_sentence_o_matic.o \
	${OBJECTDIR}/tests/test_supersafe_number.o \
	${OBJECTDIR}/tests/test_twoway_streambuf.o \
	${OBJECTDIR}/tests/test_unique.o \
	${OBJECTDIR}/tests/test_units_strong.o \
	${OBJECTDIR}/tests/test_universe.o \
	${OBJECTDIR}/tests/test_universe_performance.o \
	${OBJECTDIR}/tests/test_utilities.o \
	${OBJECTDIR}/tests/test_utils_filesystem.o \
	${OBJECTDIR}/tests/test_utils_random.o \
	${OBJECTDIR}/tests/test_utils_string.o \
	${OBJECTDIR}/tests/test_vector.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-Wall -Wextra -Wpedantic
CXXFLAGS=-Wall -Wextra -Wpedantic

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
	$(COMPILE.cc) -g -Wall -I/usr/include/gtest -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/tests/test_dbl.o: tests/test_dbl.cpp
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/usr/include/gtest -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/test_dbl.o tests/test_dbl.cpp

${OBJECTDIR}/tests/test_genetic.o: tests/test_genetic.cpp
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/usr/include/gtest -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/test_genetic.o tests/test_genetic.cpp

${OBJECTDIR}/tests/test_image_texture.o: tests/test_image_texture.cpp
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/usr/include/gtest -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/test_image_texture.o tests/test_image_texture.cpp

${OBJECTDIR}/tests/test_law_screen_rectangle.o: tests/test_law_screen_rectangle.cpp
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/usr/include/gtest -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/test_law_screen_rectangle.o tests/test_law_screen_rectangle.cpp

${OBJECTDIR}/tests/test_laws.o: tests/test_laws.cpp
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/usr/include/gtest -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/test_laws.o tests/test_laws.cpp

${OBJECTDIR}/tests/test_markov_chain.o: tests/test_markov_chain.cpp
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/usr/include/gtest -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/test_markov_chain.o tests/test_markov_chain.cpp

${OBJECTDIR}/tests/test_masscentre.o: tests/test_masscentre.cpp
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/usr/include/gtest -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/test_masscentre.o tests/test_masscentre.cpp

${OBJECTDIR}/tests/test_probabilator.o: tests/test_probabilator.cpp
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/usr/include/gtest -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/test_probabilator.o tests/test_probabilator.cpp

${OBJECTDIR}/tests/test_quadtree.o: tests/test_quadtree.cpp
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/usr/include/gtest -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/test_quadtree.o tests/test_quadtree.cpp

${OBJECTDIR}/tests/test_relentless_file_reader.o: tests/test_relentless_file_reader.cpp
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/usr/include/gtest -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/test_relentless_file_reader.o tests/test_relentless_file_reader.cpp

${OBJECTDIR}/tests/test_sentence_o_matic.o: tests/test_sentence_o_matic.cpp
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/usr/include/gtest -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/test_sentence_o_matic.o tests/test_sentence_o_matic.cpp

${OBJECTDIR}/tests/test_supersafe_number.o: tests/test_supersafe_number.cpp
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/usr/include/gtest -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/test_supersafe_number.o tests/test_supersafe_number.cpp

${OBJECTDIR}/tests/test_twoway_streambuf.o: tests/test_twoway_streambuf.cpp
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/usr/include/gtest -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/test_twoway_streambuf.o tests/test_twoway_streambuf.cpp

${OBJECTDIR}/tests/test_unique.o: tests/test_unique.cpp
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/usr/include/gtest -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/test_unique.o tests/test_unique.cpp

${OBJECTDIR}/tests/test_units_strong.o: tests/test_units_strong.cpp
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/usr/include/gtest -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/test_units_strong.o tests/test_units_strong.cpp

${OBJECTDIR}/tests/test_universe.o: tests/test_universe.cpp
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/usr/include/gtest -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/test_universe.o tests/test_universe.cpp

${OBJECTDIR}/tests/test_universe_performance.o: tests/test_universe_performance.cpp
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/usr/include/gtest -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/test_universe_performance.o tests/test_universe_performance.cpp

${OBJECTDIR}/tests/test_utilities.o: tests/test_utilities.cpp
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/usr/include/gtest -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/test_utilities.o tests/test_utilities.cpp

${OBJECTDIR}/tests/test_utils_filesystem.o: tests/test_utils_filesystem.cpp
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/usr/include/gtest -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/test_utils_filesystem.o tests/test_utils_filesystem.cpp

${OBJECTDIR}/tests/test_utils_random.o: tests/test_utils_random.cpp
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/usr/include/gtest -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/test_utils_random.o tests/test_utils_random.cpp

${OBJECTDIR}/tests/test_utils_string.o: tests/test_utils_string.cpp
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/usr/include/gtest -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/test_utils_string.o tests/test_utils_string.cpp

${OBJECTDIR}/tests/test_vector.o: tests/test_vector.cpp
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/usr/include/gtest -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/test_vector.o tests/test_vector.cpp

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
