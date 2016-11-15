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

TEST_F(fixture_universe, sun_force_on_earth)
{
   mzlib::cbody2d sun;
   sun.mass_centre.mass = mzlib::consts::sun_mass;
    
   mzlib::cbody2d earth;
   earth.mass_centre.location = {0,mzlib::consts::earth_distance_sun_average};
   earth.mass_centre.mass = mzlib::consts::earth_mass;
    
   universe.add(sun);
	universe.add(earth);
   universe.calculate_forces();
    
   mzlib::cvector2d f_sun = universe.find(sun)->data.gravity;
   mzlib::cvector2d f_earth = universe.find(earth)->data.gravity;
    
   ASSERT_EQ(f_earth, -f_sun);
   ASSERT_NEAR(f_earth.length(), 3.53e+22, 0.01e+22);
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
   earth.data.velocity = {mzlib::consts::earth_speed_aphelion,0};
    
   universe.add(sun);
	universe.add(earth);
   universe.forward_time(30.0_day, 1.0_day);
   
   mzlib::cvector2d earth_location_quarter_later = universe.find(earth)->mass_centre.location;
   ASSERT_NEAR(earth_location_quarter_later[0], 7.3e10_m, 0.1e10_m);
   ASSERT_NEAR(earth_location_quarter_later[1], 13.5e10_m, 0.1e10_m);
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
   earth.data.velocity = {mzlib::consts::earth_speed_aphelion,0};
    
   universe.add(sun);
	universe.add(earth);
   universe.forward_time(30.0_day, 1.0_day);
   
   mzlib::cvector2d earth_location_quarter_later = universe.find(earth)->mass_centre.location;
   ASSERT_NEAR(earth_location_quarter_later[0], 7.3e10_m, 0.1e10_m);
   ASSERT_NEAR(earth_location_quarter_later[1], 13.5e10_m, 0.1e10_m);
}

TEST_F(fixture_universe, long_earth_around_the_sun)
{
   mzlib::cbody2d sun;
   sun.mass_centre.mass = mzlib::consts::sun_mass;
    
   mzlib::cbody2d earth;
   mzlib::cvector2d earth_location_start = {0,mzlib::consts::earth_distance_sun_aphelion};
   earth.mass_centre.location = earth_location_start;
   earth.mass_centre.mass = mzlib::consts::earth_mass;
   earth.data.velocity = {mzlib::consts::earth_speed_aphelion,0};
    
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
      
TEST_F(fixture_universe, moving_object_while_gravity_simulation_running)
{
   mzlib::cbody2d sun;
   mzlib::cbody2d earth;

   mzlib::cvector2d earth_location_start = {0,mzlib::consts::earth_distance_sun_aphelion};
   mzlib::cvector2d sun_location_start = {0,0};
   mzlib::cvector2d earth_move_distance = {10.0_km, 10.0_km};

   // setup start state   
   sun.mass_centre.mass = mzlib::consts::sun_mass;
   sun.mass_centre.location = sun_location_start;
   earth.mass_centre.mass = mzlib::consts::earth_mass; 
   earth.mass_centre.location = earth_location_start;
   earth.data.velocity = {mzlib::consts::earth_speed_aphelion,0};
   universe.add(sun);
	universe.add(earth); 
   
   // simulation
   universe.forward_time(1.0_h, 1.0_h);
   universe.forward_time(1.0_s, 1.0_s);
   
   // measure location
   mzlib::cvector2d earth_location_without_move = universe.find(earth)->mass_centre.location;
   
   // reset to start state
   universe.remove(earth);
   universe.remove(sun);
   sun.mass_centre.mass = mzlib::consts::sun_mass;
   sun.mass_centre.location = sun_location_start;
   earth.mass_centre.mass = mzlib::consts::earth_mass; 
   earth.mass_centre.location = earth_location_start;
   earth.data.velocity = {mzlib::consts::earth_speed_aphelion,0};
   universe.add(sun);
	universe.add(earth);

   // simulate a day, but move earth by a couple of kilometers in the middle of day   
   universe.forward_time(1.0_h, 1.0_h);
   mzlib::cvector2d move_to = universe.find(earth)->mass_centre.location + earth_move_distance;
   universe.move(earth, move_to);
   universe.forward_time(1.0_s, 1.0_s);
   
   // measure location
   mzlib::cvector2d earth_location_with_move = universe.find(earth)->mass_centre.location;
   
   // did move work correctly?
   ASSERT_NEAR(earth_location_without_move[0], earth_location_with_move[0], 10.0_km);
   ASSERT_NEAR(earth_location_without_move[1], earth_location_with_move[1], 10.0_km);
}