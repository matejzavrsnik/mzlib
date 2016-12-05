//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_LAWS_GRAVITATION_H
#define	MZLIB_LAWS_GRAVITATION_H

#include "../mass_centre.h"
#include "../optional.h"
#include "../consts.h"

namespace mzlib {
namespace law {
   
template<class VectorT>
class gravitation
{
   
public:
   
   optional<mass_centre<VectorT>> m_1; 
   optional<mass_centre<VectorT>> m_2; 
   optional<double> G = optional<double>(mzlib::consts::gravitational_constant);
   optional<VectorT> f_1;
   
   void solve_for_force ()
   {
      VectorT m1_force = {0};
      double sqare_distance = m_1.get().location.square_distance_to(m_2.get().location); 
      m1_force = -m_1.get().location.direction_to(m_2.get().location).normalise(); 
      m1_force *= m_1.get().mass * m_2.get().mass; // masses
      m1_force /= sqare_distance; // distance
      m1_force *= G.get(); // factor
      f_1 = m1_force;
   }
   
   // Because I noticed that if gravity is linearly proportional to distance,
   // games are more fun. Seems like people have limited ability to intuitively
   // grasp second order polynomials like in accelerated motion or gravity force.
   void solve_for_fun_force ()
   {
      VectorT m1_force = {0};
      // todo: what when the distance is zero?
      double sqare_distance = m_1.get().location.square_distance_to(m_2.get().location); 
      m1_force = -m_1.get().location.direction_to(m_2.get().location).normalise(); 
      m1_force *= m_1.get().mass * m_2.get().mass; // masses
      m1_force /= std::sqrt(sqare_distance); // distance
      m1_force *= G.get(); // factor
      f_1 = m1_force;
   }
   
};

using cgravitation2d = gravitation<vector2d>;
using cgravitation3d = gravitation<vector3d>;

} } // namespace

#endif /* MZLIB_LAWS_H */

