//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "is_meta_directory.h"

TEST(is_meta_directory, demo)
{
   // unix
   ASSERT_TRUE (mzlib::is_meta_directory("/."));
   ASSERT_TRUE (mzlib::is_meta_directory("/.."));
   ASSERT_TRUE (mzlib::is_meta_directory("."));
   ASSERT_TRUE (mzlib::is_meta_directory(".."));
   ASSERT_TRUE (mzlib::is_meta_directory("avengers/."));
   ASSERT_TRUE (mzlib::is_meta_directory("avengers/.."));
   ASSERT_FALSE(mzlib::is_meta_directory("avengers/ironman"));
   ASSERT_FALSE(mzlib::is_meta_directory("avengers/ironman."));
   ASSERT_FALSE(mzlib::is_meta_directory("avengers/ironman.."));
   ASSERT_FALSE(mzlib::is_meta_directory("avengers."));
   ASSERT_FALSE(mzlib::is_meta_directory("avengers.."));
   
   // windows
   ASSERT_TRUE (mzlib::is_meta_directory("\\."));
   ASSERT_TRUE (mzlib::is_meta_directory("\\.."));
   ASSERT_TRUE (mzlib::is_meta_directory("avengers\\."));
   ASSERT_TRUE (mzlib::is_meta_directory("avengers\\.."));
   ASSERT_FALSE(mzlib::is_meta_directory("avengers\\ironman"));
   ASSERT_FALSE(mzlib::is_meta_directory("avengers\\ironman."));
   ASSERT_FALSE(mzlib::is_meta_directory("avengers\\ironman.."));
}
