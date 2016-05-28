// 
// Author: Matej Zavrsnik (matejzavrsnik.com)
//

#include "../include/space.h"
#include "../include/units.h"
#include "gtest/gtest.h"

namespace {

// The fixture

using namespace mzlib::units;
    
class test_space : public ::testing::Test {
 protected:

  test_space() {
  }
  
  virtual ~test_space() {
  }

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }

  std::shared_ptr<mzlib::cspace> space = std::make_shared<mzlib::cspace>();
  
};

// Tests

TEST_F(test_space, set_gravitational_constant)
{
    space->set_gravitational_constant(0.5);
    ASSERT_DOUBLE_EQ(0.5, space->get_gravitational_constant());
}

TEST_F(test_space, big_ben_force_on_empire_state_building)
{
    mzlib::cbody big_ben;
    big_ben.set_mass(10e8_kg); // 10e8 kg
    
    mzlib::cbody empire_state_building;
    empire_state_building.set_location({0,5000.0_km}); // 5000 km
    empire_state_building.set_mass(10e9_kg); // 10e9 kg
    
    space->add_body(big_ben);
	space->add_body(empire_state_building);
    space->calculate_forces();
    
    mzlib::math::cvector2d f_empire_state_building = empire_state_building.get_binded_data().get_force();
    mzlib::math::cvector2d f_big_ben = big_ben.get_binded_data().get_force();
    
    ASSERT_EQ(f_empire_state_building, -f_big_ben);
    ASSERT_NEAR(f_big_ben.length(), 2.67e-7, 0.01); // 2.67e-7 +- 0.01
}

TEST_F(test_space, sun_force_on_earth)
{
    mzlib::cbody sun;
    sun.get_binded_data().set_name("sun");
    sun.set_mass(mzlib::consts::sun_mass); // 1.99e30
    
    mzlib::cbody earth;
    earth.set_location({0,mzlib::consts::earth_distance_sun_average});
    earth.set_mass(mzlib::consts::earth_mass);
    earth.get_binded_data().set_name("earth");
    
    space->add_body(sun);
	space->add_body(earth);
    space->calculate_forces();
    
    mzlib::math::cvector2d f_sun = space->find_body(sun)->get_binded_data().get_force();
    mzlib::math::cvector2d f_earth = space->find_body(earth)->get_binded_data().get_force();
    
    ASSERT_EQ(f_earth, -f_sun);
    ASSERT_NEAR(f_earth.length(), 3.53e+22, 0.01e+22);
}

TEST_F(test_space, long_earth_around_the_sun)
{
    mzlib::cbody sun;
    sun.set_mass(1.989e30);
    
    mzlib::cbody earth;
    mzlib::math::cvector2d earth_location_start = {0,mzlib::consts::earth_distance_sun_aphelion};
    earth.set_location(earth_location_start);
    earth.set_mass(mzlib::consts::earth_mass);
    earth.get_binded_data().set_velocity({mzlib::consts::earth_speed_aphelion,0});
    
    space->add_body(sun);
	space->add_body(earth);
    space->forward_time(0.25_julian_year, 10.0_s);                       
    
    double distance_from_sun = earth.get_location().distance_to(sun.get_location());
    ASSERT_NEAR(distance_from_sun, mzlib::consts::earth_distance_sun_perihelion, 
        mzlib::consts::earth_distance_sun_perihelion*0.05); // should be less then 5 percent error
    
    space->forward_time(0.75_julian_year, 10.0_s);
    
    mzlib::math::cvector2d earth_location_year_later = earth.get_location();
    double location_diff = earth_location_year_later.distance_to(earth_location_start);
    
    ASSERT_NEAR(
        mzlib::consts::earth_orbit_length-location_diff, 
        mzlib::consts::earth_orbit_length, 
        mzlib::consts::earth_orbit_length*0.0006); // should be less then .06 percent error
}

}