//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_LAWS_CONSTANT_LINEAR_ACCELERATION_H
#define	MZLIB_LAWS_CONSTANT_LINEAR_ACCELERATION_H

#include "../nature/mass_centre.h"
#include <optional>

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
