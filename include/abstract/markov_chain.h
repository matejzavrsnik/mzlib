//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_MARKOV_CHAIN_H
#define MZLIB_MARKOV_CHAIN_H


#include <vector>
#include <map>

#include "probabilator.h"
#include "../tools/random.h"
#include "../lang/optional.h"

namespace mzlib
{

// generic markov chain generator
template<class T> 
class markov_chain
{
    
private:
        
   optional<T> m_previous_state;
   T m_next_state;
   std::map<T, probabilator<T>> m_states;
        
   const T get_random_state () 
   {
      return get_random_element(m_states)->first;
   }
        
protected:
        
   void read (T state) 
   {
      if(m_previous_state.is_set()) {
         m_states[m_previous_state.get()].add_event(state);
         m_previous_state = state;
      }
      else {
         m_previous_state = state;
      }
   }
        
   const T get() 
   {
      T& return_state = m_next_state;
      probabilator<T>& probabilator = m_states[m_next_state];
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

#endif /* MZLIB_MARKOV_CHAIN_H */

