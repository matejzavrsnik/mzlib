//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef FAST_MIN_H
#define FAST_MIN_H

namespace mzlib {
   
// Returns the smallest of three numbers 2x-3x faster than std::min({i,j,k})
template <class T> T& fast_min_ref (T& min1, T& min2, T& min3)
{
   // Beware, min-field ahead!
   return 
      min1 < min2 ?
         (min1 < min3 ? min1 : min3) :
         (min2 < min3 ? min2 : min3);
}

template <class T> T&& fast_min (T&& min1, T&& min2, T&& min3)
{
   // Beware, min-field ahead!
   return std::move(
      min1 < min2 ?
         (min1 < min3 ? min1 : min3) :
         (min2 < min3 ? min2 : min3));
}

} // namespace

#endif // FAST_MIN_H

#ifdef MZLIB_BUILDING_TESTS

TEST(fast_min, basic_lvalue) 
{
   int i1 = 1, i2 = 2, i3 = 3;
   // all permutations
   ASSERT_EQ(1, mzlib::fast_min_ref(i1, i2, i3));
   ASSERT_EQ(1, mzlib::fast_min_ref(i1, i3, i2));
   ASSERT_EQ(1, mzlib::fast_min_ref(i2, i1, i3));
   ASSERT_EQ(1, mzlib::fast_min_ref(i2, i3, i1));
   ASSERT_EQ(1, mzlib::fast_min_ref(i3, i1, i2));
   ASSERT_EQ(1, mzlib::fast_min_ref(i3, i2, i1));
}

TEST(lvalue, basic_rvalue) 
{
   // all permutations
   ASSERT_EQ(1, mzlib::fast_min(1, 2, 3));
   ASSERT_EQ(1, mzlib::fast_min(1, 3, 2));
   ASSERT_EQ(1, mzlib::fast_min(2, 1, 3));
   ASSERT_EQ(1, mzlib::fast_min(2, 3, 1));
   ASSERT_EQ(1, mzlib::fast_min(3, 1, 2));
   ASSERT_EQ(1, mzlib::fast_min(3, 2, 1));
}

#endif // MZLIB_BUILDING_TESTS


