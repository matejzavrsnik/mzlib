// 
// Author: Matej Zavrsnik (matejzavrsnik.com)
//

#ifndef BODY_H
#define	BODY_H

#include <memory>
#include "vector.h"
#include "mass_centre.h"

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
   
   void set_name (const std::string& name) 
   { 
      m_name = name; 
   }
   
   bool operator== (cbody_forces& other)
   {
      if (&other == this) {
         return true;
      }
      return (this->m_name == other.m_name);
   }
   
   bool operator!= (cbody_forces& other)
   {
      return !(*this == other);
   }

private:
        
   math::cvector2d m_force;
   math::cvector2d m_velocity;
   math::cvector2d m_gravity;
   std::string m_name; //todo: make identifiable by some other means
};

using cbody = cbinded_mass_centre<cbody_forces>;

} // namespace mzlib

#endif	/* BODY_H */

