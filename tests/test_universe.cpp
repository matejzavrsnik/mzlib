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

   mzlib::cuniverse universe;
  
};

TEST_F(fixture_universe, after_adding_body_is_found)
{
   mzlib::cbody2d body;
   universe.add(body);
   auto found_body = universe.find(body);
   ASSERT_NE(nullptr, found_body);
   ASSERT_EQ(found_body->data, body.data);
}

TEST_F(fixture_universe, after_adding_bodies_feel_force)
{
   mzlib::cbody2d sun;
   sun.mass_centre.mass = mzlib::consts::sun_mass;
    
   mzlib::cbody2d earth;
   earth.mass_centre.location = {0,mzlib::consts::earth_distance_sun};
   earth.mass_centre.mass = mzlib::consts::earth_mass;
    
   universe.add(sun);
	universe.add(earth);
    
   mzlib::cvector2d f_sun = universe.find(sun)->data.gravity;
   mzlib::cvector2d f_earth = universe.find(earth)->data.gravity;
    
   ASSERT_EQ(f_earth, -f_sun);
   ASSERT_NEAR(f_earth.length(), 3.541e+22, 0.001e+22);
}

TEST_F(fixture_universe, sun_earth_month_travel_barneshut_with_quotient_more_than_0)
{
   mzlib::cuniverse local_universe;
   mzlib::cuniverse::tproperties properties;
   properties.m_implementation = mzlib::cuniverse::implementation::barnes_hut;
   properties.m_barnes_hut_quotient = 1;
   local_universe.set_properties(properties);
   
   mzlib::cbody2d sun;
   sun.mass_centre.mass = mzlib::consts::sun_mass;
    
   mzlib::cbody2d earth;
   mzlib::cvector2d earth_location_start = {0,mzlib::consts::earth_distance_sun_aphelion};
   earth.mass_centre.location = earth_location_start;
   earth.mass_centre.mass = mzlib::consts::earth_mass;
   earth.data.velocity = {mzlib::consts::earth_velocity_aphelion,0};
    
   universe.add(sun);
	universe.add(earth);
   universe.forward_time(30.0_day, 1.0_day);
   
   mzlib::cvector2d earth_location_quarter_later = universe.find(earth)->mass_centre.location;
   ASSERT_NEAR(earth_location_quarter_later[0], 7.3e10_m, 0.2e10_m);
   ASSERT_NEAR(earth_location_quarter_later[1], 13.5e10_m, 0.2e10_m);
}

TEST_F(fixture_universe, sun_earth_month_travel_naive)
{
   mzlib::cuniverse local_universe;
   mzlib::cuniverse::tproperties properties;
   properties.m_implementation = mzlib::cuniverse::implementation::naive;
   local_universe.set_properties(properties);
   
   mzlib::cbody2d sun;
   sun.mass_centre.mass = mzlib::consts::sun_mass;
    
   mzlib::cbody2d earth;
   mzlib::cvector2d earth_location_start = {0,mzlib::consts::earth_distance_sun_aphelion};
   earth.mass_centre.location = earth_location_start;
   earth.mass_centre.mass = mzlib::consts::earth_mass;
   earth.data.velocity = {mzlib::consts::earth_velocity_aphelion,0};
    
   universe.add(sun);
	universe.add(earth);
   universe.forward_time(30.0_day, 1.0_day);
   
   mzlib::cvector2d earth_location_quarter_later = universe.find(earth)->mass_centre.location;
   ASSERT_NEAR(earth_location_quarter_later[0], 7.3e10_m, 0.2e10_m);
   ASSERT_NEAR(earth_location_quarter_later[1], 13.5e10_m, 0.2e10_m);
}

TEST_F(fixture_universe, long_earth_around_the_sun)
{
   mzlib::cbody2d sun;
   sun.mass_centre.mass = mzlib::consts::sun_mass;
    
   mzlib::cbody2d earth;
   mzlib::cvector2d earth_location_start = {0,mzlib::consts::earth_distance_sun_aphelion};
   earth.mass_centre.location = earth_location_start;
   earth.mass_centre.mass = mzlib::consts::earth_mass;
   earth.data.velocity = {mzlib::consts::earth_velocity_aphelion,0};
    
   universe.add(sun);
	universe.add(earth);
   universe.forward_time(0.25_julian_year, 10.0_s);     
   
   mzlib::cvector2d earth_location_quarter_later = universe.find(earth)->mass_centre.location;
   
   ASSERT_NEAR(earth_location_quarter_later[0], mzlib::consts::earth_distance_sun_perihelion, 2500000.0_km); // 1 day off
   ASSERT_NEAR(earth_location_quarter_later[1], 0, 5000000.0_km); // 2 days off
    
   universe.forward_time(0.75_julian_year, 10.0_s);
    
   mzlib::cvector2d earth_location_year_later = universe.find(earth)->mass_centre.location;
    
   ASSERT_NEAR(earth_location_year_later[0], 0, 10000000.0_km); // 4 days off
   ASSERT_NEAR(earth_location_year_later[1], mzlib::consts::earth_distance_sun_aphelion, 2000000.0_km); // 8 days off
}
      
TEST_F(fixture_universe, moving_object)
{
   mzlib::cbody2d body;
   
   body.mass_centre.location = {1.0_m, 2.0_m};
   mzlib::cvector2d move_to = {3.0_m, 4.0_m};

   universe.add(body); 
   universe.move(body, move_to);
   
   // measure location
   mzlib::cvector2d location_after_move = universe.find(body)->mass_centre.location;
   
   // did move work correctly?
   ASSERT_NEAR(location_after_move[0], move_to[0], 1.0_mm);
   ASSERT_NEAR(location_after_move[1], move_to[1], 1.0_mm);
}

TEST_F(fixture_universe, moving_object_naive)
{
   mzlib::cuniverse::tproperties properties;
   properties.m_implementation = mzlib::cuniverse::implementation::naive;
   universe.set_properties(properties);
   
   mzlib::cbody2d body;
   
   body.mass_centre.location = {1.0_m, 2.0_m};
   mzlib::cvector2d move_to = {3.0_m, 4.0_m};

   universe.add(body); 
   universe.move(body, move_to);
   
   // measure location
   mzlib::cvector2d location_after_move = universe.find(body)->mass_centre.location;
   
   // did move work correctly?
   ASSERT_NEAR(location_after_move[0], move_to[0], 1.0_mm);
   ASSERT_NEAR(location_after_move[1], move_to[1], 1.0_mm);
}

TEST_F(fixture_universe, moving_object_while_gravity_simulation_running)
{
   mzlib::cbody2d body1;
   mzlib::cbody2d body2;

   mzlib::cvector2d body1_location_start = { 0.0_m, 10.0_m};
   mzlib::cvector2d body1_move_vector =    { 0.0_m, 10.0_m};
   mzlib::cvector2d body2_location_start = { 0.0_m,  0.0_m};
   mzlib::cvector2d body1_velocity = { 0.0_m_per_s, 10.0_m_per_s};
   
   // setup start state   
   body1.mass_centre.mass = 10.0_kg;
   body1.mass_centre.location = body1_location_start;
   body2.mass_centre.mass = 10.0_kg; 
   body2.mass_centre.location = body2_location_start;
   body1.data.velocity = body1_velocity;
   universe.add(body1);
	universe.add(body2); 
   
   // simulation
   universe.forward_time(1.0_s, 1.0_s);
   universe.forward_time(1.0_s, 1.0_s);
   
   // measure location
   mzlib::cvector2d body1_location_without_move = universe.find(body1)->mass_centre.location;
   
   // reset to start state
   universe.remove(body1);
   universe.remove(body2);
   body1.mass_centre.location = body1_location_start;
   body2.mass_centre.location = body2_location_start;
   body2.data.velocity = body1_velocity;
   universe.add(body1);
	universe.add(body2);

   // simulation   
   universe.forward_time(1.0_s, 1.0_s);
   mzlib::cvector2d move_to = universe.find(body1)->mass_centre.location + body1_move_vector;
   universe.move(body1, move_to);
   universe.forward_time(1.0_s, 1.0_s);
   
   // measure location
   mzlib::cvector2d body1_location_with_move = universe.find(body1)->mass_centre.location;
   
   // did move work correctly?
   auto distance = body1_location_without_move - body1_location_with_move;
   ASSERT_NEAR(distance.length(), body1_move_vector.length(), 10.0_m);
}
   
TEST_F(fixture_universe, moving_object_while_gravity_simulation_running_naive)
{
   mzlib::cuniverse::tproperties properties;
   properties.m_implementation = mzlib::cuniverse::implementation::naive;
   universe.set_properties(properties);

   mzlib::cbody2d body1;
   mzlib::cbody2d body2;

   mzlib::cvector2d body1_location_start = { 0.0_m, 10.0_m};
   mzlib::cvector2d body1_move_vector =    { 0.0_m, 10.0_m};
   mzlib::cvector2d body2_location_start = { 0.0_m,  0.0_m};
   mzlib::cvector2d body1_velocity = { 0.0_m_per_s, 10.0_m_per_s};
   
   // setup start state   
   body1.mass_centre.mass = 10.0_kg;
   body1.mass_centre.location = body1_location_start;
   body2.mass_centre.mass = 10.0_kg; 
   body2.mass_centre.location = body2_location_start;
   body1.data.velocity = body1_velocity;
   universe.add(body1);
	universe.add(body2); 
   
   // simulation
   universe.forward_time(1.0_s, 1.0_s);
   universe.forward_time(1.0_s, 1.0_s);
   
   // measure location
   mzlib::cvector2d body1_location_without_move = universe.find(body1)->mass_centre.location;
   
   // reset to start state
   universe.remove(body1);
   universe.remove(body2);
   body1.mass_centre.location = body1_location_start;
   body2.mass_centre.location = body2_location_start;
   body2.data.velocity = body1_velocity;
   universe.add(body1);
	universe.add(body2);

   // simulation   
   universe.forward_time(1.0_s, 1.0_s);
   mzlib::cvector2d move_to = universe.find(body1)->mass_centre.location + body1_move_vector;
   universe.move(body1, move_to);
   universe.forward_time(1.0_s, 1.0_s);
   
   // measure location
   mzlib::cvector2d body1_location_with_move = universe.find(body1)->mass_centre.location;
   
   // did move work correctly?
   auto distance = body1_location_without_move - body1_location_with_move;
   ASSERT_NEAR(distance.length(), body1_move_vector.length(), 10.0_m);
}