//
// Copyright (c) 2012 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef GENETIC_H
#define	GENETIC_H

#include <vector>
#include <functional>
#include <algorithm> // std::sort
   
#include "utils_random.h"
#include "utilities.h"


namespace mzlib {
   
template<class TYPE>
class cgenetic
{
   
public:
   
   using ifitness_function = std::function<double(const TYPE& candidate)>;
   
   virtual ~cgenetic () {};
   
   void play_generations (int count)
   {
      for(int i=0; i<count; ++i)
      {
         mutate_generation();
         multiply_best_genomes();
      }
   }

   const TYPE& get_best_genome () const
   {
      return m_genome_pool[0].genome;
   }
    
   double get_lowest_penalty () const
   {
      return m_genome_pool[0].penalty;
   }
    
   void set_survivers_count (uint survivers_count)
   {
      m_survivers_count = survivers_count;
   }
    
   uint get_survivers_count () const
   {
      return m_survivers_count;
   }
    
   void set_mutation_rate (uint mutation_rate)
   {
      m_mutation_rate = mutation_rate;
   }
    
   uint get_mutation_rate () const
   {
      return m_mutation_rate;
   }
   
   void set_generation_size (size_t generation_size)
   {
      auto best = m_genome_pool[0];
      m_genome_pool.resize(generation_size);
      m_genome_pool.assign(generation_size, best);
   }
   
   size_t get_generation_size ()
   {
      return m_genome_pool.size();
   }
   
   virtual size_t get_problem_space () = 0;
   
protected:

   cgenetic (const TYPE& seed, ifitness_function fitness_function)
   {
      m_fitness_function = fitness_function;
      m_genome_pool.push_back({seed, m_fitness_function(seed)});
      set_generation_size(100);
   }
   
   struct tgenome
   {
      TYPE genome;
      double penalty;
   };

   struct tgenome_info 
   {
      size_t genome_size;
      char* genome_pointer;
   };

   virtual tgenome_info get_zap_info (tgenome&) = 0;
   
private:
   
   void mutate_generation()
   {
      // expected precondition: genome pool is already sorted by penalty and the
      // element at [0] is the best specimen in the population = least penalised
      
      // mutate whole population skipping the best one (so skip [0])
      for (size_t i=1; i<m_genome_pool.size(); ++i) {
         mutate_genome (m_genome_pool[i]);
      }
   }
   
   void mutate_genome (tgenome& genome)
   {
      for(int rate=0; rate<m_mutation_rate; ++rate)
      {
         tgenome_info genome_info = get_zap_info(genome);
         size_t zap_byte = mzlib::util::get_random_integer_between (0, genome_info.genome_size);
         size_t zap_bit = mzlib::util::get_random_integer_between (0, 8);
         genome_info.genome_pointer[zap_byte] ^= (1 << zap_bit); // engage radiation beam!
         genome.penalty = m_fitness_function (genome.genome); // calculate new penalty
      }
   }
    
   void multiply_best_genomes()
   {
      std::sort(m_genome_pool.begin(), m_genome_pool.end(), 
         [](const tgenome& a, const tgenome& b) { 
            // advance one that is less penalised
            return a.penalty < b.penalty; 
         });
       
      // keep the first m_survivors_count, copy the best over the rest of the slots
      mzlib::util::copy_first_n_over_rest(m_genome_pool, m_survivers_count);
   }

   std::vector<tgenome> m_genome_pool;
   uint m_mutation_rate = 1; // how many bits to mutate
   uint m_survivers_count = 1; // how many genomes should survive generation and multiply
   ifitness_function m_fitness_function;
   
};
  
// This one works on single object, like a number, or struct, or whatever.
template<class TYPE>
class cgenetic_object : public cgenetic<TYPE>
{
   
   using typename cgenetic<TYPE>::ifitness_function;
   using typename cgenetic<TYPE>::tgenome;
   using typename cgenetic<TYPE>::tgenome_info; 
   
public:
   
   cgenetic_object (const TYPE& seed, ifitness_function fitness_function) :
      cgenetic<TYPE> (seed, fitness_function)
   {
   };
   
   ~cgenetic_object () {};
   
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

// This one works on containers. It will randomly select an object from it and 
// change genome on objects that can be accessed using operator[]
template<class TYPE>
class cgenetic_container : public cgenetic<TYPE>
{
   
   using typename cgenetic<TYPE>::ifitness_function;
   using typename cgenetic<TYPE>::tgenome;
   using typename cgenetic<TYPE>::tgenome_info;
   
public:
   
   cgenetic_container (const TYPE& seed, ifitness_function fitness_function) :
      cgenetic<TYPE> (seed, fitness_function)
   {
      m_object_size = sizeof(typename TYPE::value_type);
      m_object_count = seed.size();
   };
   
   virtual ~cgenetic_container () {};
   
   virtual size_t get_problem_space () override 
   {
      return m_object_size * m_object_count;
   }
   
private:

   virtual tgenome_info get_zap_info (tgenome& genome) override 
   {
      tgenome_info info;
      size_t zap_object = mzlib::util::get_random_integer_between (0, m_object_count);
      info.genome_size = m_object_size;
      info.genome_pointer = reinterpret_cast<char*>(&genome.genome[zap_object]);;
      return info;
   }
   
   size_t m_object_size;
   size_t m_object_count;
   
};
   
template <class TYPE>
TYPE mendel_until_perfect(cgenetic<TYPE>& genetic, double perfect_penalty)
{
   while (genetic.get_lowest_penalty() != perfect_penalty) {
      genetic.play_generations(1);
   }
   return genetic.get_best_genome();
}

template <class TYPE>
TYPE mendel_smart(cgenetic<TYPE>& genetic)
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

} // namespace mzlib

#endif	/* GENETIC_H */

