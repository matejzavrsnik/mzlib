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
      size_t zap_object = get_random_between<size_t> (0, m_object_count);
      info.genome_size = m_object_size;
      info.genome_pointer = reinterpret_cast<char*>(&genome.genome[zap_object]);;
      return info;
   }
   
   size_t m_object_size;
   size_t m_object_count;
   
};

} // namespace

#endif	/* MZLIB_GENETIC_CONTAINER_H */
