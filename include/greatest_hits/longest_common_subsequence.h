//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_LONGEST_COMMON_SUBSEQUENCE_H
#define MZLIB_LONGEST_COMMON_SUBSEQUENCE_H

#include <vector>
#include <string_view>
#include <algorithm>

#include "../lang/concepts.h"

namespace mzlib {
     
namespace internal {

template<typename Sequence>
int lcs_implementation(
    const size_t idx1, const size_t idx2, 
    const Sequence& seq1, const Sequence& seq2,
    const int& lcs_so_far,
    std::vector<std::vector<int>>& cache)
{
    if(idx1 == seq1.size() || idx2 == seq2.size())
        return lcs_so_far;

    if(cache[idx1][idx2] != -1)
        return cache[idx1][idx2] + lcs_so_far;

    int lcs_complete = seq1[idx1] == seq2[idx2]
        ? lcs_implementation(idx1+1, idx2+1, seq1, seq2, lcs_so_far+1, cache)
        : std::max(
            lcs_implementation(idx1+1, idx2,   seq1, seq2, lcs_so_far, cache), 
            lcs_implementation(idx1,   idx2+1, seq1, seq2, lcs_so_far, cache));

    cache[idx1][idx2] = lcs_complete - lcs_so_far;
    return lcs_complete;
}
   
} // namespace internal

template<typename Sequence>
int longest_common_subsequence (const Sequence& str1, const Sequence& str2)
{
   std::vector<std::vector<int>> cache(str1.size(), std::vector<int>(str2.size(), -1));
   
   return internal::lcs_implementation(0, 0, str1, str2, 0, cache);
}

} // namespace

#endif // MZLIB_LONGEST_COMMON_SUBSEQUENCE_H
