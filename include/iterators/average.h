//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_AVERAGE_ITERATOR_H
#define MZLIB_AVERAGE_ITERATOR_H

#include <numeric>

namespace mzlib {
    
// calculate average of all container elements
template<class Iterator>
double average(Iterator first, Iterator last)
{
   double sum = std::accumulate(first, last, 0.0);
   double avg = sum / std::distance(first, last);
   return avg;
}

} // namespace

#endif // MZLIB_AVERAGE_ITERATOR_H
