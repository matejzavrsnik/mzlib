//
// Copyright (c) 2019 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_LINEAR_INTERPOLATION_H
#define	MZLIB_LINEAR_INTERPOLATION_H

#include "../nature/vector.h"

namespace mzlib {
namespace law {
   
// pass in two points on a plane and x and you get y
inline double linear_interpolation(
   const mzlib::point2d& p1, 
   const mzlib::point2d& p2,
   const double p3_x)
{
   const double x_diff = p2[0] - p1[0];
   const double y_diff = p2[1] - p1[1];
   const double p1_to_x = p3_x - p1[0];
   const double ratio = p1_to_x / x_diff;
   const double one_to_y = y_diff * ratio;
   return p1[1] + one_to_y;
}

} } // namespace

#endif /* MZLIB_LINEAR_INTERPOLATION_H */
