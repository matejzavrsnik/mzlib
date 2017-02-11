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
class body_properties // todo: can be struct. keep it simple
{

public:
   
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
template <class DataT, class VectorT>
class body_frame
{

public:
   
   DataT data; //todo: any better names out there?
   mass_centre<VectorT> mass_c;
   unique tag;
   
   body_frame()
   {
   }
   
   body_frame(const DataT& binded_data, VectorT location_ = {0}, double mass_ = 0) :
      data(binded_data),   
      mass_c(location_, mass_)
   {
   }
   
   body_frame (const body_frame<DataT,VectorT>&) = default;
   body_frame (body_frame<DataT,VectorT> && ) = default;
   body_frame<DataT,VectorT>& operator= (const body_frame<DataT,VectorT>&) = default;
   body_frame<DataT,VectorT>& operator= (body_frame<DataT,VectorT>&&) = default;
   ~body_frame () = default;
   
};

using body_properties2d = body_properties<vector2d>;
using body_properties3d = body_properties<vector3d>;
template<class DataT> using body_frame2d = body_frame<DataT, vector2d>;
template<class DataT> using body_frame3d = body_frame<DataT, vector3d>;
using body2d = body_frame2d<body_properties2d>;
using body3d = body_frame3d<body_properties3d>;

} // namespace

#endif	/* MZLIB_BODY_H */

