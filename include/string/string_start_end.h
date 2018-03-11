//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_STRING_START_END_H
#define MZLIB_STRING_START_END_H

#include "../iterators/starts_with.h"

namespace mzlib {

// todo: remove. use starts_with from iterators lib
inline bool string_ends_with (std::string_view str, std::string_view end) {
   return ends_with(str, end);
}

inline bool string_starts_with (std::string_view str, std::string_view start) {
   return starts_with(str, start);
}

} // namespace

#endif // MZLIB_STRING_START_END_H
