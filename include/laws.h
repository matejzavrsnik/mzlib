//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef LAWS_H
#define	LAWS_H

#include "mass_centre.h"

namespace mzlib
{
   
template<class VectorT> VectorT universal_law_of_gravitation(
   const cmass_centre<VectorT>& body1, 
   const cmass_centre<VectorT>& body2, 
   const double gravitational_constant)
   {
      double sqare_distance = body1.location.square_distance_to(body2.location); 
      VectorT force_on_body1 = -body1.location.direction_to(body2.location).normalise(); 
      force_on_body1 *= body1.mass * body2.mass; // masses
      force_on_body1 /= sqare_distance; // distance
      force_on_body1 *= gravitational_constant; // factor
      return force_on_body1;
   }

template<class VectorT> VectorT entertaining_law_of_gravitation(
   const cmass_centre<VectorT>& body1, 
   const cmass_centre<VectorT>& body2, 
   const double gravitational_constant)
   {
      double sqare_distance = body1.location.square_distance_to(body2.location); 
      VectorT force_on_body1 = -body1.location.direction_to(body2.location).normalise(); // give vector a direction
      force_on_body1 *= body1.mass * body2.mass; // masses
      force_on_body1 /= std::sqrt(sqare_distance); // distance
      force_on_body1 *= gravitational_constant; // factor
      return force_on_body1;
   }

// for convenience

using ilaw_of_gravitation2d = math::cvector2d (*) (const cmass_centre<math::cvector2d>&, const cmass_centre<math::cvector2d>&, const double);
using ilaw_of_gravitation3d = math::cvector3d (*) (const cmass_centre<math::cvector3d>&, const cmass_centre<math::cvector3d>&, const double);

static ilaw_of_gravitation2d entertaining_law_of_gravitation2d = entertaining_law_of_gravitation<math::cvector2d>;
static ilaw_of_gravitation3d entertaining_law_of_gravitation3d = entertaining_law_of_gravitation<math::cvector3d>;
static ilaw_of_gravitation2d universal_law_of_gravitation2d = universal_law_of_gravitation<math::cvector2d>;
static ilaw_of_gravitation3d universal_law_of_gravitation3d = universal_law_of_gravitation<math::cvector3d>;

} // namespace mzlib

#endif // LAWS_H

