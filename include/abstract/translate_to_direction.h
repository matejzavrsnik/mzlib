//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//
#pragma once

#include <abstract/direction.h>

namespace mzlib
{

inline direction
translate_to_direction (char dir)
{
   switch (dir)
   {
   case 'L':
   case 'l':
   case 'W':
   case 'w':
      return direction::w;
   case 'R':
   case 'r':
   case 'E':
   case 'e':
      return direction::e;
   case 'U':
   case 'u':
   case 'N':
   case 'n':
      return direction::n;
   case 'D':
   case 'd':
   case 'S':
   case 's':
      return direction::s;
   }
   std::terminate();
}

}
