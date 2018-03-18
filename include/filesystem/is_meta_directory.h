//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_IS_META_DIRECTORY_H
#define MZLIB_IS_META_DIRECTORY_H

#include <string_view>
#include "../iterators/starts_with.h"

namespace mzlib {
   
// is one of those . or .. "meta-directories"?
inline bool is_meta_directory(std::string_view directory_name)
{
   // Had to convert string literals to string_view here because
   // the directory_name is string_view. Would not be a problem if
   // it wasn't for std::rbegin returning the zero-terminator as the
   // first character for literals, but it skips the .end() iterator
   // for string_views and returns last "visible" character.
   if (directory_name == "." ||
       directory_name == ".." ||
       ends_with(directory_name, std::string_view("/."))  ||
       ends_with(directory_name, std::string_view("/..")) ||
       ends_with(directory_name, std::string_view("\\.")) ||
       ends_with(directory_name, std::string_view("\\..")))
   {
      return true;
   }
   return false;
}

} // namespace

#endif // MZLIB_IS_META_DIRECTORY_H
