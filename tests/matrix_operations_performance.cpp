//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "../include/laws/matrix_operations.h"
#include "../include/nature/matrix.h"
#include "../include/lang/stopwatch.h"
#include "../include/iterators/average.h"

#include <thread>
#include <numeric>
#include <algorithm>

#include "gtest/gtest.h"

namespace 
{
   template<typename Function>
   double run_and_measure2(Function fun)
   {
      mzlib::stopwatch stopwatch;
      auto start = stopwatch.start();
      
      fun();
      
      auto end = stopwatch.stop();
      return stopwatch.get_wall_clock(start, end);
   }
   
   template<size_t N, size_t M>
   void run_and_measure_matrix_multiply()
   {
      auto m1 = std::make_shared<mzlib::matrix<double, N, M>>();
      auto m2 = std::make_shared<mzlib::matrix<double, N, M>>();

      mzlib::law::matrix::randomise(*m1);
      mzlib::law::matrix::randomise(*m2);

      std::vector<double> times;
      for (int reps=0; reps<10; ++reps)
      {
         times.push_back( 
            run_and_measure2([&](){
                  return mzlib::law::matrix::multiply(*m1, *m2); }));
      }

      double avg_time_to_complete = mzlib::average(times.begin(), times.end());

      // neatly aligned output
      std::cout << std::fixed << std::setprecision(0)
         << N << "x" << M << "\t" 
         << avg_time_to_complete << "\t"
         << std::endl;
   }
}

TEST(matrix_multiplication_performance, DISABLED_perform)
{
   std::cout << "N*M\tms\t" << std::endl;
   
   run_and_measure_matrix_multiply<100, 100>();
   run_and_measure_matrix_multiply<200, 200>();
   run_and_measure_matrix_multiply<400, 400>();
   run_and_measure_matrix_multiply<800, 800>();
   run_and_measure_matrix_multiply<1600, 1600>();
   
   // N*M        ms
   // 100x100    1
   // 200x200    7
   // 400x400    52
   // 800x800    2035
   // 1600x1600  19873
   
   ASSERT_TRUE(true);
}
