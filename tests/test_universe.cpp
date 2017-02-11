//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#define private public
#define protected public
#include "../include/universe.h"
#undef private
#undef protected

#include "../include/units.h"
#include "gtest/gtest.h"

using namespace mzlib::units;

class fixture_universe : public ::testing::Test 
{

protected:
   
   fixture_universe() {}
   virtual ~fixture_universe() {}
   virtual void SetUp() {}
   virtual void TearDown() {}

   mzlib::universe universe;
  
};

TEST_F(fixture_universe, after_adding_body_is_found)
{
   mzlib::body2d body;
   universe.add(body);
   auto found_body = universe.find(body);
   ASSERT_NE(nullptr, found_body);
   ASSERT_EQ(found_body->tag, body.tag);
}

TEST_F(fixture_universe, after_adding_bodies_feel_force)
{
   mzlib::body2d sun;
   sun.centre.mass = mzlib::consts::sun_mass;
    
   mzlib::body2d earth;
   earth.centre.location = {0,mzlib::consts::earth_distance_sun};
   earth.centre.mass = mzlib::consts::earth_mass;
    
   universe.add(sun);
	universe.add(earth);
    
   mzlib::vector2d f_sun = universe.find(sun)->properties.gravity;
   mzlib::vector2d f_earth = universe.find(earth)->properties.gravity;
    
   ASSERT_EQ(f_earth, -f_sun);
   ASSERT_NEAR(f_earth.length(), 3.541e+22, 0.001e+22);
}

TEST_F(fixture_universe, sun_earth_month_travel_barneshut_with_quotient_more_than_0)
{
   mzlib::universe local_universe;
   mzlib::universe::tproperties properties;
   properties.m_implementation = mzlib::universe::implementation::barnes_hut;
   properties.m_barnes_hut_quotient = 1;
   local_universe.set_properties(properties);
   
   mzlib::body2d sun;
   sun.centre.mass = mzlib::consts::sun_mass;
    
   mzlib::body2d earth;
   mzlib::vector2d earth_location_start = {0,mzlib::consts::earth_distance_sun_aphelion};
   earth.centre.location = earth_location_start;
   earth.centre.mass = mzlib::consts::earth_mass;
   earth.properties.velocity = {mzlib::consts::earth_velocity_aphelion,0};
    
   universe.add(sun);
	universe.add(earth);
   universe.forward_time(30.0_day, 1.0_day);
   
   mzlib::vector2d earth_location_quarter_later = universe.find(earth)->centre.location;
   ASSERT_NEAR(earth_location_quarter_later[0], 7.3e10_m, 0.2e10_m);
   ASSERT_NEAR(earth_location_quarter_later[1], 13.5e10_m, 0.2e10_m);
}

TEST_F(fixture_universe, sun_earth_month_travel_naive)
{
   mzlib::universe local_universe;
   mzlib::universe::tproperties properties;
   properties.m_implementation = mzlib::universe::implementation::naive;
   local_universe.set_properties(properties);
   
   mzlib::body2d sun;
   sun.centre.mass = mzlib::consts::sun_mass;
    
   mzlib::body2d earth;
   mzlib::vector2d earth_location_start = {0,mzlib::consts::earth_distance_sun_aphelion};
   earth.centre.location = earth_location_start;
   earth.centre.mass = mzlib::consts::earth_mass;
   earth.properties.velocity = {mzlib::consts::earth_velocity_aphelion,0};
    
   universe.add(sun);
	universe.add(earth);
   universe.forward_time(30.0_day, 1.0_day);
   
   mzlib::vector2d earth_location_quarter_later = universe.find(earth)->centre.location;
   ASSERT_NEAR(earth_location_quarter_later[0], 7.3e10_m, 0.2e10_m);
   ASSERT_NEAR(earth_location_quarter_later[1], 13.5e10_m, 0.2e10_m);
}

TEST_F(fixture_universe, long_earth_around_the_sun)
{
   mzlib::body2d sun;
   sun.centre.mass = mzlib::consts::sun_mass;
    
   mzlib::body2d earth;
   mzlib::vector2d earth_location_start = {0,mzlib::consts::earth_distance_sun_aphelion};
   earth.centre.location = earth_location_start;
   earth.centre.mass = mzlib::consts::earth_mass;
   earth.properties.velocity = {mzlib::consts::earth_velocity_aphelion,0};
    
   universe.add(sun);
	universe.add(earth);
   universe.forward_time(0.25_julian_year, 10.0_s);     
   
   mzlib::vector2d earth_location_quarter_later = universe.find(earth)->centre.location;
   
   ASSERT_NEAR(earth_location_quarter_later[0], mzlib::consts::earth_distance_sun_perihelion, 2500000.0_km); // 1 day off
   ASSERT_NEAR(earth_location_quarter_later[1], 0, 5000000.0_km); // 2 days off
    
   universe.forward_time(0.75_julian_year, 10.0_s);
    
   mzlib::vector2d earth_location_year_later = universe.find(earth)->centre.location;
    
   ASSERT_NEAR(earth_location_year_later[0], 0, 10000000.0_km); // 4 days off
   ASSERT_NEAR(earth_location_year_later[1], mzlib::consts::earth_distance_sun_aphelion, 2000000.0_km); // 8 days off
}
      
TEST_F(fixture_universe, moving_object)
{
   mzlib::body2d body;
   
   body.centre.location = {1.0_m, 2.0_m};
   mzlib::vector2d move_to = {3.0_m, 4.0_m};

   universe.add(body); 
   universe.move(body, move_to);
   
   // measure location
   mzlib::vector2d location_after_move = universe.find(body)->centre.location;
   
   // did move work correctly?
   ASSERT_NEAR(location_after_move[0], move_to[0], 1.0_mm);
   ASSERT_NEAR(location_after_move[1], move_to[1], 1.0_mm);
}

TEST_F(fixture_universe, moving_object_naive)
{
   mzlib::universe::tproperties properties;
   properties.m_implementation = mzlib::universe::implementation::naive;
   universe.set_properties(properties);
   
   mzlib::body2d body;
   
   body.centre.location = {1.0_m, 2.0_m};
   mzlib::vector2d move_to = {3.0_m, 4.0_m};

   universe.add(body); 
   universe.move(body, move_to);
   
   // measure location
   mzlib::vector2d location_after_move = universe.find(body)->centre.location;
   
   // did move work correctly?
   ASSERT_NEAR(location_after_move[0], move_to[0], 1.0_mm);
   ASSERT_NEAR(location_after_move[1], move_to[1], 1.0_mm);
}

TEST_F(fixture_universe, moving_object_while_gravity_simulation_running)
{
   mzlib::body2d body1;
   mzlib::body2d body2;

   mzlib::vector2d body1_location_start = { 0.0_m, 10.0_m};
   mzlib::vector2d body1_move_vector =    { 0.0_m, 10.0_m};
   mzlib::vector2d body2_location_start = { 0.0_m,  0.0_m};
   mzlib::vector2d body1_velocity = { 0.0_m_per_s, 10.0_m_per_s};
   
   // setup start state   
   body1.centre.mass = 10.0_kg;
   body1.centre.location = body1_location_start;
   body2.centre.mass = 10.0_kg; 
   body2.centre.location = body2_location_start;
   body1.properties.velocity = body1_velocity;
   universe.add(body1);
	universe.add(body2); 
   
   // simulation
   universe.forward_time(1.0_s, 1.0_s);
   universe.forward_time(1.0_s, 1.0_s);
   
   // measure location
   mzlib::vector2d body1_location_without_move = universe.find(body1)->centre.location;
   
   // reset to start state
   universe.remove(body1);
   universe.remove(body2);
   body1.centre.location = body1_location_start;
   body2.centre.location = body2_location_start;
   body2.properties.velocity = body1_velocity;
   universe.add(body1);
	universe.add(body2);

   // simulation   
   universe.forward_time(1.0_s, 1.0_s);
   mzlib::vector2d move_to = universe.find(body1)->centre.location + body1_move_vector;
   universe.move(body1, move_to);
   universe.forward_time(1.0_s, 1.0_s);
   
   // measure location
   mzlib::vector2d body1_location_with_move = universe.find(body1)->centre.location;
   
   // did move work correctly?
   auto distance = body1_location_without_move - body1_location_with_move;
   ASSERT_NEAR(distance.length(), body1_move_vector.length(), 10.0_m);
}
   
TEST_F(fixture_universe, moving_object_while_gravity_simulation_running_naive)
{
   mzlib::universe::tproperties properties;
   properties.m_implementation = mzlib::universe::implementation::naive;
   universe.set_properties(properties);

   mzlib::body2d body1;
   mzlib::body2d body2;

   mzlib::vector2d body1_location_start = { 0.0_m, 10.0_m};
   mzlib::vector2d body1_move_vector =    { 0.0_m, 10.0_m};
   mzlib::vector2d body2_location_start = { 0.0_m,  0.0_m};
   mzlib::vector2d body1_velocity = { 0.0_m_per_s, 10.0_m_per_s};
   
   // setup start state   
   body1.centre.mass = 10.0_kg;
   body1.centre.location = body1_location_start;
   body2.centre.mass = 10.0_kg; 
   body2.centre.location = body2_location_start;
   body1.properties.velocity = body1_velocity;
   universe.add(body1);
	universe.add(body2); 
   
   // simulation
   universe.forward_time(1.0_s, 1.0_s);
   universe.forward_time(1.0_s, 1.0_s);
   
   // measure location
   mzlib::vector2d body1_location_without_move = universe.find(body1)->centre.location;
   
   // reset to start state
   universe.remove(body1);
   universe.remove(body2);
   body1.centre.location = body1_location_start;
   body2.centre.location = body2_location_start;
   body2.properties.velocity = body1_velocity;
   universe.add(body1);
	universe.add(body2);

   // simulation   
   universe.forward_time(1.0_s, 1.0_s);
   mzlib::vector2d move_to = universe.find(body1)->centre.location + body1_move_vector;
   universe.move(body1, move_to);
   universe.forward_time(1.0_s, 1.0_s);
   
   // measure location
   mzlib::vector2d body1_location_with_move = universe.find(body1)->centre.location;
   
   // did move work correctly?
   auto distance = body1_location_without_move - body1_location_with_move;
   ASSERT_NEAR(distance.length(), body1_move_vector.length(), 10.0_m);
}