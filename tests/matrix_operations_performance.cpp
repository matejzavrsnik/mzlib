//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "../include/laws/matrix_operations.h"
#include "../include/nature/matrix.h"
#include "../include/lang/measure_operation.h"
#include "../include/lang/out_operators_time.h"

#include <thread>
#include <numeric>
#include <algorithm>

#include "gtest/gtest.h"

namespace 
{
   template<typename T, size_t N, size_t M>
   auto make_random_matrix()
   {
      auto m = std::make_shared<mzlib::matrix<T, N, M>>();      
      mzlib::law::matrix::randomise(*m);
      return m;
   }

   void display_header()
   {
      std::cout << "NxM\t\tms\t" << std::endl;
   }
   
   void display_results(int n, int m, std::chrono::nanoseconds avg)
   {
      std::cout << std::fixed << std::setprecision(0)
         << n << "x" << m << "\t\t" 
         << avg << "\t"
         << std::endl;
   }
   
   template<size_t N, size_t M>
   std::chrono::nanoseconds run_and_measure_matrix_multiply()
   {
      auto m1 = make_random_matrix<double, N, M>();
      auto m2 = make_random_matrix<double, N, M>();

      return mzlib::get_average_operation_time(
         [&](){
            return mzlib::law::matrix::multiply(*m1, *m2); 
         },
         10
      );
   }
   
   template<size_t N, size_t M>
   std::chrono::nanoseconds run_and_measure_matrix_add()
   {
      auto m1 = make_random_matrix<double, N, M>();
      auto m2 = make_random_matrix<double, N, M>();

      return mzlib::get_average_operation_time(
         [&](){
            return mzlib::law::matrix::add(*m1, *m2); 
         },
         10
      );
   }
}

TEST(matrix_performance, DISABLED_multiply)
{
   display_header();
   std::chrono::nanoseconds result;
   
   result = run_and_measure_matrix_multiply<100, 100>();
   display_results(100, 100, result);
   
   result = run_and_measure_matrix_multiply<200, 200>();
   display_results(200, 200, result);
   
   result = run_and_measure_matrix_multiply<400, 400>();
   display_results(400, 400, result);
   
   result = run_and_measure_matrix_multiply<800, 800>();
   display_results(800, 800, result);

   result = run_and_measure_matrix_multiply<1600, 1600>();
   display_results(1600, 1600, result);
   
//   NxM             ms
//   100x100         0
//   200x200         6
//   400x400         51
//   800x800         909
//   1600x1600       7070
   
   ASSERT_TRUE(true);
}

TEST(matrix_performance, DISABLED_add)
{
   display_header();
   std::chrono::nanoseconds result;
   
   result = run_and_measure_matrix_add<100, 100>();
   display_results(100, 100, result);
   
   result = run_and_measure_matrix_add<200, 200>();
   display_results(200, 200, result);
   
   result = run_and_measure_matrix_add<400, 400>();
   display_results(400, 400, result);
   
   result = run_and_measure_matrix_add<800, 800>();
   display_results(800, 800, result);

   result = run_and_measure_matrix_add<1600, 1600>();
   display_results(1600, 1600, result);

   result = run_and_measure_matrix_add<3200, 3200>();
   display_results(3200, 3200, result);

   result = run_and_measure_matrix_add<6400, 6400>();
   display_results(6400, 6400, result);
   
   result = run_and_measure_matrix_add<12800, 12800>();
   display_results(12800, 12800, result);
   
//   NxM             ms
//   100x100         0
//   200x200         0
//   400x400         0
//   800x800         2
//   1600x1600       8
//   3200x3200       44
//   6400x6400       272
//   12800x12800     1201
   
   ASSERT_TRUE(true);
}
