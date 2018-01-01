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
   
template<class T> class markov_chain_builder;
   
// generic markov chain generator
template<class T> 
class markov_chain
{
    
private:
        
   T m_next_state;
   std::map<T, probabilator<T>> m_states;
        
public:
   
   virtual const T get_random_state () 
   {
      return get_random_element(m_states.begin(), m_states.end())->first;
   }
        
   virtual const T get_next() 
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
        
   friend class markov_chain_builder<T>;
};

template<class T> 
class markov_chain_builder
{
private:
      
   std::optional<T> m_previous_state;
   std::set<T> m_forbidden_states;
   markov_chain<T>& m_markov_chain;
   
public:
   
   markov_chain_builder(markov_chain<T>& mc)
      : m_markov_chain(mc) 
   {
         m_markov_chain.m_states.clear();
   };

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
            m_markov_chain.m_states[m_previous_state.value()].add_event(next_state);
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
   
   virtual void wrap_up ()
   {
      for (auto& state : m_markov_chain.m_states) {
         state.second.wrap_up();
      }
      m_markov_chain.m_next_state = m_markov_chain.get_random_state();
   }
};

}

#endif /* MZLIB_MARKOV_CHAIN_H */

#ifdef MZLIB_MARKOV_CHAIN_TESTS_H
#undef MZLIB_MARKOV_CHAIN_TESTS_H

TEST(markov_chain, basic_test) 
{
   mzlib::markov_chain<int> markov_chain;
   mzlib::markov_chain_builder<int> markov_chain_builder(markov_chain);
   // 1 -> 2 -> 1
   //   -> 3 -> 2
   for (int number : {1,2,1,3,2})
      markov_chain_builder.add_state(number);
   
   markov_chain_builder.wrap_up();
   
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

