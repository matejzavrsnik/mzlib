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
//  Windows
#ifndef _WIN32
   #include <dirent.h>
#endif
#include <string_view>
#include <vector>

namespace mzlib {

//  Windows
#ifndef _WIN32
namespace old {
// List all files in a directory
inline std::vector<std::string> list_files (std::string_view directory, bool include_hidden = true)
{
   std::vector<std::string> files;	
   DIR *pDIR;
   struct dirent *entry;
   if ( (pDIR=opendir(directory.data())) ) {
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
list_files2 (const std::string_view directory, option::recursive recursive = option::recursive::no, option::include_hidden include_hidden = option::include_hidden::no)
{
   std::vector<std::string> files;   
   DIR *pDIR;
   struct dirent *entry;
   if ( (pDIR=opendir(directory.data())) ) {
      while ( (entry = readdir(pDIR)) ) {
         bool is_hidden = (entry->d_name[0] == '.');
         bool is_directory = (entry->d_type == DT_DIR);
         bool is_meta = is_meta_directory(entry->d_name);
         if ((is_hidden && include_hidden == option::include_hidden::no) || is_meta) {
            continue;
         }
         if(is_directory && recursive == option::recursive::yes) {
            std::string subdir_name = directory.data();
            subdir_name += "/" + std::string(entry->d_name);
            auto files_in_subdir = list_files2(subdir_name, recursive, include_hidden);
            std::copy (files_in_subdir.begin(), files_in_subdir.end(), std::back_inserter(files));
         }
         else if (!is_directory) {
            std::string filename = directory.data();
            filename += "/" + std::string(entry->d_name);
            files.push_back(filename);
         }
      }
      closedir(pDIR);
   }
   return files;
}
#endif

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
