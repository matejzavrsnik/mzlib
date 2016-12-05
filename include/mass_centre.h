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
class mass_centre
{

public:
     
   VectorT location;
   double mass;

   mass_centre() :
      location({0}),
      mass(0)
   {
   }
   
   mass_centre(VectorT l, double m) :
      location(l),
      mass(m)
   {
   }
   
   mass_centre (const mass_centre<VectorT>&) = default;
   mass_centre (mass_centre<VectorT>&&) = default;
   mass_centre<VectorT>& operator= (const mass_centre<VectorT>&) = default;
   mass_centre<VectorT>& operator= (mass_centre<VectorT>&&) = default;
   ~mass_centre () = default;
   
   void add_to_mass_centre (const mass_centre<VectorT>& mc) 
   {
      VectorT new_location;
      double new_mass = mass + mc.mass;
      new_location = (location * mass + mc.location * mc.mass) / new_mass;
      location = new_location;
      mass = new_mass;
   }
        
   void remove_from_mass_centre(const mass_centre<VectorT>& mc) 
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

using cmass_centre2d = mass_centre<vector2d>;
using cmass_centre3d = mass_centre<vector3d>;


} // namespace
    
#endif	/* MZLIB_MASS_CENTRE_H */

