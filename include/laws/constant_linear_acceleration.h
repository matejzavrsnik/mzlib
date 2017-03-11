//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_LAWS_CONSTANT_LINEAR_ACCELERATION_H
#define	MZLIB_LAWS_CONSTANT_LINEAR_ACCELERATION_H

#include "../mass_centre.h"
#include "../lang/optional.h"

namespace mzlib {
namespace law {

template<class VectorT>
class constant_linear_acceleration
{
   
public:
      
   optional<VectorT> v_0;   
   optional<VectorT> v_f;
   optional<VectorT> r_0;   
   optional<VectorT> r_f;
   optional<VectorT> a;
   optional<double>  t;
   
   void solve_for_final_velocity()
   {
      v_f = v_0.get() + a.get() * t.get();
   }
   
   void solve_for_initial_velocity()
   {
      if ( v_f.is_set() ) {
         v_0 = v_f.get() - a.get() * t.get();
      }
      else if ( r_f.is_set() ) {
         v_0 = ( r_f.get() - r_0.get() ) / t.get() - 0.5 * a.get() * t.get();
      }
   }

   void solve_for_acceleration()
   {
      if ( v_f.is_set() ) {
         a = ( v_f.get() - v_0.get() ) / t.get();
      }
      else if ( r_f.is_set() ) {
         a = ( 2 / ( t.get() * t.get() ) ) * ( r_f.get() - r_0.get() - v_0.get() * t.get() );
      }
   }

   void solve_for_time()
   {
      t = ( v_f.get().length() - v_0.get().length() ) / a.get().length();
   }
   
   void solve_for_final_location()
   {
      r_f = r_0.get() + v_0.get() * t.get() + 0.5 * a.get() * t.get() * t.get();       
   }
};

using constant_linear_acceleration2d = constant_linear_acceleration<vector2d>;
using constant_linear_acceleration3d = constant_linear_acceleration<vector3d>;

} } // namespace

#endif /* MZLIB_LAWS_CONSTANT_LINEAR_ACCELERATION_H */

