//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "../include/universe.h"
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

TEST_F(fixture_universe, set_gravitational_constant)
{
   universe.set_gravitational_constant(0.5);
   ASSERT_DOUBLE_EQ(0.5, universe.get_gravitational_constant());
}

TEST_F(fixture_universe, big_ben_force_on_empire_state_building)
{
   mzlib::cbody2d big_ben;
   big_ben.mass = 10e8_kg; // 10e8 kg
    
   mzlib::cbody2d empire_state_building;
   empire_state_building.location = {0,5000.0_km}; // 5000 km
   empire_state_building.mass = 10e9_kg; // 10e9 kg
    
   universe.add_body(big_ben);
	universe.add_body(empire_state_building);
   universe.calculate_forces();
    
   mzlib::math::cvector2d f_empire_state_building = empire_state_building.data.force;
   mzlib::math::cvector2d f_big_ben = big_ben.data.force;
    
   ASSERT_EQ(f_empire_state_building, -f_big_ben);
   ASSERT_NEAR(f_big_ben.length(), 2.67e-7, 0.01); // 2.67e-7 +- 0.01
}

TEST_F(fixture_universe, sun_force_on_earth)
{
   mzlib::cbody2d sun;
   sun.mass = mzlib::consts::sun_mass; // 1.99e30
    
   mzlib::cbody2d earth;
   earth.location = {0,mzlib::consts::earth_distance_sun_average};
   earth.mass = mzlib::consts::earth_mass;
    
   universe.add_body(sun);
	universe.add_body(earth);
   universe.calculate_forces();
    
   mzlib::math::cvector2d f_sun = universe.find_body(sun)->data.force;
   mzlib::math::cvector2d f_earth = universe.find_body(earth)->data.force;
    
   ASSERT_EQ(f_earth, -f_sun);
   ASSERT_NEAR(f_earth.length(), 3.53e+22, 0.01e+22);
}

TEST_F(fixture_universe, long_earth_around_the_sun)
{
   mzlib::cbody2d sun;
   sun.mass = 1.989e30;
    
   mzlib::cbody2d earth;
   mzlib::math::cvector2d earth_location_start = {0,mzlib::consts::earth_distance_sun_aphelion};
   earth.location = earth_location_start;
   earth.mass = mzlib::consts::earth_mass;
   earth.data.velocity = {mzlib::consts::earth_speed_aphelion,0};
    
   universe.add_body(sun);
	universe.add_body(earth);
   universe.forward_time(0.25_julian_year, 10.0_s);     
   
   mzlib::math::cvector2d earth_location_quarter_later = universe.find_body(earth)->location;
   
   ASSERT_NEAR(earth_location_quarter_later[0], mzlib::consts::earth_distance_sun_perihelion, 2500000.0_km); // 1 day off
   ASSERT_NEAR(earth_location_quarter_later[1], 0, 5000000.0_km); // 2 days off
    
   universe.forward_time(0.75_julian_year, 10.0_s);
    
   mzlib::math::cvector2d earth_location_year_later = universe.find_body(earth)->location;
    
   ASSERT_NEAR(earth_location_year_later[0], 0, 10000000.0_km); // 4 days off
   ASSERT_NEAR(earth_location_year_later[1], mzlib::consts::earth_distance_sun_aphelion, 2000000.0_km); // 8 days off
}

TEST_F(fixture_universe, moving_object_while_gravity_simulation_running)
{
   mzlib::cbody2d sun;
   mzlib::cbody2d earth;

   mzlib::math::cvector2d earth_location_start = {0,mzlib::consts::earth_distance_sun_aphelion};
   mzlib::math::cvector2d sun_location_start = {0,0};
   mzlib::math::cvector2d earth_move_distance = {10.0_km, 10.0_km};

   // setup start state   
   sun.mass = mzlib::consts::sun_mass;
   sun.location = sun_location_start;
   earth.mass = mzlib::consts::earth_mass; 
   earth.location = earth_location_start;
   earth.data.velocity = {mzlib::consts::earth_speed_aphelion,0};
   universe.add_body(sun);
	universe.add_body(earth); 
   
   // simulation
   universe.forward_time(1.0_h, 1.0_h);
   universe.forward_time(1.0_s, 1.0_s);
   
   // measure location
   mzlib::math::cvector2d earth_location_without_move = universe.find_body(earth)->location;
   
   // reset to start state
   universe.get_tree().remove(earth.data);
   universe.get_tree().remove(sun.data);
   sun.mass = mzlib::consts::sun_mass;
   sun.location = sun_location_start;
   earth.mass = mzlib::consts::earth_mass; 
   earth.location = earth_location_start;
   earth.data.velocity = {mzlib::consts::earth_speed_aphelion,0};
   universe.add_body(sun);
	universe.add_body(earth);

   // simulate a day, but move earth by a couple kilometers in the middle of day   
   universe.forward_time(1.0_h, 1.0_h);
   mzlib::math::cvector2d move_to = universe.find_body(earth)->location + earth_move_distance;
   universe.get_tree().move(earth.data, move_to);
   universe.forward_time(1.0_s, 1.0_s);
   
   // measure location
   mzlib::math::cvector2d earth_location_with_move = universe.find_body(earth)->location;
   
   // did move work correctly?
   ASSERT_NEAR(earth_location_without_move[0], earth_location_with_move[0], 10.0_km);
   ASSERT_NEAR(earth_location_without_move[1], earth_location_with_move[1], 10.0_km);
}