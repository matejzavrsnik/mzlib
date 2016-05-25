// 
// Author: Matej Zavrsnik (matejzavrsnik.com)
//

#include "../include/markov_chain.h"
#include "gtest/gtest.h"

#include <fstream>

// The fixture    
class test_markov_chain : public ::testing::Test {

protected:
     
   test_markov_chain () {}
   virtual ~test_markov_chain () {}
   virtual void SetUp() {}
   virtual void TearDown() {}
  
};

// Tests

TEST_F(test_markov_chain, basic_test) 
{
   mzlib::cmarkov_chain<int> markov_chain;
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

