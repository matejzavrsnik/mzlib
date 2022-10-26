cmake_minimum_required (VERSION 3.19)

project (mzlib)

# Want to see make messages
set(CMAKE_VERBOSE_MAKEFILE ON)

set (CMAKE_CXX_STANDARD 23)
add_compile_options(-fconcepts-diagnostics-depth=5)

# Include cmake scripts
include(cmake/configurations.cmake)
include(cmake/warnings.cmake)
include(cmake/conan.cmake)

# Set up Conan dependencies
# To find packages:
#    - https://bintray.com/bincrafters/public-conan
#    - https://conan.io/center/
set(CONAN_EXTRA_REQUIRES "")
set(CONAN_EXTRA_OPTIONS "")
set(CONAN_EXTRA_REQUIRES ${CONAN_EXTRA_REQUIRES}
   gtest/1.12.1
   libxmlpp/5.0.1
)
run_conan()

# Set output directory of all projects to be somewhere sensible
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#include_directories(/usr/include/gtest)
#include_directories(/usr/include/glib-2.0)
#include_directories(/usr/lib64/glib-2.0/include)
#include_directories(/usr/include/glibmm-2.4)
#include_directories(/usr/lib64/glibmm-2.4/include)
#include_directories(/usr/include/libxml++-3.0)
#include_directories(/usr/lib64/libxml++-3.0/include)

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
   CONAN_PKG::gtest
   CONAN_PKG::libxmlpp
   )