//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_IS_META_DIRECTORY_H
#define MZLIB_IS_META_DIRECTORY_H

#include <string_view>
#include "../string/string_start_end.h"

namespace mzlib {
   
// is one of those . or .. "meta-directories"?
inline bool is_meta_directory(const std::string_view directory_name)
{
   if (directory_name == "." ||
       directory_name == ".." ||
       string_ends_with(directory_name, "/.")  ||
       string_ends_with(directory_name, "/..") ||
       string_ends_with(directory_name, "\\.") ||
       string_ends_with(directory_name, "\\.."))
   {
      return true;
   }
   return false;
}

} // namespace

#endif // MZLIB_IS_META_DIRECTORY_H
