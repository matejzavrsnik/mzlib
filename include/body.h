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
class cbody_properties : public cunique 
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
class cbody_frame
{

public:
   
   DataT data; //todo: any better names out there?
   cmass_centre<VectorT> mass_centre;
   
   cbody_frame()
   {
   }
   
   cbody_frame(const DataT& binded_data, VectorT location_ = {0}, double mass_ = 0) :
      data(binded_data),   
      mass_centre(location_, mass_)
   {
   }
   
   cbody_frame (const cbody_frame<DataT,VectorT>&) = default;
   cbody_frame (cbody_frame<DataT,VectorT> && ) = default;
   cbody_frame<DataT,VectorT>& operator= (const cbody_frame<DataT,VectorT>&) = default;
   cbody_frame<DataT,VectorT>& operator= (cbody_frame<DataT,VectorT>&&) = default;
   ~cbody_frame () = default;
   
};

using cbody_properties2d = cbody_properties<cvector2d>;
using cbody_properties3d = cbody_properties<cvector3d>;
template<class DataT> using cbody_frame2d = cbody_frame<DataT, cvector2d>;
template<class DataT> using cbody_frame3d = cbody_frame<DataT, cvector3d>;
using cbody2d = cbody_frame2d<cbody_properties2d>;
using cbody3d = cbody_frame3d<cbody_properties3d>;

} // namespace

#endif	/* MZLIB_BODY_H */

