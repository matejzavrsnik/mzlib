//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "../include/utils_filesystem.h"
#include "gtest/gtest.h"
#include "../options.h"
#include <algorithm>    

class fixture_utils_filesystem : public ::testing::Test 
{

protected:

   fixture_utils_filesystem() 
   {
      m_test_dir = g_arguments["mzlib_testdir"] + "/filesystem";
   }
   virtual ~fixture_utils_filesystem() {}
   
   virtual void SetUp() {}
   virtual void TearDown() {}
   
   std::string m_test_dir;
};

TEST_F(fixture_utils_filesystem, list_files_defaults) 
{
   std::vector<std::string> list = mzlib::util::list_files2(m_test_dir);
   
   auto not_found = list.end();
   ASSERT_EQ(2, list.size());
   
   ASSERT_NE(not_found, std::find(list.begin(), list.end(), "test_data/filesystem/file_text1.txt"));
   ASSERT_NE(not_found, std::find(list.begin(), list.end(), "test_data/filesystem/file_text2.txt"));	
}

TEST_F(fixture_utils_filesystem, list_files_recursive_nohidden) 
{
   std::vector<std::string> list = mzlib::util::list_files2(m_test_dir, true, false);
   
   auto not_found = list.end();
   ASSERT_EQ(6, list.size());

   ASSERT_NE(not_found, std::find(list.begin(), list.end(), "test_data/filesystem/file_text1.txt"));   
   ASSERT_NE(not_found, std::find(list.begin(), list.end(), "test_data/filesystem/file_text2.txt"));
   ASSERT_NE(not_found, std::find(list.begin(), list.end(), "test_data/filesystem/folder_with_stuff/file_text3.txt"));
   ASSERT_NE(not_found, std::find(list.begin(), list.end(), "test_data/filesystem/folder_with_stuff/file_text4.txt"));
   ASSERT_NE(not_found, std::find(list.begin(), list.end(), "test_data/filesystem/folder_with_stuff/subfolder/file_text5.txt"));
   ASSERT_NE(not_found, std::find(list.begin(), list.end(), "test_data/filesystem/folder_with_stuff/subfolder/file_text6.txt"));
}

TEST_F(fixture_utils_filesystem, list_files_recursive_hidden) 
{
   std::vector<std::string> list = mzlib::util::list_files2(m_test_dir, true, true);
   
   auto not_found = list.end();
   ASSERT_EQ(8, list.size());

   ASSERT_NE(not_found, std::find(list.begin(), list.end(), "test_data/filesystem/file_text1.txt"));   
   ASSERT_NE(not_found, std::find(list.begin(), list.end(), "test_data/filesystem/file_text2.txt"));
   ASSERT_NE(not_found, std::find(list.begin(), list.end(), "test_data/filesystem/.hidden"));
   ASSERT_NE(not_found, std::find(list.begin(), list.end(), "test_data/filesystem/folder_with_stuff/file_text3.txt"));
   ASSERT_NE(not_found, std::find(list.begin(), list.end(), "test_data/filesystem/folder_with_stuff/file_text4.txt"));
   ASSERT_NE(not_found, std::find(list.begin(), list.end(), "test_data/filesystem/folder_with_stuff/.hidden"));
   ASSERT_NE(not_found, std::find(list.begin(), list.end(), "test_data/filesystem/folder_with_stuff/subfolder/file_text5.txt"));
   ASSERT_NE(not_found, std::find(list.begin(), list.end(), "test_data/filesystem/folder_with_stuff/subfolder/file_text6.txt"));
}

TEST_F(fixture_utils_filesystem, list_files_norecursive_hidden) 
{
   std::vector<std::string> list = mzlib::util::list_files2(m_test_dir, false, true);
   
   auto not_found = list.end();
   ASSERT_EQ(3, list.size());

   ASSERT_NE(not_found, std::find(list.begin(), list.end(), "test_data/filesystem/file_text1.txt"));   
   ASSERT_NE(not_found, std::find(list.begin(), list.end(), "test_data/filesystem/file_text2.txt"));
   ASSERT_NE(not_found, std::find(list.begin(), list.end(), "test_data/filesystem/.hidden"));
}

TEST_F(fixture_utils_filesystem, is_meta_directory)
{
   ASSERT_TRUE (mzlib::util::is_meta_directory("."));
   ASSERT_TRUE (mzlib::util::is_meta_directory(".."));
   ASSERT_TRUE (mzlib::util::is_meta_directory("avengers/."));
   ASSERT_TRUE (mzlib::util::is_meta_directory("avengers/.."));
   ASSERT_FALSE(mzlib::util::is_meta_directory("avengers/ironman"));
}