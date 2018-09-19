//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_RANGE_ITERATOR_H
#define MZLIB_RANGE_ITERATOR_H

#include "range.h"

namespace mzlib {

template<typename It>
class range_iterator
{
   const It m_begin, m_end;
   const int m_min_distance;
   
public:
   
   range_iterator(It begin, It end, int min_distance) :
      m_begin(begin),
      m_end(end),
      m_min_distance(min_distance > 0 ? min_distance : 1)
   {}

   range<It> first() 
   {
      It end_copy = m_end;
      std::advance(end_copy, -1);
      return { m_begin,  end_copy };
   }
   
   range<It> next(const range<It>& r) 
   {
      if (r.end() != m_end) {
         range<It> new_r = r;
         new_r.advance(1);
         return new_r;
      }
      else if (r.distance() > 0){
         It begin = m_begin;
         It end = m_begin;
         std::advance(end, r.distance()-1);
         return range<It>(begin, end);
      }
      
      return r;
   }
   
   bool end(const range<It>& r) 
   {
      if (r.distance() < m_min_distance)
         return true;
      else 
         return false;
   }
};

} // namespace

#endif // MZLIB_RANGE_ITERATOR_H
