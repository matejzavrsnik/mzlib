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
class acceleration
{
   
public:
      
   optional<VectorT> f;   
   optional<VectorT> a;
   optional<double>  m;
   
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
      m = f.get().length() / a.get().length();
   }
   
};

using acceleration2d = acceleration<vector2d>;
using acceleration3d = acceleration<vector3d>;

} } // namespace

#endif /* MZLIB_LAWS_ACCELERATION_H */

