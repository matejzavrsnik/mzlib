// 
// Author: Matej Zavrsnik (matejzavrsnik.com)
//

#ifndef QUADTREE_IT_MASSCENTRES_H
#define QUADTREE_IT_MASSCENTRES_H

#include <iterator>
#include <memory> // shared_ptr
#include "quadtree.h"

namespace mzlib {

// Const iterator through all mass centres
template<class T>
class quadtree_it_masscentres : 
   public std::iterator<std::forward_iterator_tag, cbinded_mass_centre<T>>
{

private:

   std::vector<std::shared_ptr<cbinded_mass_centre<T>>> m_mass_centres;
   typename std::vector<std::shared_ptr<cbinded_mass_centre<T>>>::iterator m_current_it;

   void setup (const T& data) 
   {
   }

public:

   explicit quadtree_it_masscentres (const T& data, double quotient)
   { 
      setup(data); 
   }
   
   quadtree_it_masscentres ()
   { 
      m_current_it = m_mass_centres.end();
   }

   quadtree_it_masscentres (quadtree_it_masscentres&&) = default;
   quadtree_it_masscentres (const quadtree_it_masscentres&) = default;

   quadtree_it_masscentres<T>* operator++ () 
   {
      m_current_it = ++m_current_it;
      return this; 
   }
        
   quadtree_it_masscentres<T>* operator++ (int) 
   { 
      //todo: I know, I lie about postfix. Will fix some day, I promise.
      m_current_it = ++m_current_it;
      return this; 
   }

   cbinded_mass_centre<T>* operator-> ()
   {
      // It is OK to return non-const mass centres here, because they are not from
      // the tree itself, but are instead prefabricated constructs. The user is 
      // allowed to disturb them at her own discretion.
      return (*m_current_it).get();
   }

   cbinded_mass_centre<T>& operator* ()
   { 
      // First * dereferences iterator, second * dereferences smart pointer
      return *(*m_current_it); 
   }
   
   bool operator== (const quadtree_it_masscentres<T>& other) const 
   { 
      // Infinite recursion guard
      if (this == &other) return true;
      return (m_current_it == other.m_current_it);  
   }

   bool operator!= (const quadtree_it_masscentres<T>& other) const 
   { 
      return !(*this == other); 
   }
};

} // namespace mzlib

#endif // QUADTREE_IT_MASSCENTRES_H

