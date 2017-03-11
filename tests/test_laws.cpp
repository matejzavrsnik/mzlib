//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "../include/laws/acceleration.h"
#include "../include/laws/constant_linear_acceleration.h"
#include "../include/laws/gravitation.h"
#include "../include/nature/units.h"
#include "../include/nature/consts.h"

#include "gtest/gtest.h"

using namespace mzlib::units;

// I included a handful of tests that test missing arguments, but I see no point
// in testing every single law and combination of missing arguments. The underlying
// coptional class does that in one place, and that one place is tested in coptional
// tests already. There is no point in repeating basically the same experiment.

class fixture_laws : public ::testing::Test 
{

protected:
   
   fixture_laws () {}
   virtual ~fixture_laws () {}
   virtual void SetUp() {}
   virtual void TearDown() {}
   
   mzlib::vector2d unit_vector2d = mzlib::vector2d{1,1}.normalise();
};

TEST_F(fixture_laws, acceleration2d_solve_for_force) 
{
   mzlib::law::acceleration2d acc;
   acc.m = 14.17_kg;
   acc.a = unit_vector2d * 14.14_m_per_s2;
   acc.solve_for_force();
   
   auto direction = acc.f.get().normalise();
   auto size = acc.f.get().length();
   
   ASSERT_TRUE(mzlib::dbl(size).equals(200.3638L));
   ASSERT_TRUE(direction == unit_vector2d);
}

TEST_F(fixture_laws, acceleration2d_solve_for_force_missing_argument) 
{
   mzlib::law::acceleration2d acc;
   //acc.m = 14.17_kg;
   acc.a = unit_vector2d * 14.14_m_per_s2;

   ASSERT_THROW(acc.solve_for_force(), mzlib::exception::not_set);
}

TEST_F(fixture_laws, acceleration2d_solve_for_acceleration) 
{
   mzlib::law::acceleration2d acc;
   acc.m = 17.23_kg;
   acc.f = unit_vector2d * 10.52_N;
   acc.solve_for_acceleration();
   
   auto direction = acc.a.get().normalise();
   auto size = acc.a.get().length();
   
   ASSERT_TRUE(mzlib::dbl(size).equals(0.61056297156123029L));
   ASSERT_TRUE(direction == unit_vector2d);
}

TEST_F(fixture_laws, acceleration2d_solve_for_acceleration_missing_argument) 
{
   mzlib::law::acceleration2d acc;
   acc.m = 17.23_kg;
   //acc.f = unit_vector2d * 10.52_N;
   
   ASSERT_THROW(acc.solve_for_acceleration(), mzlib::exception::not_set);
}

TEST_F(fixture_laws, acceleration2d_solve_for_mass) 
{
   mzlib::law::acceleration2d acc;
   acc.f = unit_vector2d * 16.66_N;
   acc.a = unit_vector2d * 18.34_m_per_s2;
   acc.solve_for_mass();
   
   auto size = acc.m.get();
   
   ASSERT_TRUE(mzlib::dbl(size).equals(0.90839694656488568L));
}

TEST_F(fixture_laws, acceleration2d_solve_for_mass_missing_argument) 
{
   mzlib::law::acceleration2d acc;
   //acc.f = unit_vector2d * 16.66_N;
   acc.a = unit_vector2d * 18.34_m_per_s2;
   
   ASSERT_THROW(acc.solve_for_mass(), mzlib::exception::not_set);
}

TEST_F(fixture_laws, cconstant_linear_acceleration_solve_for_final_velocity)
{
   mzlib::law::constant_linear_acceleration2d acc;
   acc.v_0 = unit_vector2d * 7.53_m_per_s;
   acc.a = unit_vector2d * 1.02_m_per_s2;
   acc.t = 9.83_s;
   acc.solve_for_final_velocity();
   
   auto direction = acc.v_f.get().normalise();
   auto size = acc.v_f.get().length();
   
   ASSERT_TRUE(mzlib::dbl(size).equals(17.5566L));
   ASSERT_TRUE(direction == unit_vector2d);
}

TEST_F(fixture_laws, cconstant_linear_acceleration_solve_for_initial_velocity_given_final_velocity)
{
   mzlib::law::constant_linear_acceleration2d acc;
   acc.v_f = unit_vector2d * 33.49_m_per_s;
   acc.a = unit_vector2d * 3.22_m_per_s2;
   acc.t = 2.57_s;
   acc.solve_for_initial_velocity();
   
   auto direction = acc.v_0.get().normalise();
   auto size = acc.v_0.get().length();
   
   ASSERT_TRUE(mzlib::dbl(size).equals(25.214600000000001L));
   ASSERT_TRUE(direction == unit_vector2d);
}

TEST_F(fixture_laws, cconstant_linear_acceleration_solve_for_initial_velocity_given_location)
{
   mzlib::law::constant_linear_acceleration2d acc;
   acc.r_f = unit_vector2d * 9.13_m;
   acc.r_0 = mzlib::vector2d({1,1});
   acc.a = -unit_vector2d * 0.21_m_per_s2;
   acc.t = 3.90_s;
   acc.solve_for_initial_velocity();
   
   auto direction = acc.v_0.get().normalise();
   auto size = acc.v_0.get().length();
   
   ASSERT_TRUE(mzlib::dbl(size).equals(2.3879067788786936L));
   ASSERT_TRUE(direction == unit_vector2d);
}

TEST_F(fixture_laws, cconstant_linear_acceleration_solve_for_acceleration_given_velocities)
{
   mzlib::law::constant_linear_acceleration2d acc;
   acc.v_0 = unit_vector2d * 26.71_m_per_s;
   acc.v_f = unit_vector2d * 48.95_m_per_s;
   acc.t = 8.66_s;
   acc.solve_for_acceleration();
   
   auto direction = acc.a.get().normalise();
   auto size = acc.a.get().length();
   
   ASSERT_TRUE(mzlib::dbl(size).equals(2.5681293302540422L));
   ASSERT_TRUE(direction == unit_vector2d);
}

TEST_F(fixture_laws, cconstant_linear_acceleration_solve_for_acceleration_given_location)
{
   mzlib::law::constant_linear_acceleration2d acc;
   acc.v_0 = -unit_vector2d * 3.57_m_per_s;
   acc.r_0 = mzlib::vector2d({1,1});
   acc.r_f = unit_vector2d * 6.02_m;
   acc.t = 9.13_s;
   acc.solve_for_acceleration();
   
   auto direction = acc.a.get().normalise();
   auto size = acc.a.get().length();
   
   ASSERT_TRUE(mzlib::dbl(size).equals(0.89254486281584111L));
   ASSERT_TRUE(direction == unit_vector2d);
}

TEST_F(fixture_laws, cconstant_linear_acceleration_solve_for_time_given_velocities)
{
   mzlib::law::constant_linear_acceleration2d acc;
   acc.a = unit_vector2d * 8.17_m_per_s2;
   acc.v_0 = unit_vector2d * 24.11_m_per_s;
   acc.v_f = unit_vector2d * 44.00_m_per_s;
   acc.solve_for_time();
   
   auto size = acc.t.get();
   
   ASSERT_TRUE(mzlib::dbl(size).equals(2.4345165238678086L));
}

TEST_F(fixture_laws, cconstant_linear_acceleration_solve_for_final_location)
{
   mzlib::law::constant_linear_acceleration2d acc;
   acc.v_0 = unit_vector2d * 3.48_m_per_s;
   acc.a = unit_vector2d * 1.51_m_per_s2;
   acc.t = 2.27_s;
   acc.r_0 = mzlib::vector2d{1.1,2.2};
   acc.solve_for_final_location();
   
   auto direction = acc.r_f.get();
   
   ASSERT_TRUE(direction == mzlib::vector2d({9.4368168809072515L,10.536816880907253L}));
}

TEST_F(fixture_laws, cgravitation_solve_for_force)
{
   mzlib::law::gravitation2d gra;
   gra.m_1 = mzlib::mass_centre2d{
      unit_vector2d * 0, 
      mzlib::consts::earth_mass };
   gra.m_2 = mzlib::mass_centre2d{
      unit_vector2d * mzlib::consts::moon_distance_earth, 
      mzlib::consts::moon_mass };
   gra.solve_for_force();
   
   auto direction = gra.f_1.get().normalise();
   auto size = gra.f_1.get().length();
   
   ASSERT_TRUE(mzlib::dbl(size).equals(1.9820850603183325e20_N));
   ASSERT_TRUE(direction == unit_vector2d);
}
