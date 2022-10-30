//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_STRING_REPLACE_H
#define MZLIB_STRING_REPLACE_H

#include "../lang/concepts.h"

#include <string>

namespace mzlib {

/**
 * @brief Replaces all occurrences of a string in a string
 *
 * @example
 * \code{.cpp}
 * std::string str("Igneous rock, or magmatic rock, is one of the three main rock types.");
 * std::string_view rock("rock");
 * std::string_view scissors("scissors");
 * string_replace(str, rock, scissors);
 * std::cout << str; // "Igneous scissors, or magmatic scissors, is one of the three main scissors types."
 * \endcode
 */
inline void string_replace (
   writable_string auto& str, /**< [in/out] string that needs substrings replaced */
   readable_string auto replace_what, /**< [in] careful when this is string_view into the subject string */
   readable_string auto replace_with /**< [in] careful when this is string_view into the subject string */
)
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
