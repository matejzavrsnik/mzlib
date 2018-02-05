//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_EXTRACT_FILENAME_H
#define MZLIB_EXTRACT_FILENAME_H

namespace mzlib {

inline std::string extract_filename_from_path (std::string path)
{
   size_t pos = path.find_last_of("/\\");
   if (pos == std::string::npos) return "";
   return path.substr(pos+1, path.length()-pos);
}   

} // namespace

#endif // HEADER_H
