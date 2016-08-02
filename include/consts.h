//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef CONSTS_H
#define CONSTS_H

#include "units.h"

namespace mzlib { 
namespace consts {

using namespace mzlib::units;

// math
constexpr long double operator"" _pi          (long double pi)   { return pi*3.1415926535; }

// measured
const double earth_distance_sun_perihelion = 147098290.0_km;
const double earth_distance_sun_aphelion   = 152096000.0_km;
const double earth_distance_sun_average    = 150000000.0_km;
const double earth_distance_moon_average   = 384400.0_km;
const double earth_speed_perihelion        = 30.29_km_per_s;
const double earth_speed_aphelion          = 29.29_km_per_s;
const double earth_speed_average           = 29.78_km_per_s;
const double light_speed                   = 299792458.0_m_per_s;
const double gravitational_constant        = 6.67384e-11;

const double earth_mass                    = 5.9726e24_kg;
const double moon_mass                     = 7.34767309e22_kg;
const double sun_mass                      = 1.98855e30_kg;
    
// derived
const double earth_orbit_length            = earth_distance_sun_average * 2.0_pi;

} } // namespace mzlib::consts

#endif //CONSTS_H

