//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_MEDIAN_MAINTENANCE_H
#define MZLIB_MEDIAN_MAINTENANCE_H

#include "../lang/exceptions.h"

#include <set>

namespace mzlib {
     
// Will calculate median in O(1) after inserting numbers in O(logn).
// Can also remove numbers in O(logn) and it will still get you median in O(1).
// If even number of numbers, median is average of the two middle ones.
  
template<typename T>
class median_maintenance
{
   std::multiset<T> m_small;
   std::multiset<T> m_big;

   const T& biggest_small() 
   { 
      return *m_small.crbegin(); 
   }

   void remove_biggest_small() 
   {
      remove_from_small(biggest_small());
      //m_small.erase(m_small.rbegin());
   }

   const T& smallest_big() 
   { 
      return *m_big.cbegin(); 
   }

   void remove_smallest_big() 
   {
      m_big.erase(m_big.begin());
   }

   void insert_big(const T& element) 
   {
      m_big.insert(element);
   }

   void insert_small(const T& element) 
   {
      m_small.insert(element);
   }

   void remove_from_big(const T& element) 
   {
      m_big.erase(m_big.find(element));
   }

   void remove_from_small(const T& element) 
   {
      m_small.erase(m_small.find(element));
   }

   bool empty() 
   {
      return m_small.size() == 0;
   }

   void move_big_to_small() 
   {
      m_small.insert(smallest_big());
      remove_smallest_big();
   }

   void move_small_to_big() 
   {
      m_big.insert(biggest_small());
      remove_biggest_small();
   }

   void balance() 
   {
      int surplus_of_smalls = m_small.size() - m_big.size();
        
      if (surplus_of_smalls == -1)
         move_big_to_small();

      // if (surplus_of_smalls == 0) -> balance, perfect
      // if (surplus_of_smalls == 1) -> odd number of elements, keep median in small

      if (surplus_of_smalls == 2)
         move_small_to_big();
   }

public:
   
   median_maintenance() = default;
   
   median_maintenance(std::initializer_list<T> il)
   {
      for(const auto& element : il)
         insert(element);
   }

   void insert(const T& element) 
   {
      if (empty()) 
      {
         insert_small(element);
         return;
      }
        
      if (element > biggest_small())
         insert_big(element);
      else
         insert_small(element);

      balance();
   }

   void remove(const T& element) 
   {
      if (element > biggest_small())
         remove_from_big(element);
      else
         remove_from_small(element);

      balance();
   }

   T get_median()
   {
      if(empty())
         throw mzlib::exception::is_empty("median of empty set is nonsense");
      
      int surplus_of_smalls = m_small.size() - m_big.size();
        
      // if I maintained everything right, there should only be two options:
        
      if (surplus_of_smalls == 0) // balance
         return (smallest_big() + biggest_small()) / 2;
      else  // if (surplus_of_smalls == 1)  odd number of elements, median in small
         return biggest_small();
   }

};

} // namespace

#endif // MZLIB_MEDIAN_MAINTENANCE_H
