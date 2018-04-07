//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_CONSTS_H
#define MZLIB_CONSTS_H

#include "units.h"

namespace mzlib { 
// purpose of this nested namespace: to not pollute the library's namespace with
// numerous constants here. If the number of valuable constants is ever slightly
// increased, and that is the plan, they might be more numerous than classes and 
// functions themselves.
namespace consts {
   
using namespace units; 
   
//
// measured
//

// physical constants of universe
const double gravitational_constant = 6.67384e-11;
const double light_speed            = 299792458.0_m_per_s;
const double pi                     = 3.1415926535;

// distances of solar system bodies to sun
const double mercury_distance_sun  =   57.9e6_km;
const double venus_distance_sun    =  108.2e6_km;
const double earth_distance_sun    =  149.6e6_km;
const double mars_distance_sun     =  227.9e6_km;
const double jupiter_distance_sun  =  778.5e6_km;
const double saturn_distance_sun   = 1429.0e6_km;
const double uranus_distance_sun   = 2871.0e6_km;
const double neptune_distance_sun  = 4498.0e6_km;

// perihelion and aphelion distances
const double earth_distance_sun_perihelion = 147098290.0_km;
const double earth_distance_sun_aphelion   = 152096000.0_km;

// satellite distances to solar system bodies
const double moon_distance_earth   = 384400.0_km;

// velocities of solar system bodies
const double earth_velocity_perihelion = 30.29_km_per_s;
const double earth_velocity_aphelion   = 29.29_km_per_s;
const double earth_velocity_average    = 29.78_km_per_s;

// masses of planets in solar system
const double sun_mass       = 1.98855e30_kg;
const double mercury_mass   = 3.285e23_kg;
const double venus_mass     = 4.867e24_kg;
const double earth_mass     = 5.9726e24_kg;
const double mars_mass      = 6.39e23_kg;
const double jupiter_mass   = 1.898e27_kg;
const double saturn_mass    = 5.683e26_kg;
const double uranus_mass    = 8.681e25_kg;
const double neptune_mass   = 1.024e26_kg;

// masses of satellites in solar system
const double moon_mass      = 7.34767309e22_kg;
    
// derived
const double earth_orbit_length            = earth_distance_sun * 2.0 * pi;

} } // namespace

#endif /* MZLIB_CONSTS_H */

