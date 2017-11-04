//
// Copyright (c) 2012 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_GENETIC_OBJECT_H
#define	MZLIB_GENETIC_OBJECT_H

#include "genetic_base.h"

namespace mzlib {
  
// This one works on single object, like a number, or struct, or whatever.
template<class TYPE>
class genetic_object : public genetic_base<TYPE>
{
   
   using typename genetic_base<TYPE>::ifitness_function;
   using typename genetic_base<TYPE>::tgenome;
   using typename genetic_base<TYPE>::tgenome_info; 
   
public:
   
   genetic_object (const TYPE& seed, ifitness_function fitness_function) :
      genetic_base<TYPE> (seed, fitness_function)
   {
   };
   
   ~genetic_object () {};
   
   virtual size_t get_problem_space () override 
   {
      return sizeof(TYPE);
   }
    
private:
   
   virtual tgenome_info get_zap_info (tgenome& genome) override 
   {
      tgenome_info info;
      info.genome_size = sizeof(TYPE);
      info.genome_pointer = reinterpret_cast<char*>(&genome.genome);;
      return info;
   }
    
};

} // namespace

#endif	/* MZLIB_GENETIC_OBJECT_H */

#ifdef MZLIB_GENETIC_OBJECT_TESTS_H
#undef MZLIB_GENETIC_OBJECT_TESTS_H

TEST(genetic_object, demo) 
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
      
   mzlib::genetic_object<int> genetic(a_number, fitness_function);

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

#endif // MZLIB_GENETIC_OBJECT_TESTS_H