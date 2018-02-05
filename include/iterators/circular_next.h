//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_CIRCULAR_NEXT_ITERATOR_H
#define MZLIB_CIRCULAR_NEXT_ITERATOR_H

namespace mzlib {
    
// after last element continue from the first again.
template<class Iterator>
void circular_next_iterator(Iterator &iterator, Iterator first, Iterator last)
{
   if(++iterator == last) iterator = first;
}

} // namespace

#endif // MZLIB_CIRCULAR_NEXT_ITERATOR_H
