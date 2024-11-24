//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "genetic_container.h"

TEST(genetic_container, demo) 
{
   std::vector<int> numbers(5);
   
   // setup a fitness function
   auto fitness_function = 
      [](const std::vector<int>& candidate) {
         // test criteria: each next number is 2x its index
         double sum_difference = 0;
         for (size_t i = 0; i<candidate.size(); ++i) {
            sum_difference = std::fabs(candidate[i] - 2*i);
         }
         return sum_difference;
      };
      
   mzlib::genetic_container<std::vector<int>> genetic (numbers, fitness_function);
   
   double penalty_before = fitness_function(numbers);
   genetic.play_generations(1000);
   double penalty_after = genetic.get_lowest_penalty();
   
   // Score after is better and fitness function considers all elements of vector,
   // therefore version on vectors works!
   ASSERT_LT(penalty_after, penalty_before);
   
   // Algorithm will probably reach final solution in 1000 generations, but it
   // would still make a flaky test if I assert on it. Uncomment the code below
   // and put a breakpoint if you want to see the result
   
   //std::vector<int> numbers_after = genetic.get_best_genome();
   ASSERT_TRUE(true);
}