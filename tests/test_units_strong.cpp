//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "../include/units_strong.h"
#include "gtest/gtest.h"

using namespace mzlib::units;
    
class fixture_units_strong : public ::testing::Test 
{

protected:

   fixture_units_strong() {}
   virtual ~fixture_units_strong() {}
   virtual void SetUp() {}
   virtual void TearDown() {}

   clength length1;
   clength length2;
  
};

TEST_F(fixture_units_strong, length_default_constructor) 
{
   clength l1;
   ASSERT_TRUE(l1.equals(0_nm_).within_epsilon(1_nm_));
}

TEST_F(fixture_units_strong, length_operator_equals) 
{
   length1 = 100_m_;
   ASSERT_TRUE(length1.equals(100_m_).within_epsilon(1_nm_));
}

TEST_F(fixture_units_strong, length_units_factors) 
{
   clength length_nm = 1_nm_;
   ASSERT_DOUBLE_EQ(length_nm / 1_m_, 1e-9);
   clength length_um = 1_um_;
   ASSERT_DOUBLE_EQ(length_um / 1_m_, 1e-6);
   clength length_mm = 1_mm_;
   ASSERT_DOUBLE_EQ(length_mm / 1_m_, 1e-3);
   clength length_cm = 1_cm_;
   ASSERT_DOUBLE_EQ(length_cm / 1_m_, 1e-2);
   clength length_dm = 1_dm_;
   ASSERT_DOUBLE_EQ(length_dm / 1_m_, 1e-1);
   clength length_dam = 1_dam_;
   ASSERT_DOUBLE_EQ(length_dam / 1_m_, 1e1);
   clength length_hm = 1_hm_;
   ASSERT_DOUBLE_EQ(length_hm / 1_m_, 1e2);
   clength length_km = 1_km_;
   ASSERT_DOUBLE_EQ(length_km / 1_m_, 1e3);
   clength length_Mm = 1_Mm_;
   ASSERT_DOUBLE_EQ(length_Mm / 1_m_, 1e6);
   clength length_Gm = 1_Gm_;
   ASSERT_DOUBLE_EQ(length_Gm / 1_m_, 1e9);
   clength length_Tm = 1_Tm_;
   ASSERT_DOUBLE_EQ(length_Tm / 1_m_, 1e12);
   clength length_inch = 1_inch_;
   ASSERT_DOUBLE_EQ(length_inch / 1_m_, 0.0254);
   clength length_foot = 1_foot_;
   ASSERT_DOUBLE_EQ(length_foot / 1_m_, 0.3048);
   clength length_feet = 1_feet_;
   ASSERT_DOUBLE_EQ(length_feet / 1_m_, 0.3048);
   clength length_yard = 1_yard_; 
   ASSERT_DOUBLE_EQ(length_yard / 1_m_, 0.9144);
   clength length_mile = 1_mile_; 
   ASSERT_DOUBLE_EQ(length_mile / 1_m_, 1609.344);
   clength length_nautical_mile = 1_nautical_mile_;
   ASSERT_DOUBLE_EQ(length_nautical_mile / 1_m_, 1853.184);
   clength length_ly = 1_ly_; // light year
   ASSERT_DOUBLE_EQ(length_ly / 1_m_, 9.4605284e15);
   clength length_au = 1_au_; // astronomical unit
   ASSERT_DOUBLE_EQ(length_au / 1_m_, 1.49597871e11);
}

TEST_F(fixture_units_strong, length_operator_plus) 
{
   length1 = 1_km_;
   length1 = length1 + 1_km_;
   ASSERT_TRUE(length1.equals(2_km_).within_epsilon(1_nm_));
   length1 += 1_km_;
   ASSERT_TRUE(length1.equals(3_km_).within_epsilon(1_nm_));
}

TEST_F(fixture_units_strong, length_operator_minus) 
{
   length1 = 3_km_;
   length1 = length1 - 1_km_;
   ASSERT_TRUE(length1.equals(2_km_).within_epsilon(1_nm_));
   length1 -= 1_km_;
   ASSERT_TRUE(length1.equals(1_km_).within_epsilon(1_nm_));
}

TEST_F(fixture_units_strong, length_operator_divide) 
{
   double ratio;
   length1 = 6_km_;
   ratio = length1 / 3_km_;
   ASSERT_DOUBLE_EQ(ratio, 2);
}

TEST_F(fixture_units_strong, length_operator_divide_by_unitless) 
{
   length1 = 6_km_;
   length1 = length1 / 3;
   ASSERT_TRUE(length1.equals(2_km_).within_epsilon(1_nm_));
   length1 /= 2;
   ASSERT_TRUE(length1.equals(1_km_).within_epsilon(1_nm_));
}

TEST_F(fixture_units_strong, length_operator_multiply) 
{
   length1 = 6_km_;
   carea area = length1 * 3_km_;
   ASSERT_TRUE(area.equals(18_km2_).within_epsilon(1_mm2_));
}

TEST_F(fixture_units_strong, length_operator_multiply_with_unitless) 
{
   length1 = 6_km_;
   length1 = length1 * 3;
   ASSERT_TRUE(length1.equals(18_km_).within_epsilon(1_nm_));
   length1 *= 2;
   ASSERT_TRUE(length1.equals(36_km_).within_epsilon(1_nm_));
}

TEST_F(fixture_units_strong, transform_from_length_area) 
{
   carea area = 5_km_ * 4_km_;
   ASSERT_TRUE(area.equals(20_km2_).within_epsilon(1_mm2_));
   length1 = area / 2_km_;
   ASSERT_TRUE(length1.equals(10_km_).within_epsilon(1_mm_));
}

TEST_F(fixture_units_strong, transforms_time_length_speed) 
{
   cspeed speed = 100_km_ / 100_h_;
   ASSERT_TRUE(speed.equals(1_km_per_h_).within_epsilon(1_m_per_s_));
   length1 = speed * 100_h_;
   ASSERT_TRUE(length1.equals(100_km_).within_epsilon(1_nm_));
   cltime time = 100_km_ / speed;
   ASSERT_TRUE(time.equals(100_h_).within_epsilon(1_ns_));
}
