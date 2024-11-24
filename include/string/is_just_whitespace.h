//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_IS_JUST_WHITESPACE_H
#define MZLIB_IS_JUST_WHITESPACE_H

#include <string>
#include <cctype>

namespace mzlib {
   
inline bool is_just_whitespaces(std::string_view s)
{
   for(char c : s)
      if(!std::isspace(c))
         return false;
   return true;
}

} // namespace

#endif /* MZLIB_IS_JUST_WHITESPACE_H */
