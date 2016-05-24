// 
// Author: Matej Zavrsnik (matejzavrsnik.com)
//

#ifndef UNITS_H
#define UNITS_H

#include "units_foundation.h"

namespace mzlib { 
namespace units {

// Conversions to basic SI units

// "error: unable to find numeric literal operator ‘operator"" _km’"
// Seems like when my compiler (g++ 4.7.2) encounters a user-defined literal it decides first
// what the previous token was, only then it searches for the correct overload declaration.
// For instance, a number 5000 will parse to a user-defined integer literal and compiler will 
// try to find an overload that matches one with integer argument. As double is not an integer
// type it will simply fail to find a corresponding overload and complain about it. It will not
// attempt to convert 5000 to floating-point type just to match it with the user-defined string 
// literal. I am not sure whether this is how it was supposed to work or is this just a feature 
// of my particular compiler. I also don't wish to define everything twice. Just call the function
// with 5000.0_km instead of 5000_km and force the compiler to parse the token as floating-point.
    
constexpr long double operator"" _km          (long double km)   { return km*1000; }     // meters
constexpr long double operator"" _km_per_s    (long double kmps) { return kmps*1000; }   // meters per second
constexpr long double operator"" _m_per_s     (long double mps)  { return mps; }
constexpr long double operator"" _julian_year (long double jy)   { return jy*31558152; } // seconds
constexpr long double operator"" _s           (long double s)    { return s; }           // seconds
constexpr long double operator"" _kg          (long double kg)   { return kg; }          // kilograms
constexpr long double operator"" _pi          (long double pi)   { return pi*3.1415926535; }
    
    
// Necessary forward declarations; because units are dependent on each other.
// Example: length * length = area, area / length = length. Which one to define first?
class carea; class cspeed; class cltime; class clength;    
    
// Length
QUANTITY_DEFINITION_START(clength, m)
   friend carea  operator* (const clength lhs, const clength rhs);
   friend cspeed operator/ (const clength lhs, const cltime  rhs);
QUANTITY_DEFINITION_END(clength, m)
// SI units
UNIT_DEFINITION(clength, nm,  1e-9, m)
UNIT_DEFINITION(clength, um,  1e-6, m)
UNIT_DEFINITION(clength, mm,  1e-3, m)
UNIT_DEFINITION(clength, cm,  1e-2, m)
UNIT_DEFINITION(clength, dm,  1e-1, m)
UNIT_DEFINITION(clength, dam, 1e1,  m)
UNIT_DEFINITION(clength, hm,  1e2,  m)
UNIT_DEFINITION(clength, km,  1e3,  m)
UNIT_DEFINITION(clength, Mm,  1e6,  m)
UNIT_DEFINITION(clength, Gm,  1e9,  m)
UNIT_DEFINITION(clength, Tm,  1e12, m)
// non-SI units
UNIT_DEFINITION(clength, inch, 0.0254, m)
UNIT_DEFINITION(clength, foot, 0.3048, m)
UNIT_DEFINITION(clength, feet, 0.3048, m)
UNIT_DEFINITION(clength, yard, 0.9144, m)
UNIT_DEFINITION(clength, mile, 1609.344, m)
UNIT_DEFINITION(clength, nautical_mile, 1853.184, m)
UNIT_DEFINITION(clength, ly,  9.4605284e15, m) // light year
UNIT_DEFINITION(clength, au,  1.49597871e11, m) // astronomical unit
        
// Area 
QUANTITY_DEFINITION_START(carea, m2)
QUANTITY_DEFINITION_END(carea, m2)
// SI units
UNIT_DEFINITION(carea, mm2, 1e-6, m2)
UNIT_DEFINITION(carea, cm2, 1e-4, m2)
UNIT_DEFINITION(carea, dm2, 1e-2, m2)
UNIT_DEFINITION(carea, km2, 1e6,  m2)
// non-SI units
UNIT_DEFINITION(carea, are, 1e2,  m2)
UNIT_DEFINITION(carea, ha,  1e4,  m2)
UNIT_DEFINITION(carea, acre, 4046.86, m2)
    
// Speed 
QUANTITY_DEFINITION_START(cspeed, m_per_s)
QUANTITY_DEFINITION_END(cspeed, m_per_s)
// SI units
UNIT_DEFINITION(cspeed, km_per_s, 1e-3, m_per_s)
UNIT_DEFINITION(cspeed, km_per_h, 3.6, m_per_s)
  
// Mass
QUANTITY_DEFINITION_START(cmass, kg)
QUANTITY_DEFINITION_END(cmass, kg)
// SI units
UNIT_DEFINITION(cmass, ug,  1e-9, kg)
UNIT_DEFINITION(cmass, mg,  1e-6, kg)    
UNIT_DEFINITION(cmass, g,   1e-3, kg)
UNIT_DEFINITION(cmass, ton, 1e3,  kg)
// non-SI units
UNIT_DEFINITION(cmass, stone, 6.35029, kg)
UNIT_DEFINITION(cmass, pound, 0.453592, kg)
UNIT_DEFINITION(cmass, ounce, 0.0283495, kg) 
   
// Time
QUANTITY_DEFINITION_START(cltime, s)
   friend cspeed operator / (const clength lhs, const cltime rhs);
QUANTITY_DEFINITION_END(cltime, s)
// SI units
UNIT_DEFINITION(cltime, ns,  1e-9, s)
UNIT_DEFINITION(cltime, us,  1e-6, s)    
UNIT_DEFINITION(cltime, ms,  1e-3, s)
UNIT_DEFINITION(cltime, min, 60,   s)
UNIT_DEFINITION(cltime, h,   3600, s)
UNIT_DEFINITION(cltime, day, 86400,s)
UNIT_DEFINITION(cltime, week, 604800, s)
UNIT_DEFINITION(cltime, month, 2.63e+6, s)
UNIT_DEFINITION(cltime, year,  3.156e+7, s)
UNIT_DEFINITION(cltime, decade, 3.156e+8, s)
UNIT_DEFINITION(cltime, century, 3.156e+9, s)
    
// Operations that change quantity (Can there be others except multiplication and division?)
  
inline carea  operator * (const clength lhs, const clength rhs) {return operator "" _m2_(lhs.value *  rhs.value);}
inline cspeed operator / (const clength lhs, const cltime  rhs) {return operator "" _m_per_s_(lhs.value /  rhs.value);}

} } // namespace mzlib::units

#endif // UNITS_H

