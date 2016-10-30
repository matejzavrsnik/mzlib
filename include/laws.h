//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_LAWS_H
#define	MZLIB_LAWS_H

#include "mass_centre.h"
#include "optional.h"

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

// Newton's second law of motion
template<class VectorT>
class cacceleration
{
   
public:
      
   coptional<VectorT> f;   
   coptional<VectorT> a;
   coptional<double>  m;
   
   void solve_for_force()
   {
      f = m() * a();
   }
   
   void solve_for_acceleration()
   {
      a = f.get() / m.get();
   }
   
};

using cacceleration2d = cacceleration<cvector2d>;
using cacceleration3d = cacceleration<cvector3d>;

template<class VectorT>
class cconstant_linear_acceleration
{
   
public:
      
   coptional<VectorT> v_initial;   
   coptional<VectorT> v_final;
   coptional<VectorT> r_initial;   
   coptional<VectorT> r_final;
   coptional<VectorT> a;
   coptional<double>  time;
   
   void solve_for_final_velocity()
   {
      v_final = v_initial.get() + a.get() * time.get();
   }
   
   void solve_for_final_location()
   {
      r_final = r_initial.get() + v_initial.get() * time.get() + 0.5 * a.get() * time.get() * time.get();       
   }
};

using cconstant_linear_acceleration2d = cconstant_linear_acceleration<cvector2d>;
using cconstant_linear_acceleration3d = cconstant_linear_acceleration<cvector3d>;

} } // namespace

#endif /* MZLIB_LAWS_H */

