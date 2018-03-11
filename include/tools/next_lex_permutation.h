//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_NEXT_LEX_PERMUTATION_H
#define MZLIB_NEXT_LEX_PERMUTATION_H

#include <algorithm>
#include "../iterators/conditional_find.h"

namespace mzlib {
    
// I think everybody except me has written lexical permutation function at least 
// once in their lives. Here it goes. (FYI: there is a function in std:: that
// does this and probably does it better, if you actually need one.)
template<class Iterator>
void next_lex_permutation(Iterator begin, Iterator end)
{
   auto k = find_in(begin, end).last().smaller().than_next();
   if (k==end) return; // done, this was last permutation
   
   auto l = find_in(begin, end).last().greater().than(*k);
   if (l==end) return; // done
   
   std::iter_swap(k, l);
   std::reverse(k+1, end);
}

} // namespace

#endif // MZLIB_NEXT_LEX_PERMUTATION_H
