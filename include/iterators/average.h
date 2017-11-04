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
   double sum = std::accumulate(first, last, 0);
   double avg = sum / std::distance(first, last);
   return avg;
}

} // namespace

#endif // MZLIB_AVERAGE_ITERATOR_H

#ifdef MZLIB_AVERAGE_ITERATOR_TESTS_H
#undef MZLIB_AVERAGE_ITERATOR_TESTS_H

TEST(average_iterator, demo)
{
   std::vector<int> v{1,2,3,4,5};
   ASSERT_EQ(3.0, mzlib::average(v.begin(),   v.end()));
   ASSERT_EQ(3.5, mzlib::average(v.begin()+1, v.end()));
   ASSERT_EQ(2.5, mzlib::average(v.begin(),   v.end()-1));
}

#endif // MZLIB_AVERAGE_ITERATOR_TESTS_H

