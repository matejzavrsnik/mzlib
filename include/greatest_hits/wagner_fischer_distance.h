//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_WAGNER_FISCHER_DISTANCE_H
#define MZLIB_WAGNER_FISCHER_DISTANCE_H

#include <vector>
#include <algorithm>
#include "../tools/fast_min.h"

namespace mzlib {
        
template <class TYPE>
int wagner_fischer_distance (const TYPE& str1, const TYPE& str2)
{
   // Optimised version of this algorithm only needs two vectors, current and 
   // previous rows of the matrix
   std::vector<int> prev_row (str2.size()+1, 0);
   std::vector<int> curr_row (str2.size()+1, 0);
   
   int n=0;
   std::generate (curr_row.begin(), curr_row.end(), [&n]{ return n++; });
   
   // The core of the algorithm: a crazy cacophony of narrowly avoided off-by-ones
   for(size_t i = 1; i<str1.size()+1; i++) {
      // Some maintenance due to the fact there are only two lines available
      prev_row = curr_row;
      std::fill (curr_row.begin(), curr_row.end(), 0);;
      curr_row [0] = i;
      
      for(size_t j = 1; j<str2.size()+1; j++) {
         if(str1 [i-1] == str2 [j-1]) {
            curr_row [j] = prev_row [j-1];
         }
         else {
            curr_row [j] = fast_min(
               prev_row [j-1] +1, // substitution
               prev_row [j]   +1, // deletion
               curr_row [j-1] +1  // insertion
            );
         }
      }
   }

   return curr_row [curr_row.size()-1];
}

} // namespace

#endif // MZLIB_WAGNER_FISCHER_DISTANCE_H
