//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_LAWS_CONSTANT_LINEAR_ACCELERATION_H
#define	MZLIB_LAWS_CONSTANT_LINEAR_ACCELERATION_H

#include "../mass_centre.h"
#include "../optional.h"

namespace mzlib {
namespace law {

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

#endif /* MZLIB_LAWS_CONSTANT_LINEAR_ACCELERATION_H */

