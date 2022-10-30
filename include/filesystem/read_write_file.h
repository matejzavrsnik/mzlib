//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_READ_WRITE_FILE_H
#define MZLIB_READ_WRITE_FILE_H

#include <string>
#include <string_view>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <iostream>

namespace mzlib {

// Read file contents and return it in a string
//inline std::string read_file (const std::string_view filename)
//{
//   std::ifstream filestream(filename.data());
//   std::stringstream buffer;
//   buffer << filestream.rdbuf();
//   return buffer.str();
//}

inline std::string read_file (const std::filesystem::path& filepath)
{
   std::ifstream filestream{filepath};
   std::stringstream buffer;
   buffer << filestream.rdbuf();
   return buffer.str();
}

inline std::string read_file (
   const std::string_view filename, 
   const std::streampos read_from, 
   const std::streampos read_to)
{
   if (read_to <= read_from) return std::string();
   std::ifstream filestream(filename.data());
   filestream.seekg (read_from);
   const std::streamoff chars_to_read = read_to - read_from;
   if(chars_to_read > 0)
   {
      std::vector<char> vec_content(static_cast<std::vector<char>::size_type>(chars_to_read));
      filestream.read(&vec_content[0], chars_to_read);
      std::string str_content(vec_content.begin(), vec_content.end());
      return str_content;
   }
   else
   {
      return "";
   }
}

inline std::vector<std::string> read_file_lines(std::string_view filename)
{
   std::ifstream file(filename.data());
   std::string line;
   std::vector<std::string> lines;
   while (std::getline(file, line))
      lines.push_back(line);
   return lines;
}

// Save string contents into a file
//inline void save_file (const std::string_view filename, const std::string_view content)
//{
//   std::ofstream out(filename.data());
//   out << content;
//   //out.flush();
//   out.close();
//}

inline void save_file (const std::filesystem::path& filename, const std::string_view content)
{
   std::ofstream out{filename};
   out << content;
   out.close();
}

// Append string contents to a file
inline void append_file (const std::string_view filename, const std::string_view content)
{
   std::ofstream out(filename.data(), std::ios::app);
   out << content.data();
   out.close();
}

} // namespace

#endif // MZLIB_READ_WRITE_FILE_H
