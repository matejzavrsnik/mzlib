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
class cnewtons_law_of_gravitation
{
   
public:
   
   util::coptional<cmass_centre<VectorT>> mass_centre1; 
   util::coptional<cmass_centre<VectorT>> mass_centre2; 
   util::coptional<double> gravitational_constant;
   util::coptional<VectorT> force_on_body1;
   
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

using cnewtons_law_of_gravitation2d = cnewtons_law_of_gravitation<math::cvector2d>;
using cnewtons_law_of_gravitation3d = cnewtons_law_of_gravitation<math::cvector3d>;

// Newton's second law of motion
template<class VectorT>
class cnewtons_law_of_acceleration
{
   
public:
      
   util::coptional<VectorT> f;   
   util::coptional<VectorT> a;
   util::coptional<double>  m;
   
   void solve_for_force()
   {
      // check if needed parameters are provided
      if (!a.is_set() || !m.is_set()) {
         return;
      }
      
      // get to business
      f.set(m.get()*a.get());
   }
   
   void solve_for_acceleration()
   {
      // check if needed parameters are provided
      if (!f.is_set() || !m.is_set()) {
         return;
      }
      
      // get to business
      a.set(f.get()/m.get());
   }
   
};

using cnewtons_law_of_acceleration2d = cnewtons_law_of_acceleration<math::cvector2d>;
using cnewtons_law_of_acceleration3d = cnewtons_law_of_acceleration<math::cvector3d>;


} // namespace mzlib

#endif // LAWS_H

