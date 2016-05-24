// 
// Author: Matej Zavrsnik (matejzavrsnik.com)
//

#ifndef UNITS_FOUNDATION_H
#define UNITS_FOUNDATION_H

#include <cmath> // std::fabs

namespace mzlib { 
namespace units {
    
// The base class. Implements CRTP and provides mathematical operations for all units

template<class unit>
class cquantity 
{

public:

   // A shorthand, and also a single place to change if needed
   typedef long double type;

protected:

   type value;
   constexpr cquantity (type v) : 
      value(v) 
   {
   }

public:
        
   // Must not be virtual to be trivial. Must be trivial to make class a literal type. 
   // Class must be literal to be used as constexpr object.
   ~cquantity () = default;

   // Comparison done with builder pattern. Demanding quantity from epsilon makes physical sense.
   unit equals (const unit& other  ) const 
   { 
      return unit(value -  other.value); 
   }

   bool within_epsilon (const unit& epsilon) const 
   { 
      return std::fabs(value) < epsilon.value; 
   }

   // Generic mathematical operations that all units can inherit

   unit& operator= (const unit& other) const { return other.value;  }

   // Can add and subtract same unit

   unit operator+= (const unit& other)
   { 
      return unit(value += other.value); 
   }

   unit operator+ (const unit& other) const 
   { 
      return unit(value +  other.value); 
   }

   unit operator-= (const unit& other)
   { 
      return unit(value -= other.value); 
   }

   unit operator- (const unit& other) const 
   { 
      return unit(value -  other.value); 
   }

   // Can divide by same unit, in which case the result is value without unit.

   type operator/ (const unit& other) const 
   { 
      return value / other.value; 
   }

   // Can divide by unitless value, result is the same unit
   
   unit operator/ (const type& other) const 
   { 
      return unit(value /  other); 
   }

   unit operator/= (const type& other)
   { 
      return unit(value /= other); 
   }

   // Can multiply with values that have no unit

   unit operator* (const type& other) const 
   { 
      return unit(value *  other); 
   }

   unit operator*= (const type& other)
   {
      return unit(value *= other);
   }

    // Some operations have no physical meaning:

    // Can't have operator/= because division produces value again, which can't be assigned to U
       // type operator /= (const unit& other)

    // Can't add and subtract values without unit. How much is 100m - 20 ?
       // unit operator += (const type& other)
       // unit operator +  (const type& other)
       // unit operator -= (const type& other)
       // unit operator -  (const type& other)

    // Valid operation, but it it will result in new quantity, so it needs to be defined later
       // unit operator *  (const unit& other)

    // Will result in new quantity which cannot be assigned to old quantity
       // unit operator *= (const unit& other)
       // unit operator %  (const unit& other)

    // Comparing floating point values is dangerous
       // bool operator == (const unit& other)
       // bool operator != (const unit& other)
};

// Followed by macros to help define every physical quantity

// I didn't find a way to generalise this using templates; templates can substitute types, not names of functions.
// Also couldn't use macros to batch-define all prefixes; there are no real rules to quantity names. 
// Think how hours and kilograms differ from meters, for instance.

// Base class is made friend so that it can call explicit constructor when implementing mathematical
// operations, because by using curiously recurring template pattern, it returns this exact type.

// Only string literal implementing basic unit of quantity has access to the constructor, all other 
// quantities literals are forced to use that one. This increases readability, because it makes clear 
// what the value inside class represents. It also increases readability of other quantities 
// definitions, because it makes clear how they are defined. It is also OK if it stays visible outside 
// of this file, because it is perfectly valid operation in itself.

// That means, that no one can instantiate length unit without providing unit quantity.
// Altogether it pretty much rules out any inadvertent mistakes in quantities.


#define QUANTITY_DEFINITION_START(q_class, q_basic) \
class q_class : public cquantity< q_class > { \
   friend class cquantity< q_class >; \
   friend constexpr q_class operator"" _##q_basic##_ (long double); \
   friend constexpr q_class operator"" _##q_basic##_ (unsigned long long int);

#define QUANTITY_DEFINITION_END(q_class, q_basic) \
protected: \
   explicit constexpr q_class (type v) : cquantity< q_class >(v) {} \
public: \
   constexpr q_class () : cquantity< q_class >(0) {} \
}; \
\
constexpr q_class operator"" _##q_basic##_ (long double v) { return q_class (v); } \
constexpr q_class operator"" _##q_basic##_ (unsigned long long int v) { return q_class (v); }

#define UNIT_DEFINITION(q_class, q_short, q_factor, q_basic) \
constexpr q_class operator"" _##q_short##_ (long double v) \
{ \
   return operator "" _##q_basic##_ ( v * (long double)q_factor ); \
} \
constexpr q_class operator"" _##q_short##_ (unsigned long long int v) \
{ \
   return operator "" _##q_basic##_ ( v * (long double)q_factor ); \
} 

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

#endif // UNITS_FOUNDATION_H

