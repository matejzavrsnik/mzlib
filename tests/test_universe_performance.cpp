//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "../include/universe.h"
#include "../include/units.h"
#include "../include/utils_random.h"
#include "gtest/gtest.h"

using namespace mzlib::units;

// To test the performance of universe.
// The code is unlikely to be used often, but since it is written I'll let it stay.
// Perhaps I'll need it again if I do any massive changes to the code.
// Note: I know google test has parameterised tests, but those do not output
// detailed information. Sample below.

class fixture_universe_performance : public ::testing::Test 
{

protected:
   
   fixture_universe_performance() :
      local_universe(
         mzlib::math::cvector2d{0,0}, 
         mzlib::math::cvector2d{5000,5000}, 
         50)
   {}
   virtual ~fixture_universe_performance() {}
   
   virtual void SetUp() 
   {
   }
   
   virtual void TearDown() {}

   mzlib::cuniverse local_universe;

   void PrepareTheUniverse(
      int num_of_bodies, 
      mzlib::cuniverse::implementation implementation,
      double barnes_hut_quotient = 0)
   {
      mzlib::cuniverse::tproperties properties;
      properties.m_barnes_hut_quotient = barnes_hut_quotient;
      properties.m_implementation = implementation;
      local_universe.set_properties(properties);

      // Numbers here selected so that there is the right amount of movement.
      // Too little would not test the universe in dynamic situations.
      // Too much would just scatter bodies out of reach of quadtree.
      for(int i=0; i<num_of_bodies; ++i) {
         mzlib::cbody2d object;
         object.mass = 1000000000000;
         object.location = mzlib::math::cvector2d{
            mzlib::util::get_random_integer_between(0,5000),
            mzlib::util::get_random_integer_between(0,5000)
         };
         object.data.velocity = mzlib::math::cvector2d{
            mzlib::util::get_random_integer_between(0,6)-3,
            mzlib::util::get_random_integer_between(0,6)-3
         };
         local_universe.add_body(object);
      }
   }
   
   void RunSimulation()
   {
      local_universe.forward_time(1000,1);
   }
   
};

/*

Parameterised version of these tests don't display enough information.
Sample of output below.

INSTANTIATE_TEST_CASE_P(TestVector, fixture_universe_performance,
   ::testing::Combine(
      ::testing::Values(3,5),
      ::testing::Values(mzlib::cuniverse::implementation::naive),
      ::testing::Values(0.0))
);

INSTANTIATE_TEST_CASE_P(TestBarnesHut, fixture_universe_performance,
   ::testing::Combine(
      ::testing::Values(3,5),
      ::testing::Values(mzlib::cuniverse::implementation::barnes_hut),
      ::testing::Values(0.0,1.0,2.0,3.0))
);


TEST_P(fixture_universe_performance, all)
{
   PrepareTheUniverse(
      std::get<0>(GetParam()),
      std::get<1>(GetParam()),
      std::get<2>(GetParam()));
   RunSimulation();
   // nothing to assert, because it is used as performance test
}

 [----------] 8 tests from TestBarnesHut/fixture_universe_performance
 [ RUN      ] TestBarnesHut/fixture_universe_performance.all/0
 [       OK ] TestBarnesHut/fixture_universe_performance.all/0 (14 ms)
 [ RUN      ] TestBarnesHut/fixture_universe_performance.all/1
 [       OK ] TestBarnesHut/fixture_universe_performance.all/1 (27 ms)
 [ RUN      ] TestBarnesHut/fixture_universe_performance.all/2
 [       OK ] TestBarnesHut/fixture_universe_performance.all/2 (3 ms)
 [ RUN      ] TestBarnesHut/fixture_universe_performance.all/3
 [       OK ] TestBarnesHut/fixture_universe_performance.all/3 (4 ms)
 [ RUN      ] TestBarnesHut/fixture_universe_performance.all/4
 [       OK ] TestBarnesHut/fixture_universe_performance.all/4 (3 ms)
 [ RUN      ] TestBarnesHut/fixture_universe_performance.all/5
 [       OK ] TestBarnesHut/fixture_universe_performance.all/5 (21 ms)
 [ RUN      ] TestBarnesHut/fixture_universe_performance.all/6
 [       OK ] TestBarnesHut/fixture_universe_performance.all/6 (3 ms)
 [ RUN      ] TestBarnesHut/fixture_universe_performance.all/7
 [       OK ] TestBarnesHut/fixture_universe_performance.all/7 (27 ms)
 [----------] 8 tests from TestBarnesHut/fixture_universe_performance (103 ms total)
*/


TEST_F(fixture_universe_performance, vector_3_objects)
{
   PrepareTheUniverse(3, mzlib::cuniverse::implementation::naive);
   RunSimulation();
}

TEST_F(fixture_universe_performance, vector_5_objects)
{
   PrepareTheUniverse(5, mzlib::cuniverse::implementation::naive);
   RunSimulation();
}

TEST_F(fixture_universe_performance, vector_10_objects)
{
   PrepareTheUniverse(10, mzlib::cuniverse::implementation::naive);
   RunSimulation();
}

TEST_F(fixture_universe_performance, vector_20_objects)
{
   PrepareTheUniverse(20, mzlib::cuniverse::implementation::naive);
   RunSimulation();
}

TEST_F(fixture_universe_performance, vector_40_objects)
{
   PrepareTheUniverse(40, mzlib::cuniverse::implementation::naive);
   RunSimulation();
}

TEST_F(fixture_universe_performance, vector_80_objects)
{
   PrepareTheUniverse(80, mzlib::cuniverse::implementation::naive);
   RunSimulation();
}

TEST_F(fixture_universe_performance, vector_160_objects)
{
   PrepareTheUniverse(160, mzlib::cuniverse::implementation::naive);
   RunSimulation();
}

TEST_F(fixture_universe_performance, vector_320_objects)
{
   PrepareTheUniverse(320, mzlib::cuniverse::implementation::naive);
   RunSimulation();
}

TEST_F(fixture_universe_performance, vector_640_objects)
{
   PrepareTheUniverse(640, mzlib::cuniverse::implementation::naive);
   RunSimulation();
}

TEST_F(fixture_universe_performance, vector_1280_objects)
{
   PrepareTheUniverse(1280, mzlib::cuniverse::implementation::naive);
   RunSimulation();
}






TEST_F(fixture_universe_performance, quad_3_objects_q0)
{
   PrepareTheUniverse(3, mzlib::cuniverse::implementation::barnes_hut, 0);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_5_objects_q0)
{
   PrepareTheUniverse(5, mzlib::cuniverse::implementation::barnes_hut, 0);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_10_objects_q0)
{
   PrepareTheUniverse(10, mzlib::cuniverse::implementation::barnes_hut, 0);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_20_objects_q0)
{
   PrepareTheUniverse(20, mzlib::cuniverse::implementation::barnes_hut, 0);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_40_objects_q0)
{
   PrepareTheUniverse(40, mzlib::cuniverse::implementation::barnes_hut, 0);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_80_objects_q0)
{
   PrepareTheUniverse(80, mzlib::cuniverse::implementation::barnes_hut, 0);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_160_objects_q0)
{
   PrepareTheUniverse(160, mzlib::cuniverse::implementation::barnes_hut, 0);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_320_objects_q0)
{
   PrepareTheUniverse(320, mzlib::cuniverse::implementation::barnes_hut, 0);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_640_objects_q0)
{
   PrepareTheUniverse(640, mzlib::cuniverse::implementation::barnes_hut, 0);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_1280_objects_q0)
{
   PrepareTheUniverse(1280, mzlib::cuniverse::implementation::barnes_hut, 0);
   RunSimulation();
}






TEST_F(fixture_universe_performance, quad_3_objects_q1)
{
   PrepareTheUniverse(3, mzlib::cuniverse::implementation::barnes_hut, 1);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_5_objects_q1)
{
   PrepareTheUniverse(5, mzlib::cuniverse::implementation::barnes_hut, 1);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_10_objects_q1)
{
   PrepareTheUniverse(10, mzlib::cuniverse::implementation::barnes_hut, 1);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_20_objects_q1)
{
   PrepareTheUniverse(20, mzlib::cuniverse::implementation::barnes_hut, 1);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_40_objects_q1)
{
   PrepareTheUniverse(40, mzlib::cuniverse::implementation::barnes_hut, 1);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_80_objects_q1)
{
   PrepareTheUniverse(80, mzlib::cuniverse::implementation::barnes_hut, 1);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_160_objects_q1)
{
   PrepareTheUniverse(160, mzlib::cuniverse::implementation::barnes_hut, 1);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_320_objects_q1)
{
   PrepareTheUniverse(320, mzlib::cuniverse::implementation::barnes_hut, 1);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_640_objects_q1)
{
   PrepareTheUniverse(640, mzlib::cuniverse::implementation::barnes_hut, 1);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_1280_objects_q1)
{
   PrepareTheUniverse(1280, mzlib::cuniverse::implementation::barnes_hut, 1);
   RunSimulation();
}






TEST_F(fixture_universe_performance, quad_3_objects_q2)
{
   PrepareTheUniverse(3, mzlib::cuniverse::implementation::barnes_hut, 2);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_5_objects_q2)
{
   PrepareTheUniverse(5, mzlib::cuniverse::implementation::barnes_hut, 2);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_10_objects_q2)
{
   PrepareTheUniverse(10, mzlib::cuniverse::implementation::barnes_hut, 2);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_20_objects_q2)
{
   PrepareTheUniverse(20, mzlib::cuniverse::implementation::barnes_hut, 2);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_40_objects_q2)
{
   PrepareTheUniverse(40, mzlib::cuniverse::implementation::barnes_hut, 2);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_80_objects_q2)
{
   PrepareTheUniverse(80, mzlib::cuniverse::implementation::barnes_hut, 2);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_160_objects_q2)
{
   PrepareTheUniverse(160, mzlib::cuniverse::implementation::barnes_hut, 2);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_320_objects_q2)
{
   PrepareTheUniverse(320, mzlib::cuniverse::implementation::barnes_hut, 2);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_640_objects_q2)
{
   PrepareTheUniverse(640, mzlib::cuniverse::implementation::barnes_hut, 2);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_1280_objects_q2)
{
   PrepareTheUniverse(1280, mzlib::cuniverse::implementation::barnes_hut, 2);
   RunSimulation();
}






TEST_F(fixture_universe_performance, quad_3_objects_q3)
{
   PrepareTheUniverse(3, mzlib::cuniverse::implementation::barnes_hut, 3);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_5_objects_q3)
{
   PrepareTheUniverse(5, mzlib::cuniverse::implementation::barnes_hut, 3);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_10_objects_q3)
{
   PrepareTheUniverse(10, mzlib::cuniverse::implementation::barnes_hut, 3);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_20_objects_q3)
{
   PrepareTheUniverse(20, mzlib::cuniverse::implementation::barnes_hut, 3);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_40_objects_q3)
{
   PrepareTheUniverse(40, mzlib::cuniverse::implementation::barnes_hut, 3);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_80_objects_q3)
{
   PrepareTheUniverse(80, mzlib::cuniverse::implementation::barnes_hut, 3);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_160_objects_q3)
{
   PrepareTheUniverse(160, mzlib::cuniverse::implementation::barnes_hut, 3);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_320_objects_q3)
{
   PrepareTheUniverse(320, mzlib::cuniverse::implementation::barnes_hut, 3);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_640_objects_q3)
{
   PrepareTheUniverse(640, mzlib::cuniverse::implementation::barnes_hut, 3);
   RunSimulation();
}

TEST_F(fixture_universe_performance, quad_1280_objects_q3)
{
   PrepareTheUniverse(1280, mzlib::cuniverse::implementation::barnes_hut, 3);
   RunSimulation();
}
