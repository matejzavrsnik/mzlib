// 
// Author: Matej Zavrsnik (matejzavrsnik.com)
//

#ifndef BODY_H
#define	BODY_H

#include <memory>
#include "vector.h"
#include "mass_centre.h"

namespace mzlib {

class cbody : public cbinded_mass_centre<std::string>
{

public:
        
   cbody() : 
      cbinded_mass_centre<std::string>() 
   {
   }

   explicit cbody(const std::string& binded_data) : 
       cbinded_mass_centre<std::string>(binded_data), 
       m_force(), 
       m_velocity(), 
       m_gravity() 
   {
   }
        
   cbody(const cbody&) = default;
   cbody(cbody && ) = default;
   cbody& operator=(const cbody&) = default;
   cbody& operator=(cbody&&) = default;
   ~cbody() = default;
        
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

} // namespace mzlib

#endif	/* BODY_H */

