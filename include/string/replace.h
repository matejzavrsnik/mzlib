//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_STRING_REPLACE_H
#define MZLIB_STRING_REPLACE_H

#include <string>

namespace mzlib {

// Replace all occurrences of a string in a string
template<typename Char = char>
inline void string_replace (std::basic_string<Char>& str, std::basic_string_view<Char> replace_what, std::basic_string_view<Char> replace_with)
{
   for (size_t pos = 0; 
        (pos = str.find(replace_what, pos)) != std::string::npos; 
        pos += replace_with.length()) 
   {
      str.replace(pos, replace_what.length(), replace_with);
   }
}

// When string_replace is invoked with std::string rather than std::string_view it doesn't know how to resolve, hence this
template<typename Char = char>
inline void string_replace (std::basic_string<Char>& str, std::basic_string<Char> replace_what, std::basic_string<Char> replace_with)
{
   string_replace(str, std::basic_string_view<Char>{replace_what}, std::basic_string_view<Char>{replace_with});
}

} // namespace

#endif // HEADER_H
