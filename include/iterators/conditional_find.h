//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_CONDITIONAL_FIND_ITERATOR_H
#define MZLIB_CONDITIONAL_FIND_ITERATOR_H

#include "distance_comparison.h"

namespace mzlib {
   
template<class Iterator>
class find_in
{
private:
   
   enum class position { first, last } m_position;
   enum class comparison { smaller, greater } m_comparison;
   Iterator m_begin;
   Iterator m_end;
   
public:
   
   find_in(Iterator begin, Iterator end) :
      m_begin(begin),
      m_end(end)
   {}
   
   find_in& last()
   {
      m_position = position::last;
      return *this;
   }

   find_in& smaller()
   {
      m_comparison = comparison::smaller;
      return *this;
   }
   
   find_in& greater()
   {
      m_comparison = comparison::greater;
      return *this;
   }
   
   template<class T>
   Iterator than(T&& value)
   {
      if (m_position == position::last) {
         if (m_comparison == comparison::smaller) {
            return last_smaller_than(value);
         }
         else if (m_comparison == comparison::greater) {
            return last_greater_than(value);
         }
      }
      else if (m_position == position::first) {
         if (m_comparison == comparison::smaller) {
            return first_smaller_than(value);
         }
         else if (m_comparison == comparison::greater) {
            return first_greater_than(value);
         }
      }
      return m_end; // not found by default
   }
   
   Iterator than_next()
   {
      if (m_position == position::last) {
         if (m_comparison == comparison::smaller) {
            return last_smaller_than_next();
         }
         else if (m_comparison == comparison::greater) {
            return last_greater_than_next();
         }
      }
      else if (m_position == position::first) {
         if (m_comparison == comparison::smaller) {
            return first_smaller_than_next();
         }
         else if (m_comparison == comparison::greater) {
            return first_greater_than_next();
         }
      }
      return m_end; // not found by default
   }
   
private:

   template<class T>
   Iterator last_smaller_than(T&&)
   {
      // not implemented
      return m_end;
   }
   
   template<class T>
   Iterator last_greater_than(T&& value)
   {
      auto last = m_end;
      while(last != m_begin) 
         if (*(--last) > value) 
            return last;
      return m_end; // not found
   }
   
   template<class T>
   Iterator first_smaller_than(T&&)
   {
      // not implemented
      return m_end;
   }
   
   template<class T>
   Iterator first_greater_than(T&&)
   {
      // not implemented
      return m_end;
   }

   Iterator last_smaller_than_next()
   {
      if (mzlib::is_distance_smaller(m_begin, m_end, 2)) 
         return m_end; // not found
      
      auto next = m_end;
      auto prev = next-1;
      while(prev != m_begin) 
         if (*(--prev) < *(--next)) 
            return prev;
      return m_end; // not found
   }
   
   Iterator last_greater_than_next()
   {
      // not implemented
      return m_end;
   }
   
   Iterator first_smaller_than_next()
   {
      // not implemented
      return m_end;
   }
   
   Iterator first_greater_than_next()
   {
      // not implemented
      return m_end;
   }
      
};

} // namespace

#endif // MZLIB_CONDITIONAL_FIND_ITERATOR_H
