//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_IS_META_DIRECTORY_H
#define MZLIB_IS_META_DIRECTORY_H

namespace mzlib {

// is one of those . or .. "meta-directories"?
inline bool is_meta_directory(const char* directory_name)
{
   // to exercise my C muscles a bit
   int len_of_string = (int)strlen (directory_name);
   const char* last_dot_pos = strrchr (directory_name, '.');
   int len_to_last_dot = last_dot_pos - directory_name;
   return len_of_string == (len_to_last_dot + 1);
}

} // namespace

#endif // MZLIB_IS_META_DIRECTORY_H
