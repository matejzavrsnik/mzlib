//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "filenamearise.h"

TEST(filenamearise, demo) 
{
   ASSERT_EQ("filename", mzlib::filenamearise("filename", '_'));
   ASSERT_EQ("file_name", mzlib::filenamearise("file name", '_'));
   ASSERT_EQ("file_name", mzlib::filenamearise("file  name", '_'));
   ASSERT_EQ("filename", mzlib::filenamearise("#!""#$%&/filename", '_'));
}