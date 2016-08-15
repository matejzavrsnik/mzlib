//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include <iostream>

#include "../include/universe.h"
#include "../include/units.h"
#include "../include/utils_random.h"
#include "../include/stopwatch.h"

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
   
   void RunSimulation(mzlib::cuniverse& local_universe)
   {
      local_universe.forward_time(10,1);
   }
   
};

TEST_F(fixture_universe_performance, proper)
{
   // uncomment stuff here to do actual tests
   //std::cout << "bodies\t\tbar0.0\t\tbar0.25\t\tbar0.5\t\tbar0.75\t\tbar1.0\t\tvector" << std::endl;
   for(int bodies_count : {2, 4, /*8, 16, 32, 64, 128, 256, 512, 1024, 2000, 4000, 8000*/})
   {
      // sets of bodies, equal number, equal positions
      auto bodies_control = generate_bodies (bodies_count);
      auto bodies_barnes0 = bodies_control;
      auto bodies_barnes1 = bodies_control;
      auto bodies_barnes2 = bodies_control;
      auto bodies_barnes3 = bodies_control;
      auto bodies_barnes4 = bodies_control;
      auto bodies_vector = bodies_control;

      mzlib::util::cstopwatch stopwatch;

      // naive
      auto universe_vector = prepare_the_universe(bodies_vector, mzlib::cuniverse::implementation::naive);
      auto start_naive = stopwatch.start();
      if(bodies_count<=15000) {
         RunSimulation(universe_vector);
      }
      auto end_naive = stopwatch.mark();
      
      // barnes-hut 0
      auto universe_barnes_0 = prepare_the_universe(bodies_barnes0, mzlib::cuniverse::implementation::barnes_hut, 0);
      auto start_barnes_0 = stopwatch.mark();
      if(bodies_count<=15000) {
         RunSimulation(universe_barnes_0);
      }
      auto end_barnes_0 = stopwatch.mark();
      
      // barnes-hut 1
      auto universe_barnes_1 = prepare_the_universe(bodies_barnes1, mzlib::cuniverse::implementation::barnes_hut, 0.25);
      auto start_barnes_1 = stopwatch.mark();
      if(bodies_count<=15000) {
         RunSimulation(universe_barnes_1);
      }
      auto end_barnes_1 = stopwatch.mark();
      
      // barnes-hut 2
      auto universe_barnes_2 = prepare_the_universe(bodies_barnes2, mzlib::cuniverse::implementation::barnes_hut, 0.5);
      auto start_barnes_2 = stopwatch.mark();
      if(bodies_count<=15000) {
         RunSimulation(universe_barnes_2);
      }
      auto end_barnes_2 = stopwatch.mark();
      
      // barnes-hut 3
      auto universe_barnes_3 = prepare_the_universe(bodies_barnes3, mzlib::cuniverse::implementation::barnes_hut, 0.75);
      auto start_barnes_3 = stopwatch.mark();
      if(bodies_count<=15000) {
         RunSimulation(universe_barnes_3);
      }
      auto end_barnes_3 = stopwatch.mark();

      // barnes-hut 4
      auto universe_barnes_4 = prepare_the_universe(bodies_barnes4, mzlib::cuniverse::implementation::barnes_hut, 1.0);
      auto start_barnes_4 = stopwatch.mark();
      if(bodies_count<=15000) {
         RunSimulation(universe_barnes_4);
      }
      auto end_barnes_4 = stopwatch.mark();
      
      // neatly aligned output
      //std::cout << std::fixed << std::setprecision(0)
      //   << bodies_count << "\t\t" 
      //   << stopwatch.get_wall_clock(start_barnes_0, end_barnes_0) << "\t\t" 
      //   << stopwatch.get_wall_clock(start_barnes_1, end_barnes_1) << "\t\t" 
      //   << stopwatch.get_wall_clock(start_barnes_2, end_barnes_2) << "\t\t" 
      //   << stopwatch.get_wall_clock(start_barnes_3, end_barnes_3) << "\t\t" 
      //   << stopwatch.get_wall_clock(start_barnes_4, end_barnes_4) << "\t\t" 
      //   << stopwatch.get_wall_clock(start_naive, end_naive) << "\t\t"
      //   << std::endl;
   }
   ASSERT_TRUE(true);
}

