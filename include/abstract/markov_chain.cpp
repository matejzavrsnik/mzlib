//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "markov_chain.h"

TEST(markov_chain_builder, basic_test) 
{
   mzlib::markov_chain_builder<int> markov_chain_builder;
   // 1 -> 2 -> 1
   //   -> 3 -> 2
   for (int number : {1,2,1,3,2})
      markov_chain_builder.add_state(number);
   
   mzlib::markov_chain<int> mc = markov_chain_builder.wrap_up();
   
   ASSERT_EQ(2, mc[1].count_events());
   ASSERT_EQ(1, mc[2].count_events());
   ASSERT_EQ(1, mc[3].count_events());
}

TEST(markov_chain, basic_test) 
{
   mzlib::markov_chain_builder<int> markov_chain_builder;
   // 1 -> 2 -> 1
   //   -> 3 -> 2
   for (int number : {1,2,1,3,2})
      markov_chain_builder.add_state(number);
   
   auto mc = markov_chain_builder.wrap_up();
   
   mzlib::markov_chain_traverser<int> markov_chain(mc);
   
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