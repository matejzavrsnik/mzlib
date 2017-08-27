//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_PROBABILATOR_H
#define	MZLIB_PROBABILATOR_H

#include <algorithm>
#include "../tools/random.h"
#include "../lang/exceptions.h"

namespace mzlib {
   
template<class T>
class probabilator
{
        
private:

   typedef std::pair<T /*event*/, double /*probability level*/> event_t;
   std::vector<event_t> m_events;
        
   void normalise () 
   {
      double sum = 0;
      for(auto const& e : m_events) sum += e.second;
      for(auto& e : m_events) e.second /= sum;
   }
        
   void levelise () 
   {
      // The point of this function is to attach "levels" to each event, so that
      // when a random number [0,1] is generated, it will fall into "levels" in
      // a statistical meaningful way. Example: if there are 3 events with probabilities
      // 15%, 30%, and 55%, and then if you attach levels 0.15, 0.45, and 1.0,
      // and then you generate random number [0,1], there will be 15% chance the
      // number will fall under level 0.15, 30% chance it will be between 0.15 and 0.45,
      // and further 55% chance it will be between 0.45 and 1.0, all exactly corresponding
      // to original probabilities for events.
      double previous_level = 0;
      for (auto& e : m_events) {
         e.second += previous_level;
         previous_level = e.second;
      }
   }
        
public:

   void add_event (T event, double probability_level) 
   {
      m_events.push_back(std::make_pair(event, probability_level));
   }
        
   void add_event (T event) 
   {
      auto found = std::find_if (m_events.begin(), m_events.end(), 
         [&] (event_t& e)
         {
            return e.first == event;
         });
      if (found == m_events.end()) {
         m_events.push_back(std::make_pair(event, 1));
      }
      else {
         found->second += 1;
      }
   }
        
   void wrap_up () 
   {
      normalise();
      levelise();
   }
        
   const T get_event () 
   {
      double random = get_random_double_between_0_1();
      for (auto event_it = m_events.begin(); event_it != m_events.end(); ++event_it) {
         if (random < event_it->second) {
            return event_it->first;
         }
      }
      throw exception::is_empty(); // I couldn't imagine other way out of this
   }
   
   unsigned count_events () const 
   {
      return m_events.size();
   }

};

} // namespace

#endif /* MZLIB_PROBABILATOR_H */

#ifdef MZLIB_BUILDING_TESTS

#ifndef MZLIB_PROBABILATOR_TESTS_H
#define MZLIB_PROBABILATOR_TESTS_H

TEST(probabilator, demo_test) 
{
   mzlib::probabilator<int> probabilator;
   probabilator.add_event(0, 10); // event 1, probability 10%
   probabilator.add_event(1, 30); // event 2, probability 30%
   probabilator.add_event(2, 60); // event 3, probability 60%
   probabilator.wrap_up();
    
   std::vector<int> event_occurences = {0,0,0};
   int repetitions = 10000;
   for(int i=0; i<repetitions; ++i) {
      int event = probabilator.get_event();
      event_occurences[event]++;
   }
    
   ASSERT_NEAR(event_occurences[0], repetitions*0.1, repetitions*0.02); // event 0 happened 1000 times +- 200
   ASSERT_NEAR(event_occurences[1], repetitions*0.3, repetitions*0.02); // event 1 happened 3000 times +- 200
   ASSERT_NEAR(event_occurences[2], repetitions*0.6, repetitions*0.02); // event 2 happened 6000 times +- 200
}

#endif // MZLIB_PROBABILATOR_TESTS_H

#endif // MZLIB_BUILDING_TESTS

