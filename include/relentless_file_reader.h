//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_RELENTLESS_FILE_READER_H
#define MZLIB_RELENTLESS_FILE_READER_H

#include "tools/filesystem.h"

#include <string>
#include <functional>
#include <fstream>

namespace mzlib {

// Reports the changes to a file via callback
class relentless_file_reader
{

public:
   
   // First argument is new content, second is the filename
   using type_callback = std::function<void(const std::string&, const std::string&)>;
   
private:
   
   const std::string m_filename;
   std::streampos m_last_read_position;
   type_callback m_callback;
   
public:

   relentless_file_reader(const std::string& filename, type_callback callback) :
      m_filename(filename),
      m_last_read_position(find_eof_position(filename)),
      m_callback(callback)
   {
   }
   
   relentless_file_reader(const std::string& filename) :
      relentless_file_reader(filename, nullptr)
   {
   }
   
   void set_callback(type_callback callback)
   {
      m_callback = callback;
   }
   
   void anything_new_what_about_now() 
   {
      std::ifstream::pos_type file_eof_position = find_eof_position(m_filename);
      if (file_eof_position > m_last_read_position) {
         const std::string new_content = read_file(m_filename, m_last_read_position, file_eof_position);
         m_last_read_position = file_eof_position;
         m_callback(new_content, m_filename);
      }
   }  
   
};

// Aggregates relentless file readers to work on a collection of files
class aggregated_file_monitor
{

private:
   
   std::vector<relentless_file_reader> m_readers;
   
public:
   
   aggregated_file_monitor(
      const std::vector<std::string>& files,
      relentless_file_reader::type_callback callback)
   {
      for (const std::string& file : files) {
         m_readers.emplace_back(file, callback);
      }
   }
   
   void inspect_all()
   {
      for (auto& reader : m_readers) {
         reader.anything_new_what_about_now();
      }
   }
   
   void set_callback(relentless_file_reader::type_callback callback)
   {
      for (auto& reader : m_readers) {
         reader.set_callback(callback);
      }
   }
           
};

} // namespaces

#endif /* MZLIB_RELENTLESS_FILE_READER_H */

