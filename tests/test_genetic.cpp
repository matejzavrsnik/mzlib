//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "../include/genetic.h"
#include "gtest/gtest.h"

#include "../include/utils_random.h"
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

TEST_F(fixture_genetic, demo_test) 
{
   // start with a biggest number
   int a_number = 0b1111111111; // 10 bit switches to 0
   
   // setup a fitness function
   mzlib::cgenetic<int>::ifitness_function fitness_function = 
      [](const int& candidate) {
         // test criteria: the closer to zero the better
         // how algorithm works: the higher the score the better
         return std::numeric_limits<int>::max() - std::abs(candidate);
      };
      
   mzlib::cgenetic<int> genetic(a_number, fitness_function, 100);

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
