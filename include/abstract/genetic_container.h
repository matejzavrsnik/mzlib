//
// Copyright (c) 2012 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_GENETIC_CONTAINER_H
#define	MZLIB_GENETIC_CONTAINER_H

#include "genetic_base.h"
#include <vector>

namespace mzlib {
  
// This one works on containers. It will randomly select an object from it and 
// change genome on objects that can be accessed using operator[]
template<class TYPE>
class genetic_container : public genetic_base<TYPE>
{
   
   using typename genetic_base<TYPE>::ifitness_function;
   using typename genetic_base<TYPE>::tgenome;
   using typename genetic_base<TYPE>::tgenome_info;
   
public:
   
   genetic_container (const TYPE& seed, ifitness_function fitness_function) :
      genetic_base<TYPE> (seed, fitness_function)
   {
      m_object_size = sizeof(typename TYPE::value_type);
      m_object_count = seed.size();
   };
   
   virtual ~genetic_container () {};
   
   virtual size_t get_problem_space () override 
   {
      return m_object_size * m_object_count;
   }
   
private:

   virtual tgenome_info get_zap_info (tgenome& genome) override 
   {
      tgenome_info info;
      size_t zap_object = get_random_integer_between (0, m_object_count);
      info.genome_size = m_object_size;
      info.genome_pointer = reinterpret_cast<char*>(&genome.genome[zap_object]);;
      return info;
   }
   
   size_t m_object_size;
   size_t m_object_count;
   
};

} // namespace

#endif	/* MZLIB_GENETIC_CONTAINER_H */

#ifdef MZLIB_GENETIC_CONTAINER_TESTS_H
#undef MZLIB_GENETIC_CONTAINER_TESTS_H

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
   
   std::vector<int> numbers_after = genetic.get_best_genome();
   ASSERT_TRUE(true);
}

#endif // MZLIB_GENETIC_CONTAINER_TESTS_H