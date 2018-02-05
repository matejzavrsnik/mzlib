//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "genetic.h"

// Delete DISABLED_ to see the function in action
TEST(genetic_tools, DISABLED_mendel_smart_demo) 
{
   std::vector<int> numbers(10);
   
   // setup a fitness function
   auto fitness_function = 
      [](const std::vector<int>& candidate) {
         // test criteria: each next number is 2x the previous
         double sum_difference = 0;
         for (size_t i = 0; i<candidate.size()-1; ++i) {
            // discourage trivial and incorrect solutions
            // fun fact: in int world, 2 * -2147483648 == 0 !!
            if (candidate[i] <= 0 || candidate[i] == -2147483648) {
               return std::numeric_limits<double>::max();
            }
            for (size_t j = i+1; j<candidate.size(); ++j) {
               int factor = std::pow(2, j-i);
               sum_difference += std::fabs(candidate[j] - (factor * candidate[i]));
            }
         }
         return sum_difference;
      };
      
   mzlib::genetic_container<std::vector<int>> genetic (numbers, fitness_function);
   
   double penalty_before = fitness_function(numbers);
   std::vector<int> numbers_after = mzlib::mendel_smart(genetic);
   double penalty_after = fitness_function(numbers_after);
   
   ASSERT_LT(penalty_before, penalty_after); // warning: probabilistic assert
}