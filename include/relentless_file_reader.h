//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_RELENTLESS_FILE_READER_H
#define MZLIB_RELENTLESS_FILE_READER_H

#include "utils_filesystem.h"

#include <string>
#include <functional>
#include <fstream>

namespace mzlib {

// Keep reading file and if something is added, report via callback
class relentless_file_reader
{
   
private:
   
   const std::string m_filename;
   std::streampos m_last_read_position;
   
public:
   using type_callback = std::function<void(const std::string&, const std::string&)>;
   type_callback callback;

   relentless_file_reader(const std::string& filename) :
      m_filename(filename),
      m_last_read_position(find_eof_position(filename))
   {
   }
   
   void anything_new_what_about_now() 
   {
      std::ifstream::pos_type file_eof_position = find_eof_position(m_filename);
      if (file_eof_position > m_last_read_position) {
         const std::string new_content = read_file(m_filename, m_last_read_position, file_eof_position);
         m_last_read_position = file_eof_position;
         callback(new_content, m_filename);
      }
   }  
};

} // namespaces

#endif /* MZLIB_RELENTLESS_FILE_READER_H */

