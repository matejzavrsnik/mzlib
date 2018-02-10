//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_FIND_EOF_POSITION_H
#define MZLIB_FIND_EOF_POSITION_H

#include <fstream>

namespace mzlib {

inline std::ifstream::pos_type find_eof_position(const std::string& filename)
{
   std::ifstream filestream(filename);
   filestream.seekg (0, filestream.end);
   return filestream.tellg();
}

} // namespace

#endif // MZLIB_FIND_EOF_POSITION_H
