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
#include "unique.h"

namespace mzlib {
   
// Physical properties of a body, that will be used in physical simulations.
template <class VectorT>
struct body_properties // todo: can be struct. keep it simple
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
template <class PropertiesT, class VectorT>
class body_frame
{

public:
   
   PropertiesT properties; //todo: any better names out there?
   mass_centre<VectorT> centre;
   unique tag;
   
   body_frame()
   {
   }
   
   body_frame(const PropertiesT& properties_, VectorT location_ = {0}, double mass_ = 0) :
      properties(properties_),   
      centre(location_, mass_)
   {
   }
   
   body_frame (const body_frame<PropertiesT,VectorT>&) = default;
   body_frame (body_frame<PropertiesT,VectorT> && ) = default;
   body_frame<PropertiesT,VectorT>& operator= (const body_frame<PropertiesT,VectorT>&) = default;
   body_frame<PropertiesT,VectorT>& operator= (body_frame<PropertiesT,VectorT>&&) = default;
   ~body_frame () = default;
   
};

using body_properties2d = body_properties<vector2d>;
using body_properties3d = body_properties<vector3d>;
template<class PropertiesT> using body_frame2d = body_frame<PropertiesT, vector2d>;
template<class PropertiesT> using body_frame3d = body_frame<PropertiesT, vector3d>;
using body2d = body_frame2d<body_properties2d>;
using body3d = body_frame3d<body_properties3d>;

} // namespace

#endif	/* MZLIB_BODY_H */

