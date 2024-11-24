//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_IS_TRIVIAL_REPETITION_H
#define MZLIB_IS_TRIVIAL_REPETITION_H

#include "range_is_within.h"
#include "../tools/tally.h"

#include <vector>

namespace mzlib {
   
// If a certain smaller string is repeated in larger string, naturally all 
// substrings of that will be repeated too. Sometimes we don't want that 
// and we want to recognise them as duplicates even if they don't completely 
// align.

// Example string: duckduckgo.com
// Repeated twice: duck
// Also repeated: duc, uck, du, uc, ck

// The following function identifies such trivially repeated substrings.

template<typename Range, typename SizeT = long unsigned>
bool is_trivial_repetition(
   const std::vector<tally<Range, SizeT>>& bookkeeping, 
   const tally<Range, SizeT>& range)
{
   for(const auto& booked_range : bookkeeping)
      if (is_within(booked_range.itself(), range.itself())
         && booked_range.count() == range.count())
         return true;
   return false;
}

} // namespace

#endif // MZLIB_IS_TRIVIAL_REPETITION_H
