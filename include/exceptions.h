//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_EXCEPTIONS_H
#define	MZLIB_EXCEPTIONS_H

#include <exception>

namespace mzlib {
// purpose of this nested namespace: it better explains the purpose of these class
// names when used in code. is_empty on itself means nothing, exception::is_empty
// does. To make it more readable using other means I would need to prepend
// "exception" to every class name, but that is better done using nested namespace.
namespace exception {
   
class is_empty : public std::exception {};
class not_set : public std::exception {};
class invalid_values : public std::exception {};
      
} } // namespace

#endif /* MZLIB_EXCEPTIONS_H */

