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

// Why is this binded mass centre class needed? Because mass centre is sometimes
// not just a standalone thing with a mass and location, hanging somewhere. It can
// also represent something, like a planet or star or something abstract. Now you
// need to say, planet earth has a mass centre. Could create assemble earth object
// and mass centre object into std::pair, but I don't like those firsts and seconds,
// because you can't read from the code what it represents. You need to decrypt
// object.first.second.second.first before you can tell what the code does. You 
// need to rely on IDE to do this for you, but IDEs can sometimes be funny.
// Long story short, this class is to attach any data of generic type T to a mass centre.
template <class DataT, class VectorT>
class cbinded_mass_centre
{

public:
   
   DataT data; //todo: any better names out there?
   cmass_centre<VectorT> mass_centre;
   
   cbinded_mass_centre()
   {
   }
   
   cbinded_mass_centre(const DataT& binded_data, VectorT location_ = {0}, double mass_ = 0) :
      data(binded_data),   
      mass_centre(location_, mass_)
   {
   }
   
   cbinded_mass_centre (const cbinded_mass_centre<DataT,VectorT>&) = default;
   cbinded_mass_centre (cbinded_mass_centre<DataT,VectorT> && ) = default;
   cbinded_mass_centre<DataT,VectorT>& operator= (const cbinded_mass_centre<DataT,VectorT>&) = default;
   cbinded_mass_centre<DataT,VectorT>& operator= (cbinded_mass_centre<DataT,VectorT>&&) = default;
   ~cbinded_mass_centre () = default;
   
};

// convenient types

using cmass_centre2d = cmass_centre<cvector2d>;
using cmass_centre3d = cmass_centre<cvector3d>;
template<class DataT> using cbinded_mass_centre2d = cbinded_mass_centre<DataT, cvector2d>;
template<class DataT> using cbinded_mass_centre3d = cbinded_mass_centre<DataT, cvector3d>;


} // namespace
    
#endif	/* MZLIB_MASS_CENTRE_H */

