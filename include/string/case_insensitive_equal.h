//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "case.h"

#ifndef CASE_INSENSITIVE_EQUAL_H
#define CASE_INSENSITIVE_EQUAL_H

namespace mzlib {

template<class CharType>
bool case_insensitive_equal(const CharType& a, const CharType& b)
{
   return (tolower(a) == tolower(b));
}

}

#endif // CASE_INSENSITIVE_EQUAL_H
