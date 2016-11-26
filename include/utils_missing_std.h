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

// in anticipation of adoption of the newer c++ standard
namespace std {

#if __cplusplus < 201402L 
// Herb Sutter's implementiation suggestion   
template<typename T, typename ...Args>
std::unique_ptr<T> make_unique( Args&& ...args )
{
    return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}
#endif

} // namespace std

#endif	/* MZLIB_UTILS_MISSING_STD_H */

