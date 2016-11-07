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
   
enum class edirection { n, ne, e, se, s, sw, w, nw };

inline edirection the_opposite_direction (edirection direction)
{
   switch(direction) {
      case edirection::ne: return edirection::sw;
      case edirection::sw: return edirection::ne;
      
      case edirection::nw: return edirection::se;
      case edirection::se: return edirection::nw;

      case edirection::n: return edirection::s;
      case edirection::s: return edirection::n;

      case edirection::e: return edirection::w;
      case edirection::w: return edirection::e;
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
      case mzlib::edirection::n:  os <<  "n"; break;
      case mzlib::edirection::s:  os <<  "s"; break;
      case mzlib::edirection::w:  os <<  "w"; break;
      case mzlib::edirection::e:  os <<  "e"; break;
      
      default: os << "unknown"; break;
   };
   return os;
}

#endif	/* MZLIB_DIRECTION_H */

