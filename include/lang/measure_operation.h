//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_MEASURE_OPERATION_H
#define MZLIB_MEASURE_OPERATION_H

#include "stopwatch.h"

#include <algorithm> // std::max_element

namespace mzlib {
   
template<typename Function>
std::chrono::nanoseconds run_and_measure(Function fun)
{
   mzlib::stopwatch stopwatch;
   auto start = stopwatch.start();

   fun();

   auto end = stopwatch.stop();
   return stopwatch.get_wall_clock(start, end);
}

template<typename Function>
std::chrono::nanoseconds get_average_operation_time(Function fun, const size_t repetitions)
{
   // learn how long it takes for the loop itself
   auto loop_duration = mzlib::run_and_measure([&](){
      for (volatile size_t reps=0; reps<repetitions; ++reps) {}
   });
   
   // measure
   
   auto all_duration = mzlib::run_and_measure([&](){
      for (size_t reps=0; reps<repetitions; ++reps)
      {
         fun();
      }
   });
   
   auto fun_duration = all_duration - loop_duration;
   
   return fun_duration / repetitions;
}

template<typename Function>
std::chrono::nanoseconds get_maximum_operation_time(Function fun, const size_t repetitions)
{
   std::vector<std::chrono::nanoseconds> times;
   for (size_t reps=0; reps<repetitions; ++reps)
   {
      times.push_back( 
         mzlib::run_and_measure([&](){
            fun();
         })
      );
   }

   return *std::max_element(
      times.begin(), times.end());
}

} // namespaces

#endif /* MZLIB_MEASURE_OPERATION_H */

