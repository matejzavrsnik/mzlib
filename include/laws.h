//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef LAWS_H
#define	LAWS_H

#include "mass_centre.h"
#include "optional.h"

namespace mzlib
{

template<class VectorT>
class cuniversal_law_of_gravitation
{
   
public:
   
   util::coptional_ref<cmass_centre<VectorT>> mass_centre1; 
   util::coptional_ref<cmass_centre<VectorT>> mass_centre2; 
   util::coptional_ref<double> gravitational_constant;
   util::coptional_ref<VectorT> force_on_body1;
   
   void solve_for_force ()
   {
      // check if needed parameters are provided
      if (!mass_centre1.is_set() ||
          !mass_centre2.is_set() ||
          !gravitational_constant.is_set())
      {
         return;
      }

      // make it easier to read
      const cmass_centre<VectorT>& m1 = mass_centre1.get();
      const cmass_centre<VectorT>& m2 = mass_centre2.get();
      const double& G = gravitational_constant.get();

      // get to business
      VectorT m1_force = {0};
      double sqare_distance = m1.location.square_distance_to(m2.location); 
      m1_force = -m1.location.direction_to(m2.location).normalise(); 
      m1_force *= m1.mass * m2.mass; // masses
      m1_force /= sqare_distance; // distance
      m1_force *= G; // factor

      // done
      force_on_body1.set(m1_force);
   }
   
   // Because I noticed that if gravity is linearly proportional to distance,
   // games are more fun. Seems like people have limited ability to intuitively
   // grasp second order polynomials like in accelerated motion or gravity force.
   void solve_for_fun_force ()
   {
      // check if needed parameters are provided
      if (!mass_centre1.is_set() ||
          !mass_centre2.is_set() ||
          !gravitational_constant.is_set())
      {
         return;
      }

      // make it easier to read
      const cmass_centre<VectorT>& m1 = mass_centre1.get();
      const cmass_centre<VectorT>& m2 = mass_centre2.get();
      const double& G = gravitational_constant.get();

      // get to business
      VectorT m1_force = {0};
      double sqare_distance = m1.location.square_distance_to(m2.location); 
      m1_force = -m1.location.direction_to(m2.location).normalise(); 
      m1_force *= m1.mass * m2.mass; // masses
      m1_force /= std::sqrt(sqare_distance); // distance
      m1_force *= G; // factor

      // done
      force_on_body1.set(m1_force);
   }
   
};

using cuniversal_law_of_gravitation2d = cuniversal_law_of_gravitation<math::cvector2d>;

} // namespace mzlib

#endif // LAWS_H

