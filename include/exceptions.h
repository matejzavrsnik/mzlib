//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef EXCEPTIONS_H
#define	EXCEPTIONS_H

namespace mzlib {
namespace exception {
   
class is_empty : public std::exception {};
class not_set : public std::exception {};
      
} } // namespace mzlib::exception

#endif // EXCEPTIONS_H

