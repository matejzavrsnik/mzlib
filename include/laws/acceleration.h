//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_LAWS_ACCELERATION_H
#define	MZLIB_LAWS_ACCELERATION_H

#include "../optional.h"
#include "../vector.h"

namespace mzlib {
namespace law {
   
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
      f = m.get() * a.get();
   }
   
   void solve_for_acceleration()
   {
      a = f.get() / m.get();
   }

   void solve_for_mass()
   {
      // acceleration and force need to be colinear to use this law
      if (f.get().normalise() != a.get().normalise() ) {
         throw exception::invalid_values();
      }
      
      m = f.get().length() / a.get().length();
   }
   
};

using cacceleration2d = cacceleration<cvector2d>;
using cacceleration3d = cacceleration<cvector3d>;

} } // namespace

#endif /* MZLIB_LAWS_ACCELERATION_H */

