//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_AGGREGATED_FILE_MONITOR_H
#define MZLIB_AGGREGATED_FILE_MONITOR_H

#include "tools/relentless_file_reader.h"
#include <string>

namespace mzlib {

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

