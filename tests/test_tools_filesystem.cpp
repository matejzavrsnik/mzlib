//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "../include/tools/filesystem.h"
#include "gtest/gtest.h"
#include "../options.h"
#include <algorithm>    
#include <cstdio>

class fixture_tools_filesystem : public ::testing::Test 
{

protected:

   fixture_tools_filesystem() 
   {
      if (g_arguments.find(g_test_dir_param) != g_arguments.end()) {
         m_test_dir = g_arguments[g_test_dir_param] + "/filesystem";
         m_should_test_filesystem = true;
      }
   }
   virtual ~fixture_tools_filesystem() {}
   
   virtual void SetUp() {}
   virtual void TearDown() {}
   
   bool m_should_test_filesystem = false;
   std::string m_test_dir;
};

TEST_F(fixture_tools_filesystem, list_files_defaults) 
{
   if(m_should_test_filesystem) {
      std::vector<std::string> list = mzlib::list_files2(m_test_dir);
   
      auto not_found = list.end();
      ASSERT_EQ(2, list.size());
   
      ASSERT_NE(not_found, std::find(list.begin(), list.end(), "test_data/filesystem/file_text1.txt"));
      ASSERT_NE(not_found, std::find(list.begin(), list.end(), "test_data/filesystem/file_text2.txt"));	
   }
   else {
      ASSERT_TRUE(true);
   }
}

TEST_F(fixture_tools_filesystem, list_files_recursive_nohidden) 
{
   if(m_should_test_filesystem) {
      std::vector<std::string> list = mzlib::list_files2(m_test_dir, mzlib::option::recursive::yes, mzlib::option::include_hidden::no);

      auto not_found = list.end();
      ASSERT_EQ(6, list.size());

      ASSERT_NE(not_found, std::find(list.begin(), list.end(), "test_data/filesystem/file_text1.txt"));   
      ASSERT_NE(not_found, std::find(list.begin(), list.end(), "test_data/filesystem/file_text2.txt"));
      ASSERT_NE(not_found, std::find(list.begin(), list.end(), "test_data/filesystem/folder_with_stuff/file_text3.txt"));
      ASSERT_NE(not_found, std::find(list.begin(), list.end(), "test_data/filesystem/folder_with_stuff/file_text4.txt"));
      ASSERT_NE(not_found, std::find(list.begin(), list.end(), "test_data/filesystem/folder_with_stuff/subfolder/file_text5.txt"));
      ASSERT_NE(not_found, std::find(list.begin(), list.end(), "test_data/filesystem/folder_with_stuff/subfolder/file_text6.txt"));
   }
   else {
      ASSERT_TRUE(true);
   }
}

TEST_F(fixture_tools_filesystem, list_files_recursive_hidden) 
{
   if(m_should_test_filesystem) {
      std::vector<std::string> list = mzlib::list_files2(m_test_dir, mzlib::option::recursive::yes, mzlib::option::include_hidden::yes);

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
   else {
      ASSERT_TRUE(true);
   }
}

TEST_F(fixture_tools_filesystem, list_files_norecursive_hidden) 
{
   if(m_should_test_filesystem) {
      std::vector<std::string> list = mzlib::list_files2(m_test_dir, mzlib::option::recursive::no, mzlib::option::include_hidden::yes);

      auto not_found = list.end();
      ASSERT_EQ(3, list.size());

      ASSERT_NE(not_found, std::find(list.begin(), list.end(), "test_data/filesystem/file_text1.txt"));   
      ASSERT_NE(not_found, std::find(list.begin(), list.end(), "test_data/filesystem/file_text2.txt"));
      ASSERT_NE(not_found, std::find(list.begin(), list.end(), "test_data/filesystem/.hidden"));
   }
   else {
      ASSERT_TRUE(true);
   }
}

TEST_F(fixture_tools_filesystem, is_meta_directory)
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

TEST_F(fixture_tools_filesystem, write_append_read_file)
{
   if(m_should_test_filesystem) {
      std::string temp_file = m_test_dir + "/temp_file";
      std::string sample_content = "I must not fear.";

      mzlib::save_file (temp_file, sample_content);
      std::string temp_file_content = mzlib::read_file(temp_file);
      ASSERT_EQ(sample_content, temp_file_content);

      std::string additional_content = "Fear is the mind-killer.";
      mzlib::append_file (temp_file, additional_content);
      temp_file_content = mzlib::read_file(temp_file);
      ASSERT_EQ(sample_content + additional_content, temp_file_content);

      std::remove (temp_file.c_str());
   }
   else {
      ASSERT_TRUE(true);
   }
}

TEST_F(fixture_tools_filesystem, read_file_from_to)
{
   if(m_should_test_filesystem) {
      std::string temp_file = m_test_dir + "/temp_file";
      std::string sample_content = "I must not fear.";

      mzlib::save_file (temp_file, sample_content);
      std::string temp_file_content = mzlib::read_file(temp_file, std::streampos(11), std::streampos(15));
      ASSERT_EQ("fear", temp_file_content);

      std::remove (temp_file.c_str());
   }
   else {
      ASSERT_TRUE(true);
   }
}

TEST_F(fixture_tools_filesystem, find_eof_position)
{
   if(m_should_test_filesystem) {
      std::string temp_file = m_test_dir + "/temp_file";
      std::string sample_content = "I must not fear.";

      mzlib::save_file (temp_file, sample_content);
      std::streampos eof = mzlib::find_eof_position(temp_file);
      ASSERT_EQ(16, eof);

      std::remove (temp_file.c_str());
   }
   else {
      ASSERT_TRUE(true);
   }
}