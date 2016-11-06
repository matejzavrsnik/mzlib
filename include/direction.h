//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_DIRECTION_H
#define	MZLIB_DIRECTION_H

#include "vector.h"
#include <iostream> // operator<<

namespace mzlib {
   
enum class edirection { ne, nw, se, sw };

inline edirection the_opposite_direction (edirection direction)
{
   switch(direction) {
      case edirection::ne: return edirection::sw;
      case edirection::nw: return edirection::se;
      case edirection::se: return edirection::nw;
      case edirection::sw: return edirection::ne;
   }
}


} // namespace

inline std::ostream& operator<< (std::ostream& os, const mzlib::edirection& direction)
{
   switch(direction) {
      case mzlib::edirection::ne: os << "ne"; break;
      case mzlib::edirection::nw: os << "nw"; break;
      case mzlib::edirection::se: os << "se"; break;
      case mzlib::edirection::sw: os << "sw"; break;
      default: os << "unknown"; break;
   };
   return os;
}

#endif	/* MZLIB_DIRECTION_H */

