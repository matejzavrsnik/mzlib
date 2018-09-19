//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_RANGE_H
#define MZLIB_RANGE_H

namespace mzlib {


// for when you want to:
// - the function to return begin and end at the same time
// - advance begin and end for the same amount
// - save calls to std::distance with the same begin and end

template<typename It>
class range 
{

private:
      
   mutable int m_distance = -1;
   It m_begin, m_end;
   
public:
   
   range(It begin, It end) :
      m_distance(-1),
      m_begin(begin),
      m_end(end)
   {}
      
   const It& beg() const
   {
      return m_begin;
   }
   
   const It& end() const
   { 
      return m_end; 
   }
   
   void advance(size_t distance)
   {
      std::advance(m_begin, distance);
      std::advance(m_end, distance);
   }
   
   size_t distance()  const
   {
      // lazy evaluate and remember
      if(m_distance<0)
         m_distance = std::distance(m_begin, m_end);
      return m_distance;
   }
};

} // namespace

#endif // MZLIB_RANGE_H
