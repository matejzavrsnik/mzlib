//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_UTILS_RANDOM_H
#define MZLIB_UTILS_RANDOM_H

#include <chrono>
#include <random>
#include <type_traits>

namespace mzlib {

inline std::mt19937& get_generator()
{
   static auto seed = 
      std::chrono
         ::high_resolution_clock::now()
         .time_since_epoch()
         .count();
   
   static std::mt19937 generator(static_cast<unsigned long>(seed));
   
   return generator;
}
   
template<typename T>
T get_random ()
{
   if constexpr (std::is_integral<T>::value)
   {
      std::mt19937& gen = get_generator();
      return static_cast<T>(gen());
   }
   else
   {
      // rand() will never return completely random type T when T is a floating point type, 
      // because the integer value will be converted to a floating point value with all 
      // decimal digits 0, I invented the following trick.

      // cast to double immediately to make sure the division will be cast properly
      double numerator = get_random<unsigned>();
      double denominator = get_random<unsigned>();
      // collect some decimal digits
      double decimals = numerator / denominator;
      // collect whole digits too
      double final_rand = get_random<unsigned>() + decimals;
      return final_rand;
   }
   
}

inline double get_random_between_0_1 ()
{
   unsigned random_number = get_random<unsigned>();
   return static_cast<double>(random_number) / static_cast<double>(std::mt19937::max());
}
 
template<typename T>
inline T get_random_between (T from, T to)
{
   const double random_number = get_random_between_0_1();
   return static_cast<T>(random_number * static_cast<double>(to - from) + static_cast<double>(from));
}

} // namespace

#endif // MZLIB_UTILS_RANDOM_H
