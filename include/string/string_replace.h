//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_STRING_REPLACE_H
#define MZLIB_STRING_REPLACE_H

namespace mzlib {

// Replace all occurrences of a string in a string
inline void string_replace (std::string& str, const std::string& replace_what, const std::string& replace_with) 
{
   for (size_t pos = 0; 
        (pos = str.find(replace_what, pos)) != std::string::npos; 
        pos += replace_with.length()) 
   {
      str.replace(pos, replace_what.length(), replace_with);
   }
}

} // namespace

#endif // HEADER_H

#ifdef MZLIB_STRING_REPLACE_TESTS_H

// No tests yet

#endif // MZLIB_STRING_REPLACE_TESTS_H

