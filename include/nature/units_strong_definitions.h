//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_UNITS_STRONG_DEFINITIONS_H
#define MZLIB_UNITS_STRONG_DEFINITIONS_H

#include "units_strong_foundation.h"

namespace mzlib {
   
// Necessary forward declarations; because units are dependent on each other.
// Example: length * length = area, area / length = length. Which one to define first?
class area; class speed; class time_unit; class length;    
    
// Length
MZ_QUANTITY_DEFINITION_START(length, m)
   friend area operator* (const length& lhs, const length& rhs);
   friend length operator/ (const area& lhs, const length& rhs);
   friend speed operator/ (const length& lhs, const time_unit& rhs);
   friend time_unit operator/ (const length& lhs, const speed& rhs);
MZ_QUANTITY_DEFINITION_END(length, m)
// SI units
MZ_UNIT_DEFINITION(length, nm,  1e-9, m)
MZ_UNIT_DEFINITION(length, um,  1e-6, m)
MZ_UNIT_DEFINITION(length, mm,  1e-3, m)
MZ_UNIT_DEFINITION(length, cm,  1e-2, m)
MZ_UNIT_DEFINITION(length, dm,  1e-1, m)
MZ_UNIT_DEFINITION(length, dam, 1e1,  m)
MZ_UNIT_DEFINITION(length, hm,  1e2,  m)
MZ_UNIT_DEFINITION(length, km,  1e3,  m)
MZ_UNIT_DEFINITION(length, Mm,  1e6,  m)
MZ_UNIT_DEFINITION(length, Gm,  1e9,  m)
MZ_UNIT_DEFINITION(length, Tm,  1e12, m)
// non-SI units
MZ_UNIT_DEFINITION(length, inch, 0.0254, m)
MZ_UNIT_DEFINITION(length, foot, 0.3048, m)
MZ_UNIT_DEFINITION(length, feet, 0.3048, m)
MZ_UNIT_DEFINITION(length, yard, 0.9144, m)
MZ_UNIT_DEFINITION(length, mile, 1609.344, m)
MZ_UNIT_DEFINITION(length, nautical_mile, 1853.184, m)
MZ_UNIT_DEFINITION(length, ly,  9.4605284e15, m) // light year
MZ_UNIT_DEFINITION(length, au,  1.49597871e11, m) // astronomical unit
        
// Area 
MZ_QUANTITY_DEFINITION_START(area, m2)
   friend length operator/ (const area& lhs, const length& rhs);
MZ_QUANTITY_DEFINITION_END(area, m2)
// SI units
MZ_UNIT_DEFINITION(area, mm2, 1e-6, m2)
MZ_UNIT_DEFINITION(area, cm2, 1e-4, m2)
MZ_UNIT_DEFINITION(area, dm2, 1e-2, m2)
MZ_UNIT_DEFINITION(area, km2, 1e6,  m2)
// non-SI units
MZ_UNIT_DEFINITION(area, are, 1e2,  m2)
MZ_UNIT_DEFINITION(area, ha,  1e4,  m2)
MZ_UNIT_DEFINITION(area, acre, 4046.86, m2)
    
// Speed 
MZ_QUANTITY_DEFINITION_START(speed, m_per_s)
   friend length operator* (const speed& lhs, const time_unit& rhs);
   friend time_unit operator/ (const length& lhs, const speed& rhs);
MZ_QUANTITY_DEFINITION_END(speed, m_per_s)
// SI units
MZ_UNIT_DEFINITION(speed, km_per_s, 1e-3, m_per_s)
MZ_UNIT_DEFINITION(speed, km_per_h, 0.2777, m_per_s)
  
// Mass
MZ_QUANTITY_DEFINITION_START(mass, kg)
MZ_QUANTITY_DEFINITION_END(mass, kg)
// SI units
MZ_UNIT_DEFINITION(mass, ug,  1e-9, kg)
MZ_UNIT_DEFINITION(mass, mg,  1e-6, kg)    
MZ_UNIT_DEFINITION(mass, g,   1e-3, kg)
MZ_UNIT_DEFINITION(mass, ton, 1e3,  kg)
// non-SI units
MZ_UNIT_DEFINITION(mass, stone, 6.35029, kg)
MZ_UNIT_DEFINITION(mass, pound, 0.453592, kg)
MZ_UNIT_DEFINITION(mass, ounce, 0.0283495, kg) 
   
// Time
MZ_QUANTITY_DEFINITION_START(time_unit, s)
   friend speed operator/ (const length& lhs, const time_unit& rhs);
   friend length operator* (const speed& lhs, const time_unit& rhs);
MZ_QUANTITY_DEFINITION_END(time_unit, s)
// SI units
MZ_UNIT_DEFINITION(time_unit, ns,  1e-9, s)
MZ_UNIT_DEFINITION(time_unit, us,  1e-6, s)    
MZ_UNIT_DEFINITION(time_unit, ms,  1e-3, s)
MZ_UNIT_DEFINITION(time_unit, min, 60,   s)
MZ_UNIT_DEFINITION(time_unit, h,   3600, s)
MZ_UNIT_DEFINITION(time_unit, day, 86400,s)
MZ_UNIT_DEFINITION(time_unit, week, 604800, s)
MZ_UNIT_DEFINITION(time_unit, month, 2.63e+6, s)
MZ_UNIT_DEFINITION(time_unit, year,  3.156e+7, s)
MZ_UNIT_DEFINITION(time_unit, decade, 3.156e+8, s)
MZ_UNIT_DEFINITION(time_unit, century, 3.156e+9, s)
    
// Operations that change quantity (Can there be others except multiplication and division?)
  
inline area operator* (const length& lhs, const length& rhs) 
{
   return operator "" _m2_(lhs.value * rhs.value);
}

inline speed operator/ (const length& lhs, const time_unit&  rhs) 
{
   return operator "" _m_per_s_(lhs.value / rhs.value);
}

inline length operator/ (const area& lhs, const length& rhs)
{
   return operator "" _m_(lhs.value / rhs.value);
}

inline length operator* (const speed& lhs, const time_unit& rhs)
{
   return operator "" _m_(lhs.value * rhs.value);
}

inline time_unit operator/ (const length& lhs, const speed& rhs)
{
   return operator "" _s_(lhs.value / rhs.value);
}

// Don't undef, user might want to create own
//#undef MZ_QUANTITY_DEFINITION_START
//#undef MZ_QUANTITY_DEFINITION_END
//#undef MZ_UNIT_DEFINITION

} // namespace

#endif // MZLIB_UNITS_STRONG_DEFINITIONS_H
