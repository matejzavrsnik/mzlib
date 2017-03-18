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
#include "../abstract/unique.h"

namespace mzlib {
   
// Physical properties of a body, that will be used in physical simulations.
   
template <class VectorT>
struct body_properties
{
   
   VectorT gravity;
   VectorT velocity;

};

// A basic model of the body; that which is the essence of the body.
// I chose this to be a point of mass on given location. The rest if the properties
// of the body should depend on the needs of a given problem. For instance, Earth 
// can be considered a body, but one that doesn't really need an information about
// electrical charge when we simulate gravitational forces. If there was a reserved 
// electrical field in every body, that would amount to a lot of unnecessary data
// being stored and transferred around in this particular case. At the same time
// it enables abstract approach to building universes: this approach enables the
// user to store a number with given "mass" on the specified coordinates in space
// and see quadtree as something other than strictly "physical bodies in space".

template <class VectorT>
struct body_core
{
   mass_centre<VectorT> centre;
   unique tag;
};

// And finally a physical body that can be used. Derives from body_core instead
// of contining body_core so that core body features can be used without the need
// for a system to be aware of it's properties. If latter is desired they can still
// use this final physical_body.

template <class PropertiesT, class VectorT>
struct physical_body 
{
   PropertiesT properties;
   body_core<VectorT> core;
};

using body_properties2d = body_properties<vector2d>;
using body_properties3d = body_properties<vector3d>;
using body_core2d = body_core<vector2d>;
using body_core3d = body_core<vector3d>;
using body2d = physical_body<body_properties2d, vector2d>;
using body3d = physical_body<body_properties3d, vector3d>;

} // namespace

#endif	/* MZLIB_BODY_H */

