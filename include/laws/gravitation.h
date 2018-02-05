//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_LAWS_GRAVITATION_H
#define	MZLIB_LAWS_GRAVITATION_H

#include "../nature/mass_centre.h"
#include "../nature/consts.h"
#include <optional>

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
      double sqare_distance = vector::sqr_distance(m_1.value().location, m_2.value().location); 
      m1_force = vector::normalise(vector::direction(m_1.value().location, m_2.value().location)); 
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
      double sqare_distance = vector::sqr_distance(m_1.value().location, m_2.value().location); 
      m1_force = vector::normalise(vector::direction( m_1.value().location, m_2.value().location)); 
      m1_force *= m_1.value().mass * m_2.value().mass; // masses
      m1_force /= std::sqrt(sqare_distance); // distance
      m1_force *= G.value(); // factor
      f_1 = m1_force;
   }
   
};

using gravitation2d = gravitation<vector2d>;
using gravitation3d = gravitation<vector3d>;

} } // namespace

#endif // MZLIB_LAWS_GRAVITATION_H
