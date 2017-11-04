//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_COPY_FIRST_N_OVER_REST_H
#define MZLIB_COPY_FIRST_N_OVER_REST_H

namespace mzlib {
    
template<class T> void copy_first_n_over_rest (T& v, size_t n)
{
   if (n >= v.size()) return;
   for (uint to = n, from = 0; to < v.size(); ++to, from = to % n) {
      v[to] = v[from];
   }
}

} // namespace

#endif // MZLIB_COPY_FIRST_N_OVER_REST_H

#ifdef MZLIB_COPY_FIRST_N_OVER_REST_TESTS_H
#undef MZLIB_COPY_FIRST_N_OVER_REST_TESTS_H

TEST(copy_first_n_over_rest, demo) 
{
   std::vector<int> v       {1,2,3, 4,5,6, 7,8,9, 10};
   std::vector<int> expected{1,2,3, 1,2,3, 1,2,3, 1};
   
   mzlib::copy_first_n_over_rest(v, 3);
   
   ASSERT_EQ(expected, v);
}

#endif // MZLIB_COPY_FIRST_N_OVER_REST_TESTS_H

