//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "../include/genetic.h"
#include "gtest/gtest.h"

#include "../include/utils_random.h"
#include "../include/utilities.h"
#include <cmath>
#include <limits>

class fixture_genetic : public ::testing::Test 
{

protected:
   
   fixture_genetic () {}
   virtual ~fixture_genetic () {}
   virtual void SetUp() {}
   virtual void TearDown() {}
   
};

TEST_F(fixture_genetic, works_on_objects) 
{
   // start with a big number
   int a_number = 0b1111111111; // 10 bit switches to 0
   
   // setup a fitness function
   auto fitness_function = 
      [](const int& candidate) {
         // test criteria: the closer to zero the better
         // how algorithm works: the lower the penalty the better
         return std::fabs(candidate);
      };
      
   mzlib::cgenetic_object<int> genetic(a_number, fitness_function);

   // explanation of a test:
   // if one bit will be changed on every generation, and with 100 population and
   // 32 bits in integer, there is a big probability that at least one number will
   // be smaller than in previous generation. This is something I can quite reliably
   // test at least for first couple of generations without making test too fragile.
   
   genetic.play_generations(1);
   int best_in_generation_1 = genetic.get_best_genome();
   ASSERT_LT(best_in_generation_1, a_number);
   
   genetic.play_generations(1);
   int best_in_generation_2 = genetic.get_best_genome();
   ASSERT_LT(best_in_generation_2, best_in_generation_1);
   
   genetic.play_generations(1);
   int best_in_generation_3 = genetic.get_best_genome();
   ASSERT_LT(best_in_generation_3, best_in_generation_2);
   
   // And finally, under given circumstances, there is no probable reason why the evolution 
   // couldn't produce zero in 10 generations. Give it 100 generations, expect 0.
   
   genetic.play_generations(100);
   ASSERT_EQ(0, genetic.get_best_genome());
}

TEST_F(fixture_genetic, works_on_vector) 
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
      
   mzlib::cgenetic_container<std::vector<int>> genetic (numbers, fitness_function);
   
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
   //ASSERT_TRUE(true);
}

// Delete DISABLED_ to see the function in action
TEST_F(fixture_genetic, DISABLED_mendel_smart_demo) 
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
      
   mzlib::cgenetic_container<std::vector<int>> genetic (numbers, fitness_function);
   
   double penalty_before = fitness_function(numbers);
   std::vector<int> numbers_after = mzlib::mendel_smart(genetic);
   double penalty_after = fitness_function(numbers_after);
   
   ASSERT_LT(penalty_before, penalty_after); // warning: probabilistic assert
}
