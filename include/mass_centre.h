// 
// Author: Matej Zavrsnik (matejzavrsnik.com)
//

#ifndef MASS_CENTRE_H
#define	MASS_CENTRE_H

#include "vector.h"

namespace mzlib {

class cmass_centre
{

private:
     
   math::cvector2d m_location;
   double m_mass;
        
public:
        
   cmass_centre () : 
      m_location(), 
      m_mass(0) 
   {
   }
        
   cmass_centre (math::cvector2d location, double mass) : 
      m_location(location), 
      m_mass(mass) 
   {
   }
   
   cmass_centre(const cmass_centre&) = default;
   cmass_centre(cmass_centre && ) = default;
   cmass_centre& operator=(const cmass_centre&) = default;
   cmass_centre& operator=(cmass_centre&&) = default;
   ~cmass_centre() = default;
        
   void set_mass (double mass)
   { 
      m_mass = mass; 
   }

   void add_mass (double mass) 
   { 
      m_mass += mass; 
   }

   double get_mass () const
   { 
      return m_mass; 
   }

   math::cvector2d get_location () const
   { 
      return m_location; 
   }
     
   void add_location (const math::cvector2d& location)
   { 
      m_location += location;
   }

   void set_location  (const math::cvector2d& location)
   { 
      m_location = location; 
   }
        
   // Following two functions are an online algorithm for mass centre maintenance.
   // It is done in constant time while calculating mass centre from scratch takes linear time.
   // Be aware that precision errors creep into the calculation when removing mass centres,
   // so it is worth recalculating it from scratch every now and then.
        
   void add_to_mass_centre (const cmass_centre& mc) 
   {
      math::cvector2d new_location;
      double new_mass = m_mass+mc.m_mass;
      new_location = (m_location*m_mass+mc.m_location*mc.m_mass) / new_mass;
      m_location = new_location;
      m_mass = new_mass;
   }
        
   void remove_from_mass_centre(const cmass_centre& mc) 
   {
      math::cvector2d new_location;
      double new_mass = m_mass-mc.m_mass;
      double sum_of_masses = new_mass+mc.m_mass;
      auto a = m_location*sum_of_masses;
      auto b = mc.get_location()*mc.m_mass;
      new_location = (a-b)/new_mass;
      m_location = new_location;
      m_mass = new_mass;
   }
};

// cmass_centre will be hard to identify uniquely, because all members might be
// floating point numbers. It is practical to allow binding it with some user
// defined data, so that they can be marked in some way, either labelled or
// equiped with unique id, or whatever.
template <class T>
class cbinded_mass_centre : public cmass_centre
{

private:
   
   T m_binded_data; //todo: any better names out there?
   
public:
   
   cbinded_mass_centre()
   {
   }
   
   cbinded_mass_centre(const T& binded_data, math::cvector2d location = {0,0}, double mass = 0) :
      m_binded_data(binded_data),   
      cmass_centre(location, mass)
   {
   }
   
   cbinded_mass_centre(const cbinded_mass_centre&) = default;
   cbinded_mass_centre(cbinded_mass_centre && ) = default;
   cbinded_mass_centre& operator=(const cbinded_mass_centre&) = default;
   cbinded_mass_centre& operator=(cbinded_mass_centre&&) = default;
   ~cbinded_mass_centre() = default;
   
   T& get_binded_data()
   {
      return m_binded_data;
   }
   
   const T& get_binded_data() const
   {
      return m_binded_data;
   }
   
};

} // namespace mzlib
    
#endif	/* MASS_CENTRE_H */

