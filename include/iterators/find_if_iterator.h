//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_FIND_IN_ITERATOR_H
#define MZLIB_FIND_IN_ITERATOR_H

namespace mzlib {

// a version of find_if that finds a value in a collection of iterators
template<typename Iterator, typename Value = typename Iterator::value_type>
Iterator find_if_iterator(Iterator begin, Iterator end, Value v)
{
   return std::find_if(begin, end, [&v](auto it) {return *it == v;});
}

} // namespace

#endif // MZLIB_FIND_IN_ITERATOR_H
