//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef BODY_H
#define	BODY_H

#include "vector.h"
#include "mass_centre.h"
#include "utilities.h"

namespace mzlib {
   
template <class VectorT>
class cbody_forces
{
   
public:
        
   VectorT force;
   VectorT velocity;

};

template <class VectorT>
class cbody_properties : public cbody_forces<VectorT>, public util::cunique 
{

public:
   
   bool operator== (const cbody_properties& other) const
   {
      if (&other == this) {
         return true;
      }
      return (this->id() == other.id());
   }
   
   bool operator!= (const cbody_properties& other) const
   {
      return !(*this == other);
   }
};

using cbody_properties2d = cbody_properties<math::cvector2d>;
using cbody_properties3d = cbody_properties<math::cvector3d>;
using cbody2d = cbinded_mass_centre2d<cbody_properties2d>;
using cbody3d = cbinded_mass_centre3d<cbody_properties3d>;


} // namespace mzlib

#endif	/* BODY_H */

