//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_LAWS_ACCELERATION_H
#define	MZLIB_LAWS_ACCELERATION_H

#include <optional>

#include "../nature/vector.h"

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
      m = vector_length(f.value()) / vector_length(a.value());
   }
   
};

using acceleration2d = acceleration<vector2d>;
using acceleration3d = acceleration<vector3d>;

} } // namespace

#endif /* MZLIB_LAWS_ACCELERATION_H */

#ifdef MZLIB_BUILDING_TESTS

#ifndef MZLIB_LAWS_ACCELERATION_TESTS_H
#define MZLIB_LAWS_ACCELERATION_TESTS_H

TEST(acceleration, solve_for_force) 
{
   mzlib::law::acceleration2d acc;
   acc.m = 14.17_kg;
   acc.a = mzlib::vector2d::unit * 14.14_m_per_s2;
   acc.solve_for_force();
   
   auto direction = normalise(acc.f.value());
   auto size = vector_length(acc.f.value());
   
   ASSERT_TRUE(mzlib::dbl(size).equals(200.3638L));
   ASSERT_TRUE(direction == mzlib::vector2d::unit);
}

TEST(acceleration, solve_for_force_missing_argument) 
{
   mzlib::law::acceleration2d acc;
   //acc.m = 14.17_kg;
   acc.a = mzlib::vector2d::unit * 14.14_m_per_s2;

   ASSERT_THROW(acc.solve_for_force(), std::bad_optional_access);
}

TEST(acceleration, solve_for_acceleration) 
{
   mzlib::law::acceleration2d acc;
   acc.m = 17.23_kg;
   acc.f = mzlib::vector2d::unit * 10.52_N;
   acc.solve_for_acceleration();
   
   auto direction = normalise(acc.a.value());
   auto size = vector_length(acc.a.value());
   
   ASSERT_TRUE(mzlib::dbl(size).equals(0.61056297156123029L));
   ASSERT_TRUE(direction == mzlib::vector2d::unit);
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
   acc.f = mzlib::vector2d::unit * 16.66_N;
   acc.a = mzlib::vector2d::unit * 18.34_m_per_s2;
   acc.solve_for_mass();
   
   auto size = acc.m.value();
   
   ASSERT_TRUE(mzlib::dbl(size).equals(0.90839694656488568L));
}

TEST(acceleration, solve_for_mass_missing_argument) 
{
   mzlib::law::acceleration2d acc;
   //acc.f = unit_vector2d * 16.66_N;
   acc.a = mzlib::vector2d::unit * 18.34_m_per_s2;
   
   ASSERT_THROW(acc.solve_for_mass(), std::bad_optional_access);
}

#endif // MZLIB_LAWS_ACCELERATION_TESTS_H

#endif // MZLIB_BUILDING_TESTS
