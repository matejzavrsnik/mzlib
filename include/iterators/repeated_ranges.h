//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_REPEATED_RANGES_H
#define MZLIB_REPEATED_RANGES_H

#include "range_iterator.h"
#include "range.h"
#include "is_trivial_repetition.h"
#include "sequence_sightings.h"
#include "find_subsequence.h"

#include <optional>

namespace mzlib {

// finds all ranges that repeat in a collection and
// returns which range is repeated how many times.
   
template<typename It> 
std::vector<sequence_sightings<It>> repeated_sequences(
   It begin, It end,
   std::optional<int> minimum_length = std::nullopt,
   std::optional<int> maximum_length = std::nullopt) 
{
   std::vector<sequence_sightings<It>> result;
   
   range_iterator<It> rit(
      begin, end, 
      minimum_length.value_or(2),
      maximum_length.value_or(std::distance(begin, end)/2));
   
   std::vector<tally<range<It>>> bookkeeping;
   
   // for each possible subsequence in this sequence
   for (auto r = rit.first(); !rit.end(r); r = rit.next(r)) 
   {  
      // if it can't possibly fit, give up
      auto distance_to_end = std::distance(r.end(), end);
      if (distance_to_end < r.distance())
      {
         r.advance(distance_to_end);
         continue;
      }

      // Between then the following are by far the most expensive calls.
      //   - creating the searcher: ~70 % of cycles
      //   - searching: ~25 % of cycles
      // Performance improvement to anything that does not result in less
      // calls to this can only improve 5 % and is not worth it.
      auto searcher = std::boyer_moore_horspool_searcher(
         r.begin(), r.end());
      std::vector<It> additionals = find_subsequence(
         r.end(), end, searcher, r.distance());

      if (!additionals.empty()) 
      {
         std::vector<It> repeated;
         repeated.reserve(additionals.size()+1);
         repeated.push_back(r.begin());
         
         for(auto& additional : additionals)
            repeated.push_back(
               std::move(additional));

         tally<range<It>> repeated_range_count{r, repeated.size()};
         
         if (!is_trivial_repetition(bookkeeping, repeated_range_count))
         {
   
            bookkeeping.push_back(repeated_range_count);

            result.push_back(sequence_sightings<It>{ 
               std::move(repeated),
               std::distance(r.begin(), r.end())});
         }
      }
       
      
      
   }
   return result;
}


} // namespace

#endif // MZLIB_REPEATED_RANGES_H
