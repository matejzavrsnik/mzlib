//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "list_files.h"
#include "../../options.h"
#include <algorithm>

class fixture_list_files: public ::testing::Test 
{

protected:

   fixture_list_files() 
   {
      if (g_arguments.find(g_test_dir_param) != g_arguments.end()) {
         m_test_dir = g_arguments[g_test_dir_param] + "/filesystem";
         m_should_test_filesystem = true;
      }
   }
   virtual ~fixture_list_files() {}
   
   virtual void SetUp() {}
   virtual void TearDown() {}
   
   bool m_should_test_filesystem = false;
   std::string m_test_dir;
};

TEST_F(fixture_list_files, list_files_defaults) 
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

TEST_F(fixture_list_files, list_files_recursive_nohidden) 
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

TEST_F(fixture_list_files, list_files_recursive_hidden) 
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

TEST_F(fixture_list_files, list_files_norecursive_hidden) 
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
