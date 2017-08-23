//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#define private public
#define protected public
#include "../include/nature/universe.h"
#undef private
#undef protected

#include "../include/nature/units.h"
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
   auto tag = universe.add_copy(body);
   const mzlib::body_core2d& found_core = universe.get_body_core(tag);
   ASSERT_EQ(found_core.tag, body.core.tag);
}

TEST_F(fixture_universe, after_adding_bodies_feel_force)
{
   mzlib::body2d sun;
   sun.core.centre.mass = mzlib::consts::sun_mass;
    
   mzlib::body2d earth;
   earth.core.centre.location = {0,mzlib::consts::earth_distance_sun};
   earth.core.centre.mass = mzlib::consts::earth_mass;
    
   auto sun_tag = universe.add_copy(sun);
	auto earth_tag = universe.add_copy(earth);
    
   mzlib::vector2d f_sun = universe.get_body_properties(sun_tag).gravity;
   mzlib::vector2d f_earth = universe.get_body_properties(earth_tag).gravity;
    
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
   sun.core.centre.mass = mzlib::consts::sun_mass;
    
   mzlib::body2d earth;
   mzlib::vector2d earth_location_start = {0,mzlib::consts::earth_distance_sun_aphelion};
   earth.core.centre.location = earth_location_start;
   earth.core.centre.mass = mzlib::consts::earth_mass;
   earth.properties.velocity = {mzlib::consts::earth_velocity_aphelion,0};
    
   universe.add_copy(sun);
	auto earth_tag = universe.add_copy(earth);
   universe.forward_time(30.0_day, 1.0_day);
   
   mzlib::vector2d earth_location_quarter_later = universe.get_body_core(earth_tag).centre.location;
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
   sun.core.centre.mass = mzlib::consts::sun_mass;
    
   mzlib::body2d earth;
   mzlib::vector2d earth_location_start = {0,mzlib::consts::earth_distance_sun_aphelion};
   earth.core.centre.location = earth_location_start;
   earth.core.centre.mass = mzlib::consts::earth_mass;
   earth.properties.velocity = {mzlib::consts::earth_velocity_aphelion,0};
    
   universe.add_copy(sun);
	auto earth_tag = universe.add_copy(earth);
   universe.forward_time(30.0_day, 1.0_day);
   
   mzlib::vector2d earth_location_quarter_later = universe.get_body_core(earth_tag).centre.location;
   ASSERT_NEAR(earth_location_quarter_later[0], 7.3e10_m, 0.2e10_m);
   ASSERT_NEAR(earth_location_quarter_later[1], 13.5e10_m, 0.2e10_m);
}

TEST_F(fixture_universe, DISABLED_long_earth_around_the_sun)
{
   mzlib::body2d sun;
   sun.core.centre.mass = mzlib::consts::sun_mass;
    
   mzlib::body2d earth;
   mzlib::vector2d earth_location_start = {0,mzlib::consts::earth_distance_sun_aphelion};
   earth.core.centre.location = earth_location_start;
   earth.core.centre.mass = mzlib::consts::earth_mass;
   earth.properties.velocity = {mzlib::consts::earth_velocity_aphelion,0};
    
   universe.add_copy(sun);
	auto earth_tag = universe.add_copy(earth);
   universe.forward_time(0.25_julian_year, 10.0_s);     
   
   mzlib::vector2d earth_location_quarter_later = universe.get_body_core(earth_tag).centre.location;
   
   ASSERT_NEAR(earth_location_quarter_later[0], mzlib::consts::earth_distance_sun_perihelion, 2500000.0_km); // 1 day off
   ASSERT_NEAR(earth_location_quarter_later[1], 0, 5000000.0_km); // 2 days off
    
   universe.forward_time(0.75_julian_year, 10.0_s);
    
   mzlib::vector2d earth_location_year_later = universe.get_body_core(earth_tag).centre.location;
    
   ASSERT_NEAR(earth_location_year_later[0], 0, 10000000.0_km); // 4 days off
   ASSERT_NEAR(earth_location_year_later[1], mzlib::consts::earth_distance_sun_aphelion, 2000000.0_km); // 8 days off
}
      
TEST_F(fixture_universe, moving_object)
{
   mzlib::body2d body;
   
   body.core.centre.location = {1.0_m, 2.0_m};
   mzlib::vector2d move_to = {3.0_m, 4.0_m};

   auto tag = universe.add_copy(body); 
   universe.move(tag, move_to);
   
   // measure location
   mzlib::vector2d location_after_move = universe.get_body_core(tag).centre.location;
   
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
   
   body.core.centre.location = {1.0_m, 2.0_m};
   mzlib::vector2d move_to = {3.0_m, 4.0_m};

   auto tag = universe.add_copy(body); 
   universe.move(tag, move_to);
   
   // measure location
   mzlib::vector2d location_after_move = universe.get_body_core(tag).centre.location;
   
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
   body1.core.centre.mass = 10.0_kg;
   body1.core.centre.location = body1_location_start;
   body2.core.centre.mass = 10.0_kg; 
   body2.core.centre.location = body2_location_start;
   body1.properties.velocity = body1_velocity;
   auto tag1 = universe.add_copy(body1);
	auto tag2 = universe.add_copy(body2); 
   
   // simulation
   universe.forward_time(1.0_s, 1.0_s);
   universe.forward_time(1.0_s, 1.0_s);
   
   // measure location
   mzlib::vector2d body1_location_without_move = universe.get_body_core(tag1).centre.location;
   
   // reset to start state
   universe.remove(tag1);
   universe.remove(tag2);
   body1.core.centre.location = body1_location_start;
   body2.core.centre.location = body2_location_start;
   body2.properties.velocity = body1_velocity;
   tag1 = universe.add_copy(body1);
	tag2 = universe.add_copy(body2);

   // simulation   
   universe.forward_time(1.0_s, 1.0_s);
   mzlib::vector2d move_to = universe.get_body_core(tag1).centre.location + body1_move_vector;
   universe.move(tag1, move_to);
   universe.forward_time(1.0_s, 1.0_s);
   
   // measure location
   mzlib::vector2d body1_location_with_move = universe.get_body_core(tag1).centre.location;
   
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
   body1.core.centre.mass = 10.0_kg;
   body1.core.centre.location = body1_location_start;
   body2.core.centre.mass = 10.0_kg; 
   body2.core.centre.location = body2_location_start;
   body1.properties.velocity = body1_velocity;
   auto tag1 = universe.add_copy(body1);
	auto tag2 = universe.add_copy(body2); 
   
   // simulation
   universe.forward_time(1.0_s, 1.0_s);
   universe.forward_time(1.0_s, 1.0_s);
   
   // measure location
   mzlib::vector2d body1_location_without_move = universe.get_body_core(tag1).centre.location;
   
   // reset to start state
   universe.remove(tag1);
   universe.remove(tag2);
   body1.core.centre.location = body1_location_start;
   body2.core.centre.location = body2_location_start;
   body2.properties.velocity = body1_velocity;
   tag1 = universe.add_copy(body1);
	tag2 = universe.add_copy(body2);

   // simulation   
   universe.forward_time(1.0_s, 1.0_s);
   mzlib::vector2d move_to = universe.get_body_core(tag1).centre.location + body1_move_vector;
   universe.move(tag1, move_to);
   universe.forward_time(1.0_s, 1.0_s);
   
   // measure location
   mzlib::vector2d body1_location_with_move = universe.get_body_core(tag1).centre.location;
   
   // did move work correctly?
   auto distance = body1_location_without_move - body1_location_with_move;
   ASSERT_NEAR(distance.length(), body1_move_vector.length(), 10.0_m);
}