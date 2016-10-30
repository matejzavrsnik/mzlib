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

namespace mzlib {
namespace law {
   
template<class VectorT>
class cgravitation
{
   
public:
   
   coptional<cmass_centre<VectorT>> m1; 
   coptional<cmass_centre<VectorT>> m2; 
   coptional<double> G;
   coptional<VectorT> f1;
   
   void solve_for_force ()
   {
      VectorT m1_force = {0};
      double sqare_distance = m1.get().location.square_distance_to(m2.get().location); 
      m1_force = -m1.get().location.direction_to(m2.get().location).normalise(); 
      m1_force *= m1.get().mass * m2.get().mass; // masses
      m1_force /= sqare_distance; // distance
      m1_force *= G.get(); // factor
      f1 = m1_force;
   }
   
   // Because I noticed that if gravity is linearly proportional to distance,
   // games are more fun. Seems like people have limited ability to intuitively
   // grasp second order polynomials like in accelerated motion or gravity force.
   void solve_for_fun_force ()
   {
      VectorT m1_force = {0};
      double sqare_distance = m1.get().location.square_distance_to(m2.get().location); 
      m1_force = -m1.get().location.direction_to(m2.get().location).normalise(); 
      m1_force *= m1.get().mass * m2.get().mass; // masses
      m1_force /= std::sqrt(sqare_distance); // distance
      m1_force *= G.get(); // factor
      f1 = m1_force;
   }
   
};

using cgravitation2d = cgravitation<cvector2d>;
using cgravitation3d = cgravitation<cvector3d>;

} } // namespace

#endif /* MZLIB_LAWS_H */

