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
   
template <class VectorT>
class cbody_properties : public cunique 
{

public:
   
   VectorT gravity;
   VectorT velocity;

};

template <class DataT, class VectorT>
class cbasic_body
{

public:
   
   DataT data; //todo: any better names out there?
   cmass_centre<VectorT> mass_centre;
   
   cbasic_body()
   {
   }
   
   cbasic_body(const DataT& binded_data, VectorT location_ = {0}, double mass_ = 0) :
      data(binded_data),   
      mass_centre(location_, mass_)
   {
   }
   
   cbasic_body (const cbasic_body<DataT,VectorT>&) = default;
   cbasic_body (cbasic_body<DataT,VectorT> && ) = default;
   cbasic_body<DataT,VectorT>& operator= (const cbasic_body<DataT,VectorT>&) = default;
   cbasic_body<DataT,VectorT>& operator= (cbasic_body<DataT,VectorT>&&) = default;
   ~cbasic_body () = default;
   
};

using cbody_properties2d = cbody_properties<cvector2d>;
using cbody_properties3d = cbody_properties<cvector3d>;
template<class DataT> using cbasic_body2d = cbasic_body<DataT, cvector2d>;
template<class DataT> using cbasic_body3d = cbasic_body<DataT, cvector3d>;
using cbody2d = cbasic_body2d<cbody_properties2d>;
using cbody3d = cbasic_body3d<cbody_properties3d>;

} // namespace

#endif	/* MZLIB_BODY_H */

