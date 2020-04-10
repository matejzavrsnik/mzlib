//
// Not all code here is entirely written by me.
// Details beside every piece of code
//
// Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_UTILS_MISSING_STD_H
#define	MZLIB_UTILS_MISSING_STD_H

#include <memory>
#include <type_traits>

// in anticipation of adoption of the newer c++ standard
namespace mzlib {

// Herb Sutter's implementiation suggestion   
template<typename T, typename ...Args>
std::unique_ptr<T> make_unique( Args&& ...args )
{
    return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}

// should be in <concepts>
namespace detail {
    template< class T, class U >
    concept bool SameHelper = std::is_same_v<T, U>;
}

template <class From, class To>
concept bool convertible_to =
   std::is_convertible_v<From, To> &&
   requires(std::add_rvalue_reference_t<From> (&f)()) {
      static_cast<To>(f());
   };
   
template< class T, class U >
concept bool same_as = detail::SameHelper<T, U> && detail::SameHelper<U, T>;

} // namespace

#endif	/* MZLIB_UTILS_MISSING_STD_H */

