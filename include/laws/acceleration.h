//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_LAWS_ACCELERATION_H
#define	MZLIB_LAWS_ACCELERATION_H

#include "../optional.h"

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
      f = m() * a();
   }
   
   void solve_for_acceleration()
   {
      a = f.get() / m.get();
   }
   
};

using cacceleration2d = cacceleration<cvector2d>;
using cacceleration3d = cacceleration<cvector3d>;

} } // namespace

#endif /* MZLIB_LAWS_ACCELERATION_H */

