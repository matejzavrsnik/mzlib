//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_FIND_SUBSEQUENCE_H
#define MZLIB_FIND_SUBSEQUENCE_H

#include "contains_range.h"

#include <iterator>
#include <vector>
#include <algorithm>

namespace mzlib {

// finds in given collection where given subsequence is repeated
// and returns a set of these iterators to their starts
   
template<typename Iterator>
std::vector<Iterator> find_subsequence(
   Iterator full_begin, Iterator full_end,
   Iterator sub_begin, Iterator sub_end)
{
   std::vector<Iterator> locations;
   auto found_at = full_begin;
   auto sub_length = std::distance(sub_begin, sub_end);
   
   do 
   {
      found_at = contains_range(found_at, full_end, sub_begin, sub_end);
      
      if(found_at != full_end)
      {
         locations.push_back(found_at);
         std::advance(found_at, sub_length);
      }
      
   } while (found_at != full_end);
   
   return locations;
}

template<typename Iterator, typename Searcher>
std::vector<Iterator> find_subsequence(
   Iterator full_begin, Iterator full_end,
   const Searcher& searcher, unsigned sub_length)
{
   std::vector<Iterator> locations;
   auto found_at = full_begin;
   
   do 
   {
      found_at = std::search(found_at, full_end, searcher);
      
      if(found_at != full_end)
      {
         locations.push_back(found_at);
         std::advance(found_at, sub_length);
      }
      
   } while (found_at != full_end);
   
   return locations;
}


} // namespace

#endif // MZLIB_FIND_SUBSEQUENCE_H
