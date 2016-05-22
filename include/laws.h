// 
// Author: Matej Zavrsnik (matejzavrsnik.com)
//

#ifndef LAWS_H
#define	LAWS_H

#include "vector.h"

namespace mzlib
{
    typedef std::function<
        math::cvector2d (
            const std::shared_ptr<cbody>, 
            const std::shared_ptr<cbody>, 
            const double)> 
                interface_law_of_gravitation;
    
    inline math::cvector2d universal_law_of_gravitation(
        const std::shared_ptr<cbody> body1, 
        const std::shared_ptr<cbody> body2, 
        const double gravitational_constant)
    {
        double sqare_distance = body1->get_location().square_distance_to(body2->get_location()); 
        math::cvector2d force_on_body1 = -body1->get_location().direction_to(body2->get_location()).normalise(); 
        force_on_body1 *= body1->get_mass() * body2->get_mass(); // masses
        force_on_body1 /= sqare_distance; // distance
        force_on_body1 *= gravitational_constant; // factor
        return force_on_body1;
    }

    inline math::cvector2d more_entertaining_law_of_gravitation(
        const std::shared_ptr<cbody> body1, 
        const std::shared_ptr<cbody> body2, 
        const double gravitational_constant)
    {
        double sqare_distance = body1->get_location().square_distance_to(body2->get_location()); 
        math::cvector2d force_on_body1 = -body1->get_location().direction_to(body2->get_location()).normalise(); // give vector a direction
        force_on_body1 *= body1->get_mass() * body2->get_mass(); // masses
        force_on_body1 /= std::sqrt(sqare_distance); // distance
        force_on_body1 *= gravitational_constant; // factor
        return force_on_body1;
    }
}

#endif	/* LAWS_H */

