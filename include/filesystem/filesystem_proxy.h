//
// Copyright (c) 2021 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_FILESYSTEM_PROXY_H
#define MZLIB_FILESYSTEM_PROXY_H

#include "read_write_file.h"
#include "list_files.h"
#include "../lang/exceptions.h"
#include "../lang/optional.h"

#include <filesystem>
#include <vector>

namespace mzlib {

// Purpose of this class: to be used instead of direct interface to filesystem operations, so that they could
// be mocked in tests. Most functions are implemented, but the implementation is mostly just a redirect to places
// that have actual implementation. All functions of this class are virtual so that they could be mocked.
class filesystem_proxy
{
public:

   virtual
   ~filesystem_proxy() = default;

   // interface to filesystem functionality from mzlib

   virtual std::vector<std::string>
   get_files(
      const std::filesystem::path& folder,
      mzlib::option::recursive recursive,
      mzlib::option::include_hidden include_hidden) const
   {
      return mzlib::list_files2(folder.generic_string(), recursive, include_hidden);
   }

   virtual std::string
   read_file (
      const std::string_view filename) const
   {
      return mzlib::read_file(filename);
   }

   virtual std::string
   read_file (
      const std::string_view filename,
      const std::streampos read_from,
      const std::streampos read_to) const
   {
      return mzlib::read_file(filename, read_from, read_to);
   }

   virtual std::vector<std::string>
      read_file_lines(std::string_view filename) const
   {
      return mzlib::read_file_lines(filename);
   }

   virtual void
   save_file (
      const std::string_view filename,
      const std::string_view content) const
   {
      mzlib::save_file(filename, content);
   }

   virtual void
   append_file (
      const std::string_view filename,
      const std::string_view content) const
   {
      mzlib::append_file(filename, content);
   }

   //  interface to filesystem functionality from std::filesystem::path

   virtual bool
   exists(const std::filesystem::path& p) const
   {
      return std::filesystem::exists(p);
   }

   virtual bool
   create_directories(const std::filesystem::path& p) const
   {
      return std::filesystem::create_directories(p);
   }

   virtual bool is_regular_file(const std::filesystem::path& p) const
   {
      return std::filesystem::is_regular_file(p);
   }

   // extended functionality to be implemented if user wants to

   virtual std::filesystem::path get_system_app_config_location() const
   {
      throw mzlib::exception::not_implemented{"unimplemented filesystem function"};
   }

};

} // namespace

#endif // MZLIB_FILESYSTEM_PROXY_H
