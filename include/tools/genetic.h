//
// Copyright (c) 2012 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_UTILS_GENETIC_H
#define	MZLIB_UTILS_GENETIC_H

#include "../greatest_hits/genetic_container.h"

namespace mzlib {

template <class TYPE>
TYPE mendel_until_perfect(genetic_base<TYPE>& genetic, double perfect_penalty)
{
   while (genetic.get_lowest_penalty() != perfect_penalty) {
      genetic.play_generations(1);
   }
   return genetic.get_best_genome();
}

template <class TYPE>
TYPE mendel_smart(genetic_base<TYPE>& genetic)
{
   TYPE best_genome_overall = genetic.get_best_genome();
   double lowest_penalty_overall = genetic.get_lowest_penalty();
   
   // settings
   const double penalty_improvement_threshold = 0.0001;
   const int allowed_generations_without_improvement = 1000;
   const int generations_in_one_loop = 100;
   const int generation_size = 100;
   const int survival_count = 20;
   const int max_mutation_rate = genetic.get_problem_space();
   const double lowest_possible_penalty = 0;
   
   // setup
   double current_penalty, previous_penalty, penalty_improvement;
   current_penalty = previous_penalty = genetic.get_lowest_penalty();
   int mutation_rate = 1;
   genetic.set_mutation_rate(mutation_rate);
   genetic.set_generation_size(generation_size);
   genetic.set_survivers_count(survival_count);
           
   // make eons fly-by, doubling the mutation rate as generations get "stale"
   while (mutation_rate < max_mutation_rate && lowest_penalty_overall > lowest_possible_penalty) {
      int passed_generations_without_improvement = 0;
      do {
         genetic.play_generations(generations_in_one_loop);
         current_penalty = genetic.get_lowest_penalty();
         penalty_improvement = (previous_penalty - current_penalty) / previous_penalty;
         if (penalty_improvement < penalty_improvement_threshold) {
            passed_generations_without_improvement += generations_in_one_loop;
         }
         else {
            mutation_rate = 1;
         }
         previous_penalty = current_penalty; 
      }
      while (passed_generations_without_improvement < allowed_generations_without_improvement);
      if (genetic.get_lowest_penalty() < lowest_penalty_overall) {
         best_genome_overall = genetic.get_best_genome();
         lowest_penalty_overall = genetic.get_lowest_penalty();
      }
      if (mutation_rate < max_mutation_rate) mutation_rate *= 2;
      if (mutation_rate > max_mutation_rate) mutation_rate = max_mutation_rate;
      genetic.set_mutation_rate(mutation_rate);
   }
   
   return best_genome_overall;
}

} // namespace

#endif	/* MZLIB_UTILS_GENETIC_H */
