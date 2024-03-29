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
   for (unsigned int to = n, from = 0; to < v.size(); ++to, from = to % n) {
      v[to] = v[from];
   }
}

} // namespace

#endif // MZLIB_COPY_FIRST_N_OVER_REST_H
