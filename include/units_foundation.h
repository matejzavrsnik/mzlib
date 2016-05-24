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

} } // namespace mzlib::units

#endif // UNITS_FOUNDATION_H

