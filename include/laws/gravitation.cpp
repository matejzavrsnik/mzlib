//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "gravitation.h"

#include "../nature/units.h"
using namespace mzlib::units;

TEST(gravitation, solve_for_force)
{
   mzlib::law::gravitation2d gra;
   gra.m_1 = mzlib::mass_centre2d{
      mzlib::unit_vector2d * 0, 
      mzlib::consts::earth_mass };
   gra.m_2 = mzlib::mass_centre2d{
      mzlib::unit_vector2d * mzlib::consts::moon_distance_earth, 
      mzlib::consts::moon_mass };
   gra.solve_for_force();
   
   auto direction = mzlib::law::vector::normalise(gra.f_1.value());
   auto size = mzlib::law::vector::length(gra.f_1.value());
   
   ASSERT_TRUE(mzlib::dbl(size).equals(1.9820850603183325e20_N));
   ASSERT_TRUE(direction == mzlib::unit_vector2d);
}

TEST(gravitation, solve_for_fun_force)
{
   mzlib::law::gravitation2d gra;
   gra.m_1 = mzlib::mass_centre2d{
      mzlib::unit_vector2d * 0, 
      mzlib::consts::earth_mass };
   gra.m_2 = mzlib::mass_centre2d{
      mzlib::unit_vector2d * mzlib::consts::moon_distance_earth, 
      mzlib::consts::moon_mass };
   gra.solve_for_fun_force();
   
   auto direction = mzlib::law::vector::normalise(gra.f_1.value());
   auto size = mzlib::law::vector::length(gra.f_1.value());
   
   ASSERT_TRUE(mzlib::dbl(size).equals(7.6191349718636712e28_N));
   ASSERT_TRUE(direction == mzlib::unit_vector2d);
}