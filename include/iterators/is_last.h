//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_IS_LAST_H
#define MZLIB_IS_LAST_H

namespace mzlib {

template<class Iterator, class Container>
bool is_last(const Iterator& i, const Container& c)
{
   return (std::next(i) == c.end());
}

} // namespace

#endif // MZLIB_IS_LAST_H

#ifdef MZLIB_BUILDING_TESTS

#ifndef MZLIB_IS_LAST_TESTS_H
#define MZLIB_IS_LAST_TESTS_H

// No tests yet

#endif // MZLIB_IS_LAST_TESTS_H

#endif // MZLIB_BUILDING_TESTS
