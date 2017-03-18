//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_DIRECTION_H
#define	MZLIB_DIRECTION_H

#include "../nature/vector.h"
#include "../exceptions.h"
#include <iostream> // operator<<

namespace mzlib {
   
enum class direction { n, ne, e, se, s, sw, w, nw, centre };

inline direction the_opposite_direction (direction direction)
{
   switch(direction) {
      case direction::ne: return direction::sw;
      case direction::sw: return direction::ne;
      
      case direction::nw: return direction::se;
      case direction::se: return direction::nw;

      case direction::n: return direction::s;
      case direction::s: return direction::n;

      case direction::e: return direction::w;
      case direction::w: return direction::e;
      
      case direction::centre: return direction::centre;
   }
   throw exception::meaningless();
}


} // namespace

inline std::ostream& operator<< (std::ostream& os, const mzlib::direction& direction)
{
   switch(direction) {
      case mzlib::direction::ne: os << "ne"; break;
      case mzlib::direction::nw: os << "nw"; break;
      case mzlib::direction::se: os << "se"; break;
      case mzlib::direction::sw: os << "sw"; break;
      case mzlib::direction::n:  os <<  "n"; break;
      case mzlib::direction::s:  os <<  "s"; break;
      case mzlib::direction::w:  os <<  "w"; break;
      case mzlib::direction::e:  os <<  "e"; break;
      case mzlib::direction::centre: os << "centre"; break;
      
      default: os << "unknown"; break;
   };
   return os;
}

#endif	/* MZLIB_DIRECTION_H */

