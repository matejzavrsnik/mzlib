//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include <iostream>
#include <thread>
#include <future>

#include "../include/universe.h"
#include "../include/units.h"
#include "../include/utils_random.h"
#include "../include/stopwatch.h"
#include "../include/utilities.h"

#include "gtest/gtest.h"

using namespace mzlib::units;

// To test the performance of universe.
// The code is unlikely to be used often, but since it is written I'll let it stay.
// Perhaps I'll need it again if I do any massive changes to the code.
// Note: I know google test has parameterised tests, but those do not output
// detailed information.

class fixture_universe_performance : public ::testing::Test 
{

protected:
   
   fixture_universe_performance() {}
   virtual ~fixture_universe_performance() {}
   
   virtual void SetUp()  {}
   virtual void TearDown() {}

   std::vector<mzlib::cbody2d> generate_bodies (unsigned int num_of_bodies)
   {
      std::vector<mzlib::cbody2d> bodies;
      // Numbers here selected so that there is the right amount of movement.
      // Too little would not test the universe in dynamic situations.
      // Too much would just scatter bodies out of reach of quadtree.
      for(unsigned int i=0; i<num_of_bodies; ++i) {
         mzlib::cbody2d object;
         object.mass = 1000000000000;
         object.location = mzlib::math::cvector2d {
            (double)mzlib::util::get_random_integer_between(0,5000),
            (double)mzlib::util::get_random_integer_between(0,5000)
         };
         object.data.velocity = mzlib::math::cvector2d {
            (double)mzlib::util::get_random_integer_between(0,6)-3,
            (double)mzlib::util::get_random_integer_between(0,6)-3
         };
         bodies.push_back(object);
      }
      return bodies;
   }
   
   mzlib::cuniverse prepare_the_universe(
      std::vector<mzlib::cbody2d> bodies, 
      mzlib::cuniverse::implementation implementation,
      double barnes_hut_quotient = 0)
   {
      mzlib::cuniverse local_universe(
         mzlib::math::cvector2d{0,0}, 
         mzlib::math::cvector2d{5000,5000}, 
         50);
      mzlib::cuniverse::tproperties properties;
      properties.m_barnes_hut_quotient = barnes_hut_quotient;
      properties.m_implementation = implementation;
      local_universe.set_properties(properties);

      for(auto& body : bodies) {
         local_universe.add_body(body);
      }
      
      return std::move(local_universe);
   }
   
   double run_simulation(mzlib::cuniverse local_universe)
   {
      mzlib::util::cstopwatch stopwatch;
      auto start = stopwatch.start();
      local_universe.forward_time(1,1);
      auto end = stopwatch.stop();
      return stopwatch.get_wall_clock(start, end);
   }
   
   double run_simulation_async(mzlib::cuniverse& universe, std::chrono::milliseconds timeout)
   {
      auto fut = std::async(std::launch::async,&fixture_universe_performance::run_simulation, this, std::move(universe));
      auto duration = timeout.count();
      if(fut.wait_for(timeout) != std::future_status::timeout) {
         duration = fut.get();
      }
      return duration;
   }
   
};

TEST_F(fixture_universe_performance, DISABLED_perform)
{
   std::cout << "bodies\t\tbar0.0\t\tbar0.25\t\tbar0.5\t\tbar0.75\t\tbar1.0\t\tvector" << std::endl;
   for (int bodies_count : mzlib::util::cbasic_style_for<int>::
            loop()->from(0)->to(10000)->step(100))
   {
      // sets of bodies, equal number, equal positions
      auto bodies_control = generate_bodies (bodies_count);
      auto bodies_barnes0 = bodies_control;
      auto bodies_barnes1 = bodies_control;
      auto bodies_barnes2 = bodies_control;
      auto bodies_barnes3 = bodies_control;
      auto bodies_barnes4 = bodies_control;
      auto bodies_vector = bodies_control;

      std::chrono::milliseconds timeout (50000);

      // naive
      auto universe_vector = prepare_the_universe(bodies_vector, mzlib::cuniverse::implementation::naive);
      auto duration_naive = run_simulation_async(universe_vector, timeout);
      
      // barnes-hut, theta=0      
      auto universe_barnes_0 = prepare_the_universe(bodies_barnes0, mzlib::cuniverse::implementation::barnes_hut, 0);
      double duration_barnes_0 = run_simulation_async(universe_barnes_0, timeout);
      
      // barnes-hut, theta=0.25
      auto universe_barnes_1 = prepare_the_universe(bodies_barnes1, mzlib::cuniverse::implementation::barnes_hut, 0.25);
      auto duration_barnes_1 = run_simulation_async(universe_barnes_1, timeout);
      
      // barnes-hut, theta=0.5
      auto universe_barnes_2 = prepare_the_universe(bodies_barnes2, mzlib::cuniverse::implementation::barnes_hut, 0.5);
      auto duration_barnes_2 = run_simulation_async(universe_barnes_2, timeout);
      
      // barnes-hut, theta=0.75
      auto universe_barnes_3 = prepare_the_universe(bodies_barnes3, mzlib::cuniverse::implementation::barnes_hut, 0.75);
      auto duration_barnes_3 = run_simulation_async(universe_barnes_3, timeout);

      // barnes-hut, theta=1
      auto universe_barnes_4 = prepare_the_universe(bodies_barnes4, mzlib::cuniverse::implementation::barnes_hut, 1.0);
      auto duration_barnes_4 = run_simulation_async(universe_barnes_4, timeout);
      
      // neatly aligned output
      std::cout << std::fixed << std::setprecision(0)
         << bodies_count << "\t\t" 
         << duration_barnes_0 << "\t\t" 
         << duration_barnes_1 << "\t\t" 
         << duration_barnes_2 << "\t\t" 
         << duration_barnes_3 << "\t\t" 
         << duration_barnes_4 << "\t\t" 
         << duration_naive << "\t\t"
         << std::endl;
      
      // cool down CPU a bit
      std::this_thread::sleep_for(std::chrono::seconds(60));
   }
   ASSERT_TRUE(true);
}

