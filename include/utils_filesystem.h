//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef UTILS_FILESYSTEM_H
#define UTILS_FILESYSTEM_H

#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <dirent.h>

namespace mzlib {
namespace util {
    
// Read file contents and return it in a string
inline std::string read_file (std::string filename) 
{
   std::ifstream filestream(filename);
   std::stringstream buffer;
   buffer << filestream.rdbuf();
   return buffer.str();
}

// Save string contents into a file
inline void save_file (std::string filename, std::string content)
{
   std::ofstream out(filename);
   out << content;
   out.close();
}

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

#endif // UTILS_FILESYSTEM_H

