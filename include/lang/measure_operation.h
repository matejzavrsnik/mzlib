//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_MEASURE_OPERATION_H
#define MZLIB_MEASURE_OPERATION_H

#include "stopwatch.h"
#include "../iterators/average.h"

namespace mzlib {

template<typename Function>
double run_and_measure(Function fun)
{
   mzlib::stopwatch stopwatch;
   auto start = stopwatch.start();

   fun();

   auto end = stopwatch.stop();
   return stopwatch.get_wall_clock(start, end);
}

template<typename Function>
double get_average_operation_time(Function fun, const size_t repetitions)
{
   std::vector<double> times;
   for (size_t reps=0; reps<repetitions; ++reps)
   {
      times.push_back(mzlib::run_and_measure(fun));
   }
   return mzlib::average(times.begin(), times.end());
}

} // namespaces

#endif /* MZLIB_MEASURE_OPERATION_H */

