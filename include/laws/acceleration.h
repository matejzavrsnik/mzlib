//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_LAWS_ACCELERATION_H
#define	MZLIB_LAWS_ACCELERATION_H

#include "../nature/vector.h"
#include <optional>

namespace mzlib {
namespace law {
   
// Newton's second law of motion
template<class VectorT>
class acceleration
{
   
public:
      
   std::optional<VectorT> f;   
   std::optional<VectorT> a;
   std::optional<double>  m;
   
   void solve_for_force()
   {
      f = m.value() * a.value();
   }
   
   void solve_for_acceleration()
   {
      a = f.value() / m.value();
   }

   void solve_for_mass()
   {
      m = vector::length(f.value()) / vector::length(a.value());
   }
   
};

using acceleration2d = acceleration<vector2d>;
using acceleration3d = acceleration<vector3d>;

} } // namespace

#endif /* MZLIB_LAWS_ACCELERATION_H */
