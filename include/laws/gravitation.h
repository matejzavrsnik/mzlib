//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_LAWS_GRAVITATION_H
#define	MZLIB_LAWS_GRAVITATION_H

#include <optional>

#include "../nature/mass_centre.h"
#include "../nature/consts.h"

namespace mzlib {
namespace law {
   
template<class VectorT>
class gravitation
{
   
public:
   
   std::optional<mass_centre<VectorT>> m_1; 
   std::optional<mass_centre<VectorT>> m_2; 
   std::optional<double> G = std::optional<double>(mzlib::consts::gravitational_constant);
   std::optional<VectorT> f_1;
   
   void solve_for_force ()
   {
      VectorT m1_force = {0};
      double sqare_distance = m_1.value().location.square_distance_to(m_2.value().location); 
      m1_force = -m_1.value().location.direction_to(m_2.value().location).normalise(); 
      m1_force *= m_1.value().mass * m_2.value().mass; // masses
      m1_force /= sqare_distance; // distance
      m1_force *= G.value(); // factor
      f_1 = m1_force;
   }
   
   // Because I noticed that if gravity is linearly proportional to distance,
   // games are more fun. Seems like people have limited ability to intuitively
   // grasp second order polynomials like in accelerated motion or gravity force.
   void solve_for_fun_force ()
   {
      VectorT m1_force = {0};
      // todo: what when the distance is zero?
      double sqare_distance = m_1.value().location.square_distance_to(m_2.value().location); 
      m1_force = -m_1.value().location.direction_to(m_2.value().location).normalise(); 
      m1_force *= m_1.value().mass * m_2.value().mass; // masses
      m1_force /= std::sqrt(sqare_distance); // distance
      m1_force *= G.value(); // factor
      f_1 = m1_force;
   }
   
};

using gravitation2d = gravitation<vector2d>;
using gravitation3d = gravitation<vector3d>;

} } // namespace

#endif /* MZLIB_LAWS_H */

#ifdef MZLIB_BUILDING_TESTS

TEST(gravitation, solve_for_force)
{
   mzlib::law::gravitation2d gra;
   gra.m_1 = mzlib::mass_centre2d{
      mzlib::vector2d::unit * 0, 
      mzlib::consts::earth_mass };
   gra.m_2 = mzlib::mass_centre2d{
      mzlib::vector2d::unit * mzlib::consts::moon_distance_earth, 
      mzlib::consts::moon_mass };
   gra.solve_for_force();
   
   auto direction = gra.f_1.value().normalise();
   auto size = gra.f_1.value().length();
   
   ASSERT_TRUE(mzlib::dbl(size).equals(1.9820850603183325e20_N));
   ASSERT_TRUE(direction == mzlib::vector2d::unit);
}

#endif // MZLIB_BUILDING_TESTS
