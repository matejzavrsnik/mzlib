//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "units_strong_definitions.h"

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