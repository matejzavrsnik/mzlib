// 
// Author: Matej Zavrsnik (matejzavrsnik.com)
//

#ifndef MASS_CENTRE_H
#define	MASS_CENTRE_H

#include "vector.h"

namespace mzlib
{

    class cmass_centre
    {
    private:
        
        math::cvector2d m_location;
        double m_mass;
        
    public:
        
        cmass_centre() : m_location(), m_mass(0) {}
        cmass_centre(math::cvector2d location, double mass) : m_location(location), m_mass(mass) {}
        
        double  get_x() const           { return m_location[0]; }
        double  get_y() const           { return m_location[1]; }  
        void    set_mass(double mass)   { m_mass = mass; }
        void    add_mass(double mass) { m_mass += mass; }
        double  get_mass() const        { return m_mass; }
        math::cvector2d get_location() const  { return m_location; }     
        void    add_location(const math::cvector2d& location) { m_location += location;}
        void    set_location  (const math::cvector2d& location) { m_location = location; }
        
        // Following two functions are an online algorithm for mass centre maintenance.
        // It is done in constant time while calculating mass centre from scratch takes linear time.
        // Be aware that precision errors creep into the calculation when removing mass centres,
        // so it is worth recalculating it from scratch every now and then.
        
        void add_to_mass_centre(const cmass_centre& mc) 
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

}
    
#endif	/* MASS_CENTRE_H */

