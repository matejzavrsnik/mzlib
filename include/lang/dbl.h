//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_DBL_H
#define	MZLIB_DBL_H

#include <cmath>
#include <limits>

namespace mzlib {

// to compare doubles for equality
class dbl
{

private:

   double m_val;
   double m_compared_to;
        
public:
        
   explicit dbl (double val) : 
      m_val(val),
      m_compared_to(val)
   {
   }
        
   dbl& equals (double val) 
   {
      m_compared_to = val;
      return *this;
   }
        
   operator bool () const 
   {
      const double delta = std::abs(m_val-m_compared_to);
      const double magnitude_candidate = std::abs(m_val+m_compared_to);
      const double magnitude = (magnitude_candidate >= 1 ? magnitude_candidate : 1);
      const int units_in_last_place = 4;
      const double allowed_delta = std::numeric_limits<double>::epsilon() * magnitude * units_in_last_place;
      return delta < allowed_delta || delta < std::numeric_limits<double>::min();
   }
        
   bool within_epsilon (double eps = 1e-10) const 
   {
      return std::abs(m_val-m_compared_to) <= eps;
   }

};

} // namespace

#endif	/* MZLIB_DBL_H */

#ifdef MZLIB_DBL_TESTS_H
#undef MZLIB_DBL_TESTS_H

inline double allowed_double_delta(double val, int ulp)
{ 
   double use_val = std::abs(val);
   if(use_val<1) use_val = 1;
   return std::numeric_limits<double>::epsilon() * use_val * ulp;
}


TEST(dbl, compare_equal_doubles_for_equality) 
{
   ASSERT_TRUE(mzlib::dbl(13.3L).equals(13.3L));
}

TEST(dbl, compare_different_doubles_for_equality) 
{
   ASSERT_FALSE(mzlib::dbl(13.3L).equals(13.2L));
}

TEST(dbl, compare_ranges_of_nearly_equals_doubles_for_equality) {
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

TEST(dbl, compare_equal_doubles_for_equality_within_epsilon) 
{
   ASSERT_TRUE(mzlib::dbl(13.3).equals(13.2).within_epsilon(0.2));
}

TEST(dbl, compare_different_doubles_for_equality_within_epsilon) 
{
   ASSERT_FALSE(mzlib::dbl(13.3).equals(13.2).within_epsilon(0.01));
}

#endif // MZLIB_DBL_TESTS_H
