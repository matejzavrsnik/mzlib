//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_LAWS_ACCELERATION_H
#define	MZLIB_LAWS_ACCELERATION_H

#include "../nature/vector.h"
#include <optional>

namespace mzlib {
namespace law {
   
// Newton's second law of motion
template<class VectorT>
class acceleration
{
   
public:
      
   std::optional<VectorT> f;   
   std::optional<VectorT> a;
   std::optional<double>  m;
   
   void solve_for_force()
   {
      f = m.value() * a.value();
   }
   
   void solve_for_acceleration()
   {
      a = f.value() / m.value();
   }

   void solve_for_mass()
   {
      m = vector::length(f.value()) / vector::length(a.value());
   }
   
};

using acceleration2d = acceleration<vector2d>;
using acceleration3d = acceleration<vector3d>;

} } // namespace

#endif /* MZLIB_LAWS_ACCELERATION_H */

#ifdef MZLIB_LAWS_ACCELERATION_TESTS_H
#undef MZLIB_LAWS_ACCELERATION_TESTS_H

#include "../nature/units.h"
using namespace mzlib::units;

TEST(acceleration, solve_for_force) 
{
   mzlib::law::acceleration2d acc;
   acc.m = 14.17_kg;
   acc.a = mzlib::unit_vector2d * 14.14_m_per_s2;
   acc.solve_for_force();
   
   auto direction = mzlib::law::vector::normalise(acc.f.value());
   auto size = mzlib::law::vector::length(acc.f.value());
   
   ASSERT_TRUE(mzlib::dbl(size).equals(200.3638L));
   ASSERT_TRUE(direction == mzlib::unit_vector2d);
}

TEST(acceleration, solve_for_force_missing_argument) 
{
   mzlib::law::acceleration2d acc;
   //acc.m = 14.17_kg;
   acc.a = mzlib::unit_vector2d * 14.14_m_per_s2;

   ASSERT_THROW(acc.solve_for_force(), std::bad_optional_access);
}

TEST(acceleration, solve_for_acceleration) 
{
   mzlib::law::acceleration2d acc;
   acc.m = 17.23_kg;
   acc.f = mzlib::unit_vector2d * 10.52_N;
   acc.solve_for_acceleration();
   
   auto direction = mzlib::law::vector::normalise(acc.a.value());
   auto size = mzlib::law::vector::length(acc.a.value());
   
   ASSERT_TRUE(mzlib::dbl(size).equals(0.61056297156123029L));
   ASSERT_TRUE(direction == mzlib::unit_vector2d);
}

TEST(acceleration, solve_for_acceleration_missing_argument) 
{
   mzlib::law::acceleration2d acc;
   acc.m = 17.23_kg;
   //acc.f = unit_vector2d * 10.52_N;
   
   ASSERT_THROW(acc.solve_for_acceleration(), std::bad_optional_access);
}

TEST(acceleration, solve_for_mass) 
{
   mzlib::law::acceleration2d acc;
   acc.f = mzlib::unit_vector2d * 16.66_N;
   acc.a = mzlib::unit_vector2d * 18.34_m_per_s2;
   acc.solve_for_mass();
   
   auto size = acc.m.value();
   
   ASSERT_TRUE(mzlib::dbl(size).equals(0.90839694656488568L));
}

TEST(acceleration, solve_for_mass_missing_argument) 
{
   mzlib::law::acceleration2d acc;
   //acc.f = unit_vector2d * 16.66_N;
   acc.a = mzlib::unit_vector2d * 18.34_m_per_s2;
   
   ASSERT_THROW(acc.solve_for_mass(), std::bad_optional_access);
}


#endif
