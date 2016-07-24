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

namespace mzlib {

template<class TYPE>
class cgenetic
{
   
public:
    
   using ifitness_function = std::function<int(const TYPE& candidate)>;
    
   cgenetic (
      const TYPE& seed, 
      ifitness_function fitness_function, 
      uint generation_size)
   {
      // remember fitness function
      m_fitness_function = fitness_function;
      
      // create seed genome
      tgenome seed_genome;
      seed_genome.genome = seed;
      seed_genome.score = m_fitness_function(seed);
      
      // create initial population from seed genomw
      m_genome_pool.assign(generation_size, seed_genome);
   };
    
   ~cgenetic () {};

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
    
   int get_best_score () const
   {
      return m_genome_pool[0].score;
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
    
private:
    
   struct tgenome
   {
      TYPE genome;
      int score;
   };
    
   void mutate_generation()
   {
      // expected precondition: genome pool is already sorted by score and the
      // element at [0] is the best specimen in the population.
      
      // mutate whole population skipping the best one (so skip [0])
      for (size_t i=1; i<m_genome_pool.size(); ++i) {
         mutate_genome (m_genome_pool[i]);
      }
   }
    
   void mutate_genome (tgenome& genome)
   {
      size_t size_of_object = sizeof(TYPE);
      char* genome_pointer = reinterpret_cast<char*>(&genome.genome);
      
      for(int rate=0; rate<m_mutation_rate; ++rate)
      {  
         size_t zap_byte = mzlib::util::get_random_integer_between (0, size_of_object);
         size_t zap_bit = mzlib::util::get_random_integer_between (0, 8);
         genome_pointer[zap_byte] ^= (1 << zap_bit); // engage radiation beam!
         genome.score = m_fitness_function (genome.genome); // calculate new score
      }
   }
    
   void multiply_best_genomes()
   {
      std::sort(m_genome_pool.begin(), m_genome_pool.end(), 
         [](const tgenome& a, const tgenome& b) { 
            return a.score > b.score; 
         });
       
      // keep the first m_survivers_count, copy the best over the rest of the slots
      auto start = m_genome_pool.begin() + m_survivers_count;
      std::fill(start, m_genome_pool.end(), m_genome_pool[0]);
   }

   std::vector<tgenome> m_genome_pool;
   ifitness_function m_fitness_function;

   // settings
   uint m_mutation_rate = 1; // how many bits to mutate
   uint m_survivers_count = 1; // how many genomes should survive generation and multiply
};
   
} // namespace mzlib

#endif	/* GENETIC_H */

