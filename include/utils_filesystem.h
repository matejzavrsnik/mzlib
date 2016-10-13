//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_UTILS_FILESYSTEM_H
#define MZLIB_UTILS_FILESYSTEM_H

#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <dirent.h>
#include <cstring>

#include "enums.h"

namespace mzlib {
namespace util {
    
// Read file contents and return it in a string
inline std::string read_file (const std::string& filename) 
{
   std::ifstream filestream(filename);
   std::stringstream buffer;
   buffer << filestream.rdbuf();
   return buffer.str();
}

// Save string contents into a file
inline void save_file (const std::string& filename, const std::string& content)
{
   std::ofstream out(filename);
   out << content;
   out.close();
}

// Append string contents to a file
inline void append_file (const std::string& filename, const std::string& content)
{
   std::ofstream out(filename, std::ios::app);
   out << content;
   out.close();
}

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

// is one of those . or .. "meta-directories"?
bool is_meta_directory(const char* directory_name)
{
   // to exercise my C muscles a bit
   int len_of_string = (int)strlen (directory_name);
   const char* last_dot_pos = strrchr (directory_name, '.');
   int len_to_last_dot = last_dot_pos - directory_name;
   return len_of_string == (len_to_last_dot + 1);
}

inline std::vector<std::string> 
list_files2 (const std::string& directory, erecursive recursive = erecursive::no, einclude_hidden include_hidden = einclude_hidden::no)
{
   std::vector<std::string> files;   
   DIR *pDIR;
   struct dirent *entry;
   if ( (pDIR=opendir(directory.c_str())) ) {
      while ( (entry = readdir(pDIR)) ) {
         bool is_hidden = (entry->d_name[0] == '.');
         bool is_directory = (entry->d_type == DT_DIR);
         bool is_meta = is_meta_directory(entry->d_name);
         if ((is_hidden && include_hidden == einclude_hidden::no) || is_meta) {
            continue;
         }
         if(is_directory && recursive == erecursive::yes) {
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
    
} } // namespace mzlib::util

#endif /* MZLIB_UTILS_FILESYSTEM_H */

