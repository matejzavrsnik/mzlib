//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_LIST_FILES_H
#define MZLIB_LIST_FILES_H

#include "is_meta_directory.h"
#include "../lang/binary_options.h"
#include <dirent.h>

namespace mzlib {

namespace old {
// List all files in a directory
inline std::vector<std::string> list_files (std::string directory, bool include_hidden = true)
{
   std::vector<std::string> files;	
   DIR *pDIR;
   struct dirent *entry;
   if ( (pDIR=opendir(directory.c_str())) ) {
      while ( (entry = readdir(pDIR)) ) {
         bool hidden = (entry->d_name[0] == '.');
         if (hidden && !include_hidden) {
            continue;
         }
         std::string filename = entry->d_name;
         files.push_back(filename);
      }
      closedir(pDIR);
   }
   return files;
}

} // namespace old

inline std::vector<std::string> 
list_files2 (const std::string& directory, option::recursive recursive = option::recursive::no, option::include_hidden include_hidden = option::include_hidden::no)
{
   std::vector<std::string> files;   
   DIR *pDIR;
   struct dirent *entry;
   if ( (pDIR=opendir(directory.c_str())) ) {
      while ( (entry = readdir(pDIR)) ) {
         bool is_hidden = (entry->d_name[0] == '.');
         bool is_directory = (entry->d_type == DT_DIR);
         bool is_meta = is_meta_directory(entry->d_name);
         if ((is_hidden && include_hidden == option::include_hidden::no) || is_meta) {
            continue;
         }
         if(is_directory && recursive == option::recursive::yes) {
            std::string subdir_name = directory + "/" + std::string(entry->d_name);
            auto files_in_subdir = list_files2(subdir_name, recursive, include_hidden);
            std::copy (files_in_subdir.begin(), files_in_subdir.end(), std::back_inserter(files));
         }
         else if (!is_directory) {
            std::string filename = directory + "/" + std::string(entry->d_name);
            files.push_back(filename);
         }
      }
      closedir(pDIR);
   }
   return files;
}

// defined in boost/filesystem.hpp
// if project includes that, it will see, compile, and be able to use the following functions
#ifdef BOOST_FILESYSTEM_FILESYSTEM_HPP    

// List all files in a directory using boost
inline std::vector<std::string> boost_list_files (std::string directory, bool include_hidden = true)
{
   std::vector<std::string> files;
   boost::filesystem::path p(directory);
   boost::filesystem::directory_iterator end;
   for (boost::filesystem::directory_iterator path_it(p); path_it != end; ++path_it)
   {
      if (boost::filesystem::is_regular_file(*path_it)) {
         std::string filename = path_it->path().string();
         bool hidden = (filename[0] == '.');
         if (hidden && !include_hidden) {
            continue;
         }
         files.push_back(filename);
      }
   }
   return files;
}
#endif
    
} // namespace

#endif // MZLIB_LIST_FILES_H

#ifdef MZLIB_LIST_FILES_TESTS_H
#undef MZLIB_LIST_FILES_TESTS_H

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


#endif // MZLIB_LIST_FILES_TESTS_H

