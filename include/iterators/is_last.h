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
