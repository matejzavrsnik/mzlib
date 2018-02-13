//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_STRING_START_END_H
#define MZLIB_STRING_START_END_H

namespace mzlib {

inline bool string_ends_with (const std::string_view& str, const std::string_view& end) {
   if (str.length() >= end.length()) {
      const int comparisson = str.compare (str.length() - end.length(), end.length(), end);
      return (comparisson == 0);
   }
   else {
      return false;
   }
}

inline bool string_starts_with (const std::string_view& str, const std::string_view& start) {
   if (str.length() >= start.length()) {
      const int comparisson = str.compare (0, start.length(), start);
      return (comparisson == 0);
   }
   else {
      return false;
   }
}

} // namespace

#endif // MZLIB_STRING_START_END_H
