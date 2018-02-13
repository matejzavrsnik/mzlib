//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "extract_filename.h"

TEST(extract_filename_from_path, demo) 
{
   // unix
   ASSERT_EQ("filename", mzlib::extract_filename_from_path("/home/matej/filename"));
   ASSERT_EQ("", mzlib::extract_filename_from_path("whatabout_when_no_filename"));
   ASSERT_EQ("with.ending", mzlib::extract_filename_from_path("/home/matej/with.ending"));
   
   // windows
   ASSERT_EQ("filename", mzlib::extract_filename_from_path("C:\\matej\\filename"));
   ASSERT_EQ("", mzlib::extract_filename_from_path("whatabout_when_no_filename"));
   ASSERT_EQ("with.ending", mzlib::extract_filename_from_path("C:\\matej\\with.ending"));
}