//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_BODY_H
#define	MZLIB_BODY_H

#include "vector.h"
#include "mass_centre.h"
#include "unique.h"

namespace mzlib {
   
template <class VectorT>
class cbody_forces
{
   
public:
        
   VectorT gravity;
   VectorT velocity;

};

template <class VectorT>
class cbody_properties : public cbody_forces<VectorT>, public cunique 
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

using cbody_properties2d = cbody_properties<cvector2d>;
using cbody_properties3d = cbody_properties<cvector3d>;
using cbody2d = cbinded_mass_centre2d<cbody_properties2d>;
using cbody3d = cbinded_mass_centre3d<cbody_properties3d>;


} // namespace

#endif	/* MZLIB_BODY_H */

