// 
// Author: Matej Zavrsnik (matejzavrsnik.com)
//

#ifndef UNITS_H
#define UNITS_H

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

} } // namespace mzlib::units

#endif // UNITS_H

