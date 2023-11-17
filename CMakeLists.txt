cmake_minimum_required (VERSION 3.19)

project (mzlib)

# Want to see make messages
set(CMAKE_VERBOSE_MAKEFILE ON)

set (CMAKE_CXX_STANDARD 23)
add_compile_options(-fconcepts-diagnostics-depth=5)

# Include cmake scripts
include(cmake/configurations.cmake)
include(cmake/warnings.cmake)

# Set output directory of all projects to be somewhere sensible
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB Source
   include/abstract/*.*
   include/apps/*.*
   include/extension/*.*
   include/extension/libxmlpp/*.*
   include/extension/sdl/*.*
   include/extension/imgui/*.*
   include/filesystem/*.*
   include/greatest_hits/*.*
   include/grid/*.*
   include/iterators/*.*
   include/joke/*.*
   include/lang/*.*
   include/laws/*.*
   include/mocks/*.*
   include/nature/*.*
   include/printers/*.*
   include/string/*.*
   include/tools/*.*
   include/tools/internal/*.*
   )

file(GLOB Runner main.cpp)

set(SOURCES ${Source} ${Runner})

message(${SOURCES})

add_executable (mzlib ${SOURCES})

find_package(GTest)
find_package(libxmlpp)

target_link_libraries(mzlib
   gtest::gtest
   libxmlpp::libxmlpp)
