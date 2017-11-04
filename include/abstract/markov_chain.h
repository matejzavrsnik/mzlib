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

// generic markov chain generator
template<class T> 
class markov_chain
{
    
private:
        
   std::optional<T> m_previous_state;
   T m_next_state;
   std::map<T, probabilator<T>> m_states;
        
   const T get_random_state () 
   {
      return get_random_element(m_states.begin(), m_states.end())->first;
   }
        
protected:
        
   void read (T state) 
   {
      if(m_previous_state.has_value()) {
         m_states[m_previous_state.value()].add_event(state);
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

#ifdef MZLIB_MARKOV_CHAIN_TESTS_H
#undef MZLIB_MARKOV_CHAIN_TESTS_H

TEST(markov_chain, basic_test) 
{
   mzlib::markov_chain<int> markov_chain;
   // 1 -> 2 -> 1
   //   -> 3 -> 2
   for (int number : {1,2,1,3,2})
      markov_chain.read_next(number);
   markov_chain.wrap_up();
   
   int count = 0, repetitions = 10000, next_number;
   std::array<int,3> stats = {0,0,0};
   std::vector<int> sequence;
   do {
      ++count;
      next_number = markov_chain.get_next();
      ++stats[next_number-1];
      sequence.push_back(next_number);
   }
   while (count < repetitions);
    
   // test statistical probability of items occurring
   ASSERT_NEAR(stats[0], repetitions*0.4, repetitions*0.02); // 0 happened 4000 times +- 200
   ASSERT_NEAR(stats[1], repetitions*0.4, repetitions*0.02); // 1 happened 4000 times +- 200
   ASSERT_NEAR(stats[2], repetitions*0.2, repetitions*0.02); // 2 happened 2000 times +- 200

   // test for impossible sequences, given markov chain rules
   size_t number, previous;
   for (number = 1, previous=0; number < sequence.size(); ++number, ++previous) {
      ASSERT_NE(sequence[number], sequence[previous]) << "no transition allows repeated number";
      if(sequence[number]==1) {
         ASSERT_EQ(sequence[previous], 2) 
            << "defined only 2->1, this is invalid: " 
            << sequence[previous] << "->" << sequence[number];
      }
      if (sequence[number]==3) {
         ASSERT_EQ(sequence[previous], 1) 
            << "defined only 1->3, this is invalid: " 
            << sequence[previous] << "->" << sequence[number];
      }
   }
}

#endif // MZLIB_MARKOV_CHAIN_TESTS_H

