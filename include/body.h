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
   
class cbody_forces
{
   
public:
        
   math::cvector2d force;
   math::cvector2d velocity;

};

class cbody_properties : public cbody_forces, public util::cunique 
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

using cbody = cbinded_mass_centre2d<cbody_properties>;


} // namespace mzlib

#endif	/* BODY_H */

