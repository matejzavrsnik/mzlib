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
