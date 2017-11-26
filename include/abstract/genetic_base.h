//
// Copyright (c) 2012 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_GENETIC_BASE_H
#define	MZLIB_GENETIC_BASE_H

#include "../tools/random.h"
#include "../tools/copy_first_n_over_rest.h"
#include <functional>
#include <algorithm> // std::sort

namespace mzlib {
   
template<class TYPE>
class genetic_base
{
   
public:
   
   using ifitness_function = std::function<double(const TYPE& candidate)>;
   
   virtual ~genetic_base () {};
   
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

   genetic_base (const TYPE& seed, ifitness_function fitness_function)
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
      for(unsigned rate=0; rate<m_mutation_rate; ++rate)
      {
         tgenome_info genome_info = get_zap_info(genome);
         size_t zap_byte = get_random_integer_between (0, genome_info.genome_size);
         size_t zap_bit = get_random_integer_between (0, 8);
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
      copy_first_n_over_rest(m_genome_pool, m_survivers_count);
   }

   std::vector<tgenome> m_genome_pool;
   uint m_mutation_rate = 1; // how many bits to mutate
   uint m_survivers_count = 1; // how many genomes should survive generation and multiply
   ifitness_function m_fitness_function;
   
};

} // namespace

#endif	/* MZLIB_GENETIC_BASE_H */

#ifdef MZLIB_GENETIC_BASE_TESTS_H
#undef MZLIB_GENETIC_BASE_TESTS_H



#endif