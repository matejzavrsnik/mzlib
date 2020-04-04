//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_ISWORDDELIMITER_H
#define MZLIB_ISWORDDELIMITER_H

#include <cctype>

namespace mzlib {
        
inline bool is_word_delimiter(int ch_prev, int ch)
{
   return isspace( ch ) // space is an obvious delimiter, but also
          || ( ispunct( ch )     // punctuations, but not
               && !( ch == '\'' ) // aren't, 'till
               && !( ch == '-' && ch_prev != ' ' ) // mind-boggling
             );
}

} // namespace

#endif // MZLIB_ISWORDDELIMITER_H
