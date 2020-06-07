//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_NESTED_ITERATION_H
#define MZLIB_NESTED_ITERATION_H

#include <vector>

namespace mzlib {

// For when you need all possible combinations of N elements in a collection
// of size M. For example, if the collection is {1,2,3,4,5}, you might
// need {1,2,3}, {1,2,4}, {1,2,5}, {1,3,4}, {1,3,5}, etc. If that is the case,
// you can use this class.
   
template<typename Iterator>
class nested_iteration
{
   
private:
   
   // iterators to be returned if not finished yet
   std::vector<Iterator> m_iterators;
   // one after last valid position for a specific iterator
   std::vector<Iterator> m_ends;
   bool m_end_flag;
   
   void generate_initial_iterators(
      const Iterator begin, 
      const Iterator end, 
      size_t num)
   {
      for(auto it = begin; it != end && num > 0; ++it, --num)
         m_iterators.push_back(it);
   }
   
   void generate_end_iterators(
      Iterator begin, 
      const Iterator end,
      const size_t distance,
      const size_t count)
   {
      std::advance(begin, distance - count);
      do
      {
         std::advance(begin, 1);
         m_ends.push_back(begin);
      }
      while(begin != end);
   }
   
   bool reached_the_end(const int iterator_index) const
   {
      return (m_iterators[iterator_index] == m_ends[iterator_index]);
   }
   
   bool is_first(const int iterator_index) const
   {
      return (iterator_index == 0);
   }
   
   void wrap_around(const int iterator_index)
   {
      const int previous = iterator_index-1;
      
      // try advance previous for one step (will recurse)
      advance(previous);
      
      // set current one step ahead of previous
      m_iterators[iterator_index] = std::next(m_iterators[previous]);
   }
   
   void advance(int iterator_index)
   {
      // boldly advance ...
      std::advance(m_iterators[iterator_index], 1);

      // ... then fix the consequences if needed
      if (reached_the_end(iterator_index))
      {
         if (is_first(iterator_index)) m_end_flag = true;
         else wrap_around(iterator_index);
      }
   }
   
public:
   
   nested_iteration(
      const Iterator begin, 
      const Iterator end, 
      const size_t count) 
      :
      m_end_flag(false)
   {
      const size_t distance = std::distance(begin, end);
      if (count > distance) 
      {
         m_end_flag = true;
      }
      else
      {
         generate_initial_iterators(begin, end, count);
         generate_end_iterators(begin, end, distance, count);
      }
   }
   
   void next()
   {
      const int last_iterator_index = m_iterators.size()-1;
      advance(last_iterator_index);
   }
   
   bool end() const
   {
      return m_end_flag;
   }
   
   const std::vector<Iterator>& get() const
   {
      return m_iterators;
   }
};

}

#endif // MZLIB_NESTED_ITERATION_H