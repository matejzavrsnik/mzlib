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
CND_CONF=Release
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
	${OBJECTDIR}/tests/test_tools_random.o \
	${OBJECTDIR}/tests/test_tools_string.o \
	${OBJECTDIR}/tests/test_universe_performance.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-Wall -Wextra -Wpedantic -std=c++1z
CXXFLAGS=-Wall -Wextra -Wpedantic -std=c++1z

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lgtest -lgtest_main -lpthread -lgmock /usr/lib64/libgmock.so

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mzlib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mzlib: /usr/lib64/libgmock.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mzlib: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mzlib ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/tests.o: tests.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests.o tests.cpp

${OBJECTDIR}/tests/test_tools_random.o: tests/test_tools_random.cpp
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/test_tools_random.o tests/test_tools_random.cpp

${OBJECTDIR}/tests/test_tools_string.o: tests/test_tools_string.cpp
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/test_tools_string.o tests/test_tools_string.cpp

${OBJECTDIR}/tests/test_universe_performance.o: tests/test_universe_performance.cpp
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -I/usr/include/gtest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests/test_universe_performance.o tests/test_universe_performance.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} -r ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgmock.so
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mzlib

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
