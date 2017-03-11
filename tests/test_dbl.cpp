//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "../include/lang/dbl.h"
#include "gtest/gtest.h"

class fixture_dbl : public ::testing::Test 
{

protected:
   
   fixture_dbl () {}
   virtual ~fixture_dbl () {}
   virtual void SetUp() {}
   virtual void TearDown() {}
  
   double allowed_double_delta(double val, int ulp)
   { 
      double use_val = std::abs(val);
      if(use_val<1) use_val = 1;
      return std::numeric_limits<double>::epsilon() * use_val * ulp;
   }
   
};

TEST_F(fixture_dbl, compare_equal_doubles_for_equality) 
{
   ASSERT_TRUE(mzlib::dbl(13.3L).equals(13.3L));
}

TEST_F(fixture_dbl, compare_different_doubles_for_equality) 
{
   ASSERT_FALSE(mzlib::dbl(13.3L).equals(13.2L));
}

TEST_F(fixture_dbl, compare_ranges_of_nearly_equals_doubles_for_equality) {
   // allowed difference is 4 units in last place
   const int ulp = 4;
   // compare all values in epsilon vicinity of centre values
   double centre_values[] = { 
      std::numeric_limits<double>::min(), // smallest possible
      -1e300L, // small, but far from min
      -1e10L, // almost zero on negative side, but far from zero
      -1e-321L, // compare to nearly zero on negative side
      -0L, // compare to negative zero
      0L, // around zero
      1e-321L, // compare to nearly zero on positive side
      1e-10L, // almost zero on positive side, but far from zero
      1L, // one
      13.3L, // something "normal"
      1e300, // large, but still far from max
      std::numeric_limits<double>::max()
   }; 
   
   // epsilon vicinity is 1000 representable values around specific centre value
   const int count_max = 1000;
   // for each such number
   for(double centre_value : centre_values) {
      double value=centre_value;
      // rewind half-way back to the negative
      for(int count=0; count<(count_max/2); ++count) {
         value = std::nextafter(value, value-1);
      }
      // run count_max comparisons to the positive
      for(int count=0; count<count_max; value = std::nextafter(value, value+1), ++count) {
         const double allowed_difference = allowed_double_delta(centre_value+value, ulp);
         const double difference = std::abs(value-centre_value);
         if(difference <= allowed_difference) {
            ASSERT_TRUE(mzlib::dbl(value).equals(centre_value)) 
               << "Comparing " << value << " to " << centre_value << 
               " failed, but they are within " << ulp << " ulp.";
         }
         else {
            ASSERT_FALSE(mzlib::dbl(value).equals(centre_value)) 
               << "Comparing " << value << " to " << centre_value << 
               " succeeded, but they are " << ulp << " ulp appart.";
         }
      }
   }
}

TEST_F(fixture_dbl, compare_equal_doubles_for_equality_within_epsilon) 
{
   ASSERT_TRUE(mzlib::dbl(13.3).equals(13.2).within_epsilon(0.2));
}

TEST_F(fixture_dbl, compare_different_doubles_for_equality_within_epsilon) 
{
   ASSERT_FALSE(mzlib::dbl(13.3).equals(13.2).within_epsilon(0.01));
}
