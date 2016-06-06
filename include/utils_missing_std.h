//
// Not all code here is entirely written by me.
// Details beside every piece of code
//
// Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef UTILS_MISSING_STD_H
#define	UTILS_MISSING_STD_H

// in anticipation of adoption of the newer c++ standard
namespace std {

// Herb Sutter's implementiation suggestion   
template<typename T, typename ...Args>
std::unique_ptr<T> make_unique( Args&& ...args )
{
    return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}
   
} // namespace std

#endif	/* UTILS_MISSING_STD_H */

