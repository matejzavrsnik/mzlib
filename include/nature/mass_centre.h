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
struct mass_centre
{
   VectorT location{0};
   double mass{0};
};

template<class VectorT>
void add_to_mass_centre (mass_centre<VectorT>& to_mc, const mass_centre<VectorT>& mc) 
{
   VectorT new_location;
   double new_mass = to_mc.mass + mc.mass;
   new_location = (to_mc.location * to_mc.mass + mc.location * mc.mass) / new_mass;
   to_mc.location = new_location;
   to_mc.mass = new_mass;
}

template<class VectorT>
void remove_from_mass_centre(mass_centre<VectorT>& from_mc, const mass_centre<VectorT>& mc) 
{
   VectorT new_location;
   double new_mass = from_mc.mass - mc.mass;
   double sum_of_masses = new_mass + mc.mass;
   auto a = from_mc.location * sum_of_masses;
   auto b = mc.location * mc.mass;
   new_location = (a-b) / new_mass;
   from_mc.location = new_location;
   from_mc.mass = new_mass;
}

// convenient types

using mass_centre2d = mass_centre<vector2d>;
using mass_centre3d = mass_centre<vector3d>;

} // namespace

template<class VectorT>
inline std::ostream& operator<< (std::ostream& os, const mzlib::mass_centre<VectorT> mc)
{
   os << "[" 
      << mc.location << ","
      << mc.mass
      << "]";
   return os;
}

#endif	/* MZLIB_MASS_CENTRE_H */
