//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_FAST_FORWARD_ITERATOR_UNTIL_H
#define MZLIB_FAST_FORWARD_ITERATOR_UNTIL_H

namespace mzlib {
    
// Iterate forward in a container until the condition is met.
template<class Element, class Iterator>
Iterator fast_forward(
   Iterator begin,
   Iterator end,
   std::function<bool(const Element&)> condition)
{
   while (begin != end && !condition(*begin)) {
      begin = std::next(begin);
   }
   return begin;
}

} // namespace

#endif // MZLIB_FAST_FORWARD_ITERATOR_UNTIL_H

#ifdef MZLIB_BUILDING_TESTS

#ifndef MZLIB_FAST_FORWARD_ITERATOR_UNTIL_TESTS_H
#define MZLIB_FAST_FORWARD_ITERATOR_UNTIL_TESTS_H

TEST(fast_forward, demo)
{
   std::vector<int> v = {1,2,3,4,5,6,7,8,9};
   
   using namespace std::placeholders;
   
   auto result_f = mzlib::fast_forward<int>(
      v.begin(), v.end(), 
      std::bind(std::greater<int>(), _1, 5));
   ASSERT_EQ(6, *result_f);
   
   auto result_b = mzlib::fast_forward<int>(
      v.rbegin(), v.rend(), 
      std::bind(std::less<int>(), _1, 5));
   ASSERT_EQ(4, *result_b);
}

#endif // MZLIB_FAST_FORWARD_ITERATOR_UNTIL_TESTS_H

#endif // MZLIB_BUILDING_TESTS
