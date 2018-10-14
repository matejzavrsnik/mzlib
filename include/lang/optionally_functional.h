//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_OPTIONALLY_FUNCTIONAL_H
#define MZLIB_OPTIONALLY_FUNCTIONAL_H

#include <optional>
#include <functional>

// Wrapper functions that allow for convenient use of
// std::optional as if they were normal values.

// Key to this is obviously handling the cases where the
// values are not defined. As a guideline in these cases
// I choose to return calculated result only if both values
// are defined, otherwise the result is undefined. I think
// that makes sense in most situations.

// Inspired by similar std function objects, but aren't
// injected into std namespace because some of them might
// result in incorrect results. For example: std::less
// returns bool, not the original type, so I could not avoid
// defining it. I could fudge my guideline above and
// say less is false if not both are defined, e.i.: can't
// confirm it's less; it's not less. But then in std::map for 
// example, equivalency is defined as !less(a,b) && !less(b,a).
// In this case if one of the parameters was not defined, 
// they would appear equivalent to std::map and there are 
// clearly no grounds for that claim.

namespace mzlib {
   
// Arithmetic operations 
   
template<typename T>
constexpr std::optional<T> plus (
   const std::optional<T>& lhs, 
   const std::optional<T>& rhs)
{
   return (lhs && rhs) ?
      std::optional<T>(*lhs + *rhs) :
      std::nullopt;
}

template<typename T>
constexpr std::optional<T> minus (
   const std::optional<T>& lhs, 
   const std::optional<T>& rhs)
{
   return (lhs && rhs) ?
      std::optional<T>(*lhs - *rhs) :
      std::nullopt;
}

template<typename T>
constexpr std::optional<T> multiplies (
   const std::optional<T>& lhs, 
   const std::optional<T>& rhs)
{
   return (lhs && rhs) ?
      std::optional<T>(*lhs * *rhs) :
      std::nullopt;
}

template<typename T>
constexpr std::optional<T> divides (
   const std::optional<T>& lhs, 
   const std::optional<T>& rhs)
{
   return (lhs && rhs) ?
      std::optional<T>(*lhs / *rhs) :
      std::nullopt;
}

template<typename T>
constexpr std::optional<T> modulus (
   const std::optional<T>& lhs, 
   const std::optional<T>& rhs)
{
   return (lhs && rhs) ?
      std::optional<T>(*lhs % *rhs) :
      std::nullopt;
}

template<typename T>
constexpr std::optional<T> negate (
   const std::optional<T>& val)
{
   return (val) ?
      std::optional<T>(-*val) :
      std::nullopt;
}

// Comparisons

// Should two undefined be equal?
// Should one undefined and other defined be not equal?
// For now I will not make the code attempt to be too clever.
// The demand stays: both need to be defined in order to get
// defined result. This way it's symmetric to other operations.

template<typename T>
constexpr std::optional<bool> equal_to (
   const std::optional<T>& lhs, 
   const std::optional<T>& rhs)
{
   return (lhs && rhs) ?
      std::optional<bool>(*lhs == *rhs) :
      std::nullopt;
}

template<typename T>
constexpr std::optional<bool> not_equal_to (
   const std::optional<T>& lhs, 
   const std::optional<T>& rhs)
{
   return (lhs && rhs) ?
      std::optional<bool>(*lhs != *rhs) :
      std::nullopt;
}

template<typename T>
constexpr std::optional<bool> greater (
   const std::optional<T>& lhs, 
   const std::optional<T>& rhs)
{
   return (lhs && rhs) ?
      std::optional<bool>(*lhs > *rhs) :
      std::nullopt;
}

template<typename T>
constexpr std::optional<bool> less (
   const std::optional<T>& lhs, 
   const std::optional<T>& rhs)
{
   return (lhs && rhs) ?
      std::optional<bool>(*lhs < *rhs) :
      std::nullopt;
}

template<typename T>
constexpr std::optional<bool> greater_equal (
   const std::optional<T>& lhs, 
   const std::optional<T>& rhs)
{
   return (lhs && rhs) ?
      std::optional<bool>(*lhs >= *rhs) :
      std::nullopt;
}

template<typename T>
constexpr std::optional<bool> less_equal (
   const std::optional<T>& lhs, 
   const std::optional<T>& rhs)
{
   return (lhs && rhs) ?
      std::optional<bool>(*lhs <= *rhs) :
      std::nullopt;
}

} // namespace

#endif // MZLIB_OPTIONALLY_FUNCTIONAL_H
