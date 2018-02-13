//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_EXTRACT_FILENAME_H
#define MZLIB_EXTRACT_FILENAME_H

#include <string_view>


namespace mzlib {

inline std::string_view extract_filename_from_path (std::string_view path)
{
   size_t pos = path.find_last_of("/\\");
   if (pos == std::string_view::npos) return "";
   return path.substr(pos+1, path.length()-pos);
}   

} // namespace

#endif // HEADER_H
