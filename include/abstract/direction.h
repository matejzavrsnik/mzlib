//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_DIRECTION_H
#define	MZLIB_DIRECTION_H

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
      
      // The following is not the best thing ever, but it does keep compiler
      // warnings away. As soon as I invent direction::unknown I would have to
      // account for it everywhere, if I throw I would have to catch everywhere.
      // This is simple function, let it remain simple. There are not many simple
      // things in the world today and that makes them so much more precious :)
      // Besides, "should never happen" anyway, right?
      default: return direction::centre;
   }
}

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
   }
   return os;
}

} // namespace

#endif	/* MZLIB_DIRECTION_H */

