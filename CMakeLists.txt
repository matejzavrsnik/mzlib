cmake_minimum_required (VERSION 3.19)
project (mzlib)

set (CMAKE_CXX_STANDARD 20)

# Set output directory of all projects to be somewhere sensible
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(/usr/include/gtest)
include_directories(/usr/include/glib-2.0)
include_directories(/usr/lib64/glib-2.0/include)
include_directories(/usr/include/glibmm-2.4)
include_directories(/usr/lib64/glibmm-2.4/include)
include_directories(/usr/include/libxml++-3.0)
include_directories(/usr/lib64/libxml++-3.0/include)

file(GLOB Source
   include/abstract/*.*
   include/apps/*.*
   include/extension/*.*
   include/extension/libxmlpp/*.*
   include/extension/sdl/*.*
   include/extension/imgui/*.*
   include/filesystem/*.*
   include/greatest_hits/*.*
   include/iterators/*.*
   include/joke/*.*
   include/lang/*.*
   include/laws/*.*
   include/mocks/*.*
   include/nature/*.*
   include/string/*.*
   include/tools/*.*
   include/tools/internal/*.*
   )

file(GLOB Runner main.cpp)

set(SOURCES ${Source} ${Runner})

message(${SOURCES})

add_executable (mzlib ${SOURCES})

target_link_libraries(mzlib
   pthread
   gtest
   gmock
   glib-2.0
   glibmm-2.4
   xml++-3.0
   )