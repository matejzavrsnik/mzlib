//
// I am not really and author of this, apart from cosmetics.
// Code heavily influenced by: http://stackoverflow.com/a/13772771
//

#ifndef CPUCYCLE_H
#define	CPUCYCLE_H

#include <stdint.h>

namespace mzlib {
namespace util {    

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

} } // namespaces

#endif // CPUCYCLE_H

