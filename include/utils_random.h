//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_UTILS_RANDOM_H
#define MZLIB_UTILS_RANDOM_H

#include <map>
#include <chrono>
#include <random>

namespace mzlib {
namespace util {
    
inline unsigned int get_random_integer ()
{
   static unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
   static std::mt19937 generator(seed);
   return generator();
}
    
inline double get_random_double_between_0_1 ()
{
   unsigned random_number = get_random_integer();
   return (double)random_number / (double)std::mt19937::max();
}

inline double get_random_double ()
{
   // rand() will never return completely random type T when T is a floating point type, 
   // because the integer value will be converted to a floating point value with all 
   // decimal digits 0, I invented the following trick.

   // cast to double immediately to make sure the division will be cast properly
   double numerator = get_random_integer();
   double denominator = get_random_integer();
   // collect some decimal digits
   double decimals = numerator / denominator;
   // collect whole digits too
   double final_rand = get_random_integer() + decimals;
   return final_rand;
}
    
inline unsigned int get_random_integer_between (unsigned from, unsigned to)
{
   double random_number = get_random_double_between_0_1();
   return (random_number * (to - from) + from);
}
    
template<class T, class U> typename std::map<T,U>::iterator 
get_random_element (std::map<T,U>& from_map) 
{
   unsigned random = get_random_integer_between(0, from_map.size()-1);
   auto result = from_map.begin();
   std::advance(result, random);
   return result;
}

} } // namespace mzlib::util

#endif /* MZLIB_UTILS_RANDOM_H */

