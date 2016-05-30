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

   cbody_forces() :  
       m_force(), 
       m_velocity(), 
       m_gravity() 
   {
   }
        
   cbody_forces(const cbody_forces&) = default;
   cbody_forces(cbody_forces && ) = default;
   cbody_forces& operator=(const cbody_forces&) = default;
   cbody_forces& operator=(cbody_forces&&) = default;
   ~cbody_forces() = default;
        
   void set_velocity (const math::cvector2d& velocity) 
   { 
      m_velocity = velocity; 
   }

   void add_velocity (const math::cvector2d& velocity) 
   { 
      m_velocity += velocity; 
   }
        
   math::cvector2d get_velocity () const
   { 
      return m_velocity; 
   }
        
   math::cvector2d get_force () const
   { 
      return m_force; 
   }
        
   void add_force (const math::cvector2d& force)
   { 
      m_force += force; 
   }

   void set_force (const math::cvector2d& force) 
   { 
      m_force = force; 
   }

private:
        
   math::cvector2d m_force;
   math::cvector2d m_velocity;
   math::cvector2d m_gravity;

};

class cbody_properties : public cbody_forces, public util::cunique 
{

public:
   
   bool operator== (cbody_properties& other)
   {
      if (&other == this) {
         return true;
      }
      return (this->id() == other.id());
   }
   
   bool operator!= (cbody_properties& other)
   {
      return !(*this == other);
   }
};

using cbody = cbinded_mass_centre<cbody_properties>;

} // namespace mzlib

#endif	/* BODY_H */

