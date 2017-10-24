//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_UNITS_STRONG_DEFINITIONS_H
#define MZLIB_UNITS_STRONG_DEFINITIONS_H

#include "units_strong_foundation.h"

namespace mzlib {
   
// Necessary forward declarations; because units are dependent on each other.
// Example: length * length = area, area / length = length. Which one to define first?
class area; class speed; class time_unit; class length;    
    
// Length
MZ_QUANTITY_DEFINITION_START(length, m)
   friend area operator* (const length& lhs, const length& rhs);
   friend length operator/ (const area& lhs, const length& rhs);
   friend speed operator/ (const length& lhs, const time_unit& rhs);
   friend time_unit operator/ (const length& lhs, const speed& rhs);
MZ_QUANTITY_DEFINITION_END(length, m)
// SI units
MZ_UNIT_DEFINITION(length, nm,  1e-9, m)
MZ_UNIT_DEFINITION(length, um,  1e-6, m)
MZ_UNIT_DEFINITION(length, mm,  1e-3, m)
MZ_UNIT_DEFINITION(length, cm,  1e-2, m)
MZ_UNIT_DEFINITION(length, dm,  1e-1, m)
MZ_UNIT_DEFINITION(length, dam, 1e1,  m)
MZ_UNIT_DEFINITION(length, hm,  1e2,  m)
MZ_UNIT_DEFINITION(length, km,  1e3,  m)
MZ_UNIT_DEFINITION(length, Mm,  1e6,  m)
MZ_UNIT_DEFINITION(length, Gm,  1e9,  m)
MZ_UNIT_DEFINITION(length, Tm,  1e12, m)
// non-SI units
MZ_UNIT_DEFINITION(length, inch, 0.0254, m)
MZ_UNIT_DEFINITION(length, foot, 0.3048, m)
MZ_UNIT_DEFINITION(length, feet, 0.3048, m)
MZ_UNIT_DEFINITION(length, yard, 0.9144, m)
MZ_UNIT_DEFINITION(length, mile, 1609.344, m)
MZ_UNIT_DEFINITION(length, nautical_mile, 1853.184, m)
MZ_UNIT_DEFINITION(length, ly,  9.4605284e15, m) // light year
MZ_UNIT_DEFINITION(length, au,  1.49597871e11, m) // astronomical unit
        
// Area 
MZ_QUANTITY_DEFINITION_START(area, m2)
   friend length operator/ (const area& lhs, const length& rhs);
MZ_QUANTITY_DEFINITION_END(area, m2)
// SI units
MZ_UNIT_DEFINITION(area, mm2, 1e-6, m2)
MZ_UNIT_DEFINITION(area, cm2, 1e-4, m2)
MZ_UNIT_DEFINITION(area, dm2, 1e-2, m2)
MZ_UNIT_DEFINITION(area, km2, 1e6,  m2)
// non-SI units
MZ_UNIT_DEFINITION(area, are, 1e2,  m2)
MZ_UNIT_DEFINITION(area, ha,  1e4,  m2)
MZ_UNIT_DEFINITION(area, acre, 4046.86, m2)
    
// Speed 
MZ_QUANTITY_DEFINITION_START(speed, m_per_s)
   friend length operator* (const speed& lhs, const time_unit& rhs);
   friend time_unit operator/ (const length& lhs, const speed& rhs);
MZ_QUANTITY_DEFINITION_END(speed, m_per_s)
// SI units
MZ_UNIT_DEFINITION(speed, km_per_s, 1e-3, m_per_s)
MZ_UNIT_DEFINITION(speed, km_per_h, 0.2777, m_per_s)
  
// Mass
MZ_QUANTITY_DEFINITION_START(mass, kg)
MZ_QUANTITY_DEFINITION_END(mass, kg)
// SI units
MZ_UNIT_DEFINITION(mass, ug,  1e-9, kg)
MZ_UNIT_DEFINITION(mass, mg,  1e-6, kg)    
MZ_UNIT_DEFINITION(mass, g,   1e-3, kg)
MZ_UNIT_DEFINITION(mass, ton, 1e3,  kg)
// non-SI units
MZ_UNIT_DEFINITION(mass, stone, 6.35029, kg)
MZ_UNIT_DEFINITION(mass, pound, 0.453592, kg)
MZ_UNIT_DEFINITION(mass, ounce, 0.0283495, kg) 
   
// Time
MZ_QUANTITY_DEFINITION_START(time_unit, s)
   friend speed operator/ (const length& lhs, const time_unit& rhs);
   friend length operator* (const speed& lhs, const time_unit& rhs);
MZ_QUANTITY_DEFINITION_END(time_unit, s)
// SI units
MZ_UNIT_DEFINITION(time_unit, ns,  1e-9, s)
MZ_UNIT_DEFINITION(time_unit, us,  1e-6, s)    
MZ_UNIT_DEFINITION(time_unit, ms,  1e-3, s)
MZ_UNIT_DEFINITION(time_unit, min, 60,   s)
MZ_UNIT_DEFINITION(time_unit, h,   3600, s)
MZ_UNIT_DEFINITION(time_unit, day, 86400,s)
MZ_UNIT_DEFINITION(time_unit, week, 604800, s)
MZ_UNIT_DEFINITION(time_unit, month, 2.63e+6, s)
MZ_UNIT_DEFINITION(time_unit, year,  3.156e+7, s)
MZ_UNIT_DEFINITION(time_unit, decade, 3.156e+8, s)
MZ_UNIT_DEFINITION(time_unit, century, 3.156e+9, s)
    
// Operations that change quantity (Can there be others except multiplication and division?)
  
inline area operator* (const length& lhs, const length& rhs) 
{
   return operator "" _m2_(lhs.value * rhs.value);
}

inline speed operator/ (const length& lhs, const time_unit&  rhs) 
{
   return operator "" _m_per_s_(lhs.value / rhs.value);
}

inline length operator/ (const area& lhs, const length& rhs)
{
   return operator "" _m_(lhs.value / rhs.value);
}

inline length operator* (const speed& lhs, const time_unit& rhs)
{
   return operator "" _m_(lhs.value * rhs.value);
}

inline time_unit operator/ (const length& lhs, const speed& rhs)
{
   return operator "" _s_(lhs.value / rhs.value);
}

// Don't undef, user might want to create own
//#undef MZ_QUANTITY_DEFINITION_START
//#undef MZ_QUANTITY_DEFINITION_END
//#undef MZ_UNIT_DEFINITION

} // namespace

#endif // MZLIB_UNITS_STRONG_DEFINITIONS_H

#ifdef MZLIB_UNITS_STRONG_DEFINITIONS_TESTS_H

namespace mzlib {

TEST(fixture_units_strong, length_default_constructor) 
{
   length l1;
   ASSERT_TRUE(l1.equals(0_nm_).within_epsilon(1_nm_));
}

TEST(fixture_units_strong, length_operator_equals) 
{
   length l = 100_m_;
   ASSERT_TRUE(l.equals(100_m_).within_epsilon(1_nm_));
}

TEST(fixture_units_strong, length_units_factors) 
{
   length length_nm = 1_nm_;
   ASSERT_DOUBLE_EQ(length_nm / 1_m_, 1e-9);
   length length_um = 1_um_;
   ASSERT_DOUBLE_EQ(length_um / 1_m_, 1e-6);
   length length_mm = 1_mm_;
   ASSERT_DOUBLE_EQ(length_mm / 1_m_, 1e-3);
   length length_cm = 1_cm_;
   ASSERT_DOUBLE_EQ(length_cm / 1_m_, 1e-2);
   length length_dm = 1_dm_;
   ASSERT_DOUBLE_EQ(length_dm / 1_m_, 1e-1);
   length length_dam = 1_dam_;
   ASSERT_DOUBLE_EQ(length_dam / 1_m_, 1e1);
   length length_hm = 1_hm_;
   ASSERT_DOUBLE_EQ(length_hm / 1_m_, 1e2);
   length length_km = 1_km_;
   ASSERT_DOUBLE_EQ(length_km / 1_m_, 1e3);
   length length_Mm = 1_Mm_;
   ASSERT_DOUBLE_EQ(length_Mm / 1_m_, 1e6);
   length length_Gm = 1_Gm_;
   ASSERT_DOUBLE_EQ(length_Gm / 1_m_, 1e9);
   length length_Tm = 1_Tm_;
   ASSERT_DOUBLE_EQ(length_Tm / 1_m_, 1e12);
   length length_inch = 1_inch_;
   ASSERT_DOUBLE_EQ(length_inch / 1_m_, 0.0254);
   length length_foot = 1_foot_;
   ASSERT_DOUBLE_EQ(length_foot / 1_m_, 0.3048);
   length length_feet = 1_feet_;
   ASSERT_DOUBLE_EQ(length_feet / 1_m_, 0.3048);
   length length_yard = 1_yard_; 
   ASSERT_DOUBLE_EQ(length_yard / 1_m_, 0.9144);
   length length_mile = 1_mile_; 
   ASSERT_DOUBLE_EQ(length_mile / 1_m_, 1609.344);
   length length_nautical_mile = 1_nautical_mile_;
   ASSERT_DOUBLE_EQ(length_nautical_mile / 1_m_, 1853.184);
   length length_ly = 1_ly_; // light year
   ASSERT_DOUBLE_EQ(length_ly / 1_m_, 9.4605284e15);
   length length_au = 1_au_; // astronomical unit
   ASSERT_DOUBLE_EQ(length_au / 1_m_, 1.49597871e11);
}

TEST(fixture_units_strong, length_operator_plus) 
{
   length l = 1_km_;
   l = l + 1_km_;
   ASSERT_TRUE(l.equals(2_km_).within_epsilon(1_nm_));
   l += 1_km_;
   ASSERT_TRUE(l.equals(3_km_).within_epsilon(1_nm_));
}

TEST(fixture_units_strong, length_operator_minus) 
{
   length l = 3_km_;
   l = l - 1_km_;
   ASSERT_TRUE(l.equals(2_km_).within_epsilon(1_nm_));
   l -= 1_km_;
   ASSERT_TRUE(l.equals(1_km_).within_epsilon(1_nm_));
}

TEST(fixture_units_strong, length_operator_divide) 
{
   double ratio;
   length l = 6_km_;
   ratio = l / 3_km_;
   ASSERT_DOUBLE_EQ(ratio, 2);
}

TEST(fixture_units_strong, length_operator_divide_by_unitless) 
{
   length l = 6_km_;
   l = l / 3;
   ASSERT_TRUE(l.equals(2_km_).within_epsilon(1_nm_));
   l /= 2;
   ASSERT_TRUE(l.equals(1_km_).within_epsilon(1_nm_));
}

TEST(fixture_units_strong, length_operator_multiply) 
{
   length l = 6_km_;
   area area = l * 3_km_;
   ASSERT_TRUE(area.equals(18_km2_).within_epsilon(1_mm2_));
}

TEST(fixture_units_strong, length_operator_multiply_with_unitless) 
{
   length l = 6_km_;
   l = l * 3;
   ASSERT_TRUE(l.equals(18_km_).within_epsilon(1_nm_));
   l *= 2;
   ASSERT_TRUE(l.equals(36_km_).within_epsilon(1_nm_));
}

TEST(fixture_units_strong, transform_from_length_area) 
{
   area area = 5_km_ * 4_km_;
   ASSERT_TRUE(area.equals(20_km2_).within_epsilon(1_mm2_));
   length l = area / 2_km_;
   ASSERT_TRUE(l.equals(10_km_).within_epsilon(1_mm_));
}

TEST(fixture_units_strong, transforms_time_length_speed) 
{
   speed speed = 100_km_ / 100_h_;
   ASSERT_TRUE(speed.equals(1_km_per_h_).within_epsilon(1_m_per_s_));
   length l = speed * 100_h_;
   ASSERT_TRUE(l.equals(100_km_).within_epsilon(1_nm_));
   time_unit t = 100_km_ / speed;
   ASSERT_TRUE(t.equals(100_h_).within_epsilon(1_ns_));
}

} // namespace

#endif // MZLIB_UNITS_STRONG_DEFINITIONS_TESTS_H

