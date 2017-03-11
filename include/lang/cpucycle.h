//
// Code heavily influenced by: http://stackoverflow.com/a/13772771
//
// Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_CPUCYCLE_H
#define	MZLIB_CPUCYCLE_H

#include <stdint.h>

namespace mzlib { 

//  Windows
#ifdef _WIN32

#include <intrin.h>
uint64_t cycle_count()
{
   return __rdtsc();
}

//  Linux/GCC
#else

uint64_t cycle_count()
{
   unsigned int lo,hi;
   __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
   return ((uint64_t)hi << 32) | lo;
}

#endif

} // namespace

#endif /* MZLIB_CPUCYCLE_H */

