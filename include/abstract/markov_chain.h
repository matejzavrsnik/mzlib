//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_MARKOV_CHAIN_H
#define MZLIB_MARKOV_CHAIN_H

#include "probabilator.h"
#include "../iterators/get_random.h"
#include <map>
#include <optional>


namespace mzlib
{   

template<class T> using markov_chain = std::map<T, probabilator<T>>;

// generic markov chain generator
template<class T> 
class markov_chain_traverser
{
    
private:
        
   T m_next_state;
   markov_chain<T> m_markov_chain;
        
public:
   
   markov_chain_traverser(markov_chain<T> chain)
   {
      m_markov_chain = chain;
      set_random_next_state ();
   }
   
   virtual void set_random_next_state () 
   {
      m_next_state = get_random_element(m_markov_chain.begin(), m_markov_chain.end())->first;
   }
        
   virtual const T get_next() 
   {
      T& return_state = m_next_state;
      probabilator<T>& probabilator = m_markov_chain[m_next_state];
      if (probabilator.count_events() == 0) {
         set_random_next_state();
      }
      else {
         m_next_state = probabilator.get_event();
      }
      return return_state;
   }

};

template<class T> 
class markov_chain_builder
{
private:
      
   std::optional<T> m_previous_state;
   std::set<T> m_forbidden_states;
   markov_chain<T> m_markov_chain;
   
public:

   void add_forbidden_states(std::vector<T> forbidden_states)
   {
      m_forbidden_states.insert(
         forbidden_states.begin(), 
         forbidden_states.end());
   }
   
   virtual void add_state (T next_state)
   {
      if(m_previous_state.has_value()) {
         if(m_forbidden_states.count(next_state) == 0)
         {
            m_markov_chain[m_previous_state.value()].add_event(next_state);
            m_previous_state = next_state;
         }
      }
      else {
         m_previous_state = next_state;
      }
   }
   
   virtual void add_state (T prev_state, T next_state)
   {
      m_previous_state = prev_state;
      add_state (next_state);
   }
   
   virtual markov_chain<T> wrap_up ()
   {
      for (auto& state : m_markov_chain) {
         state.second.wrap_up();
      }
      return m_markov_chain;
   }
};

}

#endif /* MZLIB_MARKOV_CHAIN_H */
