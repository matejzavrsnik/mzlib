//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef LAWS_H
#define	LAWS_H

#include "vector.h"
#include "mass_centre.h"

namespace mzlib
{

typedef std::function<
   math::cvector2d (
      const cmass_centre&, 
      const cmass_centre&, 
      const double)> 
   interface_law_of_gravitation;
    
inline math::cvector2d universal_law_of_gravitation(
   const cmass_centre& body1, 
   const cmass_centre& body2, 
   const double gravitational_constant)
   {
      double sqare_distance = body1.location.square_distance_to(body2.location); 
      math::cvector2d force_on_body1 = -body1.location.direction_to(body2.location).normalise(); 
      force_on_body1 *= body1.mass * body2.mass; // masses
      force_on_body1 /= sqare_distance; // distance
      force_on_body1 *= gravitational_constant; // factor
      return force_on_body1;
   }

inline math::cvector2d more_entertaining_law_of_gravitation(
   const cmass_centre& body1, 
   const cmass_centre& body2, 
   const double gravitational_constant)
   {
      double sqare_distance = body1.location.square_distance_to(body2.location); 
      math::cvector2d force_on_body1 = -body1.location.direction_to(body2.location).normalise(); // give vector a direction
      force_on_body1 *= body1.mass * body2.mass; // masses
      force_on_body1 /= std::sqrt(sqare_distance); // distance
      force_on_body1 *= gravitational_constant; // factor
      return force_on_body1;
   }

}

#endif // LAWS_H

