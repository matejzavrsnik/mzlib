//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "is_meta_directory.h"

#include "../../options.h"

class fixture_is_meta_directory : public ::testing::Test 
{

protected:

   fixture_is_meta_directory() 
   {
      if (g_arguments.find(g_test_dir_param) != g_arguments.end()) {
         m_test_dir = g_arguments[g_test_dir_param] + "/filesystem";
         m_should_test_filesystem = true;
      }
   }
   virtual ~fixture_is_meta_directory() {}
   
   virtual void SetUp() {}
   virtual void TearDown() {}
   
   bool m_should_test_filesystem = false;
   std::string m_test_dir;
};


TEST_F(fixture_is_meta_directory, is_meta_directory)
{
   if(m_should_test_filesystem) {
      ASSERT_TRUE (mzlib::is_meta_directory("."));
      ASSERT_TRUE (mzlib::is_meta_directory(".."));
      ASSERT_TRUE (mzlib::is_meta_directory("avengers/."));
      ASSERT_TRUE (mzlib::is_meta_directory("avengers/.."));
      ASSERT_FALSE(mzlib::is_meta_directory("avengers/ironman"));
   }
   else {
      ASSERT_TRUE(true);
   }
}
