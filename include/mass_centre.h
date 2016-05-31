//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//


#ifndef MASS_CENTRE_H
#define	MASS_CENTRE_H

#include "vector.h"

namespace mzlib {

class cmass_centre
{

public:
     
   math::cvector2d location;
   double mass;

   cmass_centre(math::cvector2d l = {0,0}, double m = 0) :
      location(l),
      mass(m)
   {
   }
   
   cmass_centre(const cmass_centre&) = default;
   cmass_centre(cmass_centre &&) = default;
   cmass_centre& operator=(const cmass_centre&) = default;
   cmass_centre& operator=(cmass_centre&&) = default;
   ~cmass_centre() = default;
   
   void add_to_mass_centre (const cmass_centre& mc) 
   {
      math::cvector2d new_location;
      double new_mass = mass + mc.mass;
      new_location = (location * mass + mc.location * mc.mass) / new_mass;
      location = new_location;
      mass = new_mass;
   }
        
   void remove_from_mass_centre(const cmass_centre& mc) 
   {
      math::cvector2d new_location;
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
template <class T>
class cbinded_mass_centre : public cmass_centre
{

public:
   
   T data; //todo: any better names out there?
   
   cbinded_mass_centre()
   {
   }
   
   cbinded_mass_centre(const T& binded_data, math::cvector2d location_ = {0,0}, double mass_ = 0) :
      data(binded_data),   
      cmass_centre(location_, mass_)
   {
   }
   
   cbinded_mass_centre(const cbinded_mass_centre&) = default;
   cbinded_mass_centre(cbinded_mass_centre && ) = default;
   cbinded_mass_centre& operator=(const cbinded_mass_centre&) = default;
   cbinded_mass_centre& operator=(cbinded_mass_centre&&) = default;
   ~cbinded_mass_centre() = default;
   
};

} // namespace mzlib
    
#endif	/* MASS_CENTRE_H */

