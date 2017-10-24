//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_LAWS_CONSTANT_LINEAR_ACCELERATION_H
#define	MZLIB_LAWS_CONSTANT_LINEAR_ACCELERATION_H

#include <optional>

#include "../nature/mass_centre.h"

namespace mzlib {
namespace law {

template<class VectorT>
class constant_linear_acceleration
{
   
public:
      
   std::optional<VectorT> v_0;   
   std::optional<VectorT> v_f;
   std::optional<VectorT> r_0;   
   std::optional<VectorT> r_f;
   std::optional<VectorT> a;
   std::optional<double>  t;
   
   void solve_for_final_velocity()
   {
      v_f = v_0.value() + a.value() * t.value();
   }
   
   void solve_for_initial_velocity()
   {
      if ( v_f.has_value() ) {
         v_0 = v_f.value() - a.value() * t.value();
      }
      else if ( r_f.has_value() ) {
         v_0 = ( r_f.value() - r_0.value() ) / t.value() - 0.5 * a.value() * t.value();
      }
   }

   void solve_for_acceleration()
   {
      if ( v_f.has_value() ) {
         a = ( v_f.value() - v_0.value() ) / t.value();
      }
      else if ( r_f.has_value() ) {
         a = ( 2 / ( t.value() * t.value() ) ) * ( r_f.value() - r_0.value() - v_0.value() * t.value() );
      }
   }

   void solve_for_time()
   {
      t = ( vector::length(v_f.value()) - vector::length(v_0.value()) ) / vector::length(a.value());
   }
   
   void solve_for_final_location()
   {
      r_f = r_0.value() + v_0.value() * t.value() + 0.5 * a.value() * t.value() * t.value();       
   }
};

using constant_linear_acceleration2d = constant_linear_acceleration<vector2d>;
using constant_linear_acceleration3d = constant_linear_acceleration<vector3d>;

} } // namespace

#endif /* MZLIB_LAWS_CONSTANT_LINEAR_ACCELERATION_H */

#ifdef MZLIB_LAWS_CONSTANT_LINEAR_ACCELERATION_TESTS_H
#undef MZLIB_LAWS_CONSTANT_LINEAR_ACCELERATION_TESTS_H

#include "../nature/units.h"
using namespace mzlib::units;

TEST(constant_linear_acceleration, solve_for_final_velocity)
{
   mzlib::law::constant_linear_acceleration2d acc;
   acc.v_0 = mzlib::unit_vector2d * 7.53_m_per_s;
   acc.a = mzlib::unit_vector2d * 1.02_m_per_s2;
   acc.t = 9.83_s;
   acc.solve_for_final_velocity();
   
   auto direction = mzlib::law::vector::normalise(acc.v_f.value());
   auto size = mzlib::law::vector::length(acc.v_f.value());
   
   ASSERT_TRUE(mzlib::dbl(size).equals(17.5566L));
   ASSERT_TRUE(direction == mzlib::unit_vector2d);
}

TEST(constant_linear_acceleration, solve_for_initial_velocity_given_final_velocity)
{
   mzlib::law::constant_linear_acceleration2d acc;
   acc.v_f = mzlib::unit_vector2d * 33.49_m_per_s;
   acc.a = mzlib::unit_vector2d * 3.22_m_per_s2;
   acc.t = 2.57_s;
   acc.solve_for_initial_velocity();
   
   auto direction = mzlib::law::vector::normalise(acc.v_0.value());
   auto size = mzlib::law::vector::length(acc.v_0.value());
   
   ASSERT_TRUE(mzlib::dbl(size).equals(25.214600000000001L));
   ASSERT_TRUE(direction == mzlib::unit_vector2d);
}

TEST(constant_linear_acceleration, solve_for_initial_velocity_given_location)
{
   mzlib::law::constant_linear_acceleration2d acc;
   acc.r_f = mzlib::unit_vector2d * 9.13_m;
   acc.r_0 = mzlib::vector2d({1,1});
   acc.a = -mzlib::unit_vector2d * 0.21_m_per_s2;
   acc.t = 3.90_s;
   acc.solve_for_initial_velocity();
   
   auto direction = mzlib::law::vector::normalise(acc.v_0.value());
   auto size = mzlib::law::vector::length(acc.v_0.value());
   
   ASSERT_TRUE(mzlib::dbl(size).equals(2.3879067788786936L));
   ASSERT_TRUE(direction == mzlib::unit_vector2d);
}

TEST(constant_linear_acceleration, solve_for_acceleration_given_velocities)
{
   mzlib::law::constant_linear_acceleration2d acc;
   acc.v_0 = mzlib::unit_vector2d * 26.71_m_per_s;
   acc.v_f = mzlib::unit_vector2d * 48.95_m_per_s;
   acc.t = 8.66_s;
   acc.solve_for_acceleration();
   
   auto direction = mzlib::law::vector::normalise(acc.a.value());
   auto size = mzlib::law::vector::length(acc.a.value());
   
   ASSERT_TRUE(mzlib::dbl(size).equals(2.5681293302540422L));
   ASSERT_TRUE(direction == mzlib::unit_vector2d);
}

TEST(constant_linear_acceleration, solve_for_acceleration_given_location)
{
   mzlib::law::constant_linear_acceleration2d acc;
   acc.v_0 = -mzlib::unit_vector2d * 3.57_m_per_s;
   acc.r_0 = mzlib::vector2d({1,1});
   acc.r_f = mzlib::unit_vector2d * 6.02_m;
   acc.t = 9.13_s;
   acc.solve_for_acceleration();
   
   auto direction = mzlib::law::vector::normalise(acc.a.value());
   auto size = mzlib::law::vector::length(acc.a.value());
   
   ASSERT_TRUE(mzlib::dbl(size).equals(0.89254486281584111L));
   ASSERT_TRUE(direction == mzlib::unit_vector2d);
}

TEST(constant_linear_acceleration, solve_for_time_given_velocities)
{
   mzlib::law::constant_linear_acceleration2d acc;
   acc.a = mzlib::unit_vector2d * 8.17_m_per_s2;
   acc.v_0 = mzlib::unit_vector2d * 24.11_m_per_s;
   acc.v_f = mzlib::unit_vector2d * 44.00_m_per_s;
   acc.solve_for_time();
   
   auto size = acc.t.value();
   
   ASSERT_TRUE(mzlib::dbl(size).equals(2.4345165238678086L));
}

TEST(constant_linear_acceleration, solve_for_final_location)
{
   mzlib::law::constant_linear_acceleration2d acc;
   acc.v_0 = mzlib::unit_vector2d * 3.48_m_per_s;
   acc.a = mzlib::unit_vector2d * 1.51_m_per_s2;
   acc.t = 2.27_s;
   acc.r_0 = mzlib::vector2d{1.1,2.2};
   acc.solve_for_final_location();
   
   auto direction = acc.r_f.value();
   
   ASSERT_TRUE(direction == mzlib::vector2d({9.4368168809072515L,10.536816880907253L}));
}


#endif
