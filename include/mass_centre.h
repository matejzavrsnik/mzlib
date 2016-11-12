//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//


#ifndef MZLIB_MASS_CENTRE_H
#define	MZLIB_MASS_CENTRE_H

#include "vector.h"

namespace mzlib {

template <class VectorT>
class cmass_centre
{

public:
     
   VectorT location;
   double mass;

   cmass_centre() :
      location({0}),
      mass(0)
   {
   }
   
   cmass_centre(VectorT l, double m) :
      location(l),
      mass(m)
   {
   }
   
   cmass_centre (const cmass_centre<VectorT>&) = default;
   cmass_centre (cmass_centre<VectorT>&&) = default;
   cmass_centre<VectorT>& operator= (const cmass_centre<VectorT>&) = default;
   cmass_centre<VectorT>& operator= (cmass_centre<VectorT>&&) = default;
   ~cmass_centre () = default;
   
   void add_to_mass_centre (const cmass_centre<VectorT>& mc) 
   {
      VectorT new_location;
      double new_mass = mass + mc.mass;
      new_location = (location * mass + mc.location * mc.mass) / new_mass;
      location = new_location;
      mass = new_mass;
   }
        
   void remove_from_mass_centre(const cmass_centre<VectorT>& mc) 
   {
      VectorT new_location;
      double new_mass = mass - mc.mass;
      double sum_of_masses = new_mass + mc.mass;
      auto a = location * sum_of_masses;
      auto b = mc.location * mc.mass;
      new_location = (a-b) / new_mass;
      location = new_location;
      mass = new_mass;
   }
};

// convenient types

using cmass_centre2d = cmass_centre<cvector2d>;
using cmass_centre3d = cmass_centre<cvector3d>;


} // namespace
    
#endif	/* MZLIB_MASS_CENTRE_H */

