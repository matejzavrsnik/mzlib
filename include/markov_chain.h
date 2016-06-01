//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MARKOV_CHAIN_H
#define MARKOV_CHAIN_H


#include <vector>
#include <map>

#include "utilities.h"
#include "utils_random.h"

namespace mzlib
{

// generic markov chain generator
template<class T> 
class cmarkov_chain
{
    
private:
        
   T m_previous_state;
   bool m_previous_state_set = false;     
   T m_next_state;
   std::map<T, mzlib::util::cprobabilator<T>> m_states;
        
   const T get_random_state () 
   {
      return mzlib::util::get_random_element(m_states)->first;
   }
        
protected:
        
   void read (T state) 
   {
      if(m_previous_state_set) {
         m_states[m_previous_state].add_event(state);
         m_previous_state = state;
      }
      else {
         m_previous_state = state;
         m_previous_state_set = true;
      }
   }
        
   const T get() 
   {
      T& return_state = m_next_state;
      mzlib::util::cprobabilator<T>& probabilator = m_states[m_next_state];
      if (probabilator.count_events() == 0) {
         m_next_state = get_random_state();
      }
      else {
         m_next_state = probabilator.get_event();
      }
      return return_state;
   }
        
public:
        
   virtual void read_next (T state) 
   {  
      read(state);
   }
        
   void wrap_up () 
   {
      for (auto& state : m_states) {
         state.second.wrap_up();
      }
      m_next_state = get_random_state();
   }
        
   virtual T get_next () 
   {
      return get();
   }
};
    
}

#endif // MARKOV_CHAIN_H

