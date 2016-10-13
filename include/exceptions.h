//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_EXCEPTIONS_H
#define	MZLIB_EXCEPTIONS_H

namespace mzlib {
namespace exception {
   
class is_empty : public std::exception {};
class not_set : public std::exception {};
      
} } // namespace mzlib::exception

#endif /* MZLIB_EXCEPTIONS_H */

