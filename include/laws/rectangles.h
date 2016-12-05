//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_LAWS_RECTANGLES_H
#define	MZLIB_LAWS_RECTANGLES_H

#include "../optional.h"
#include "../rectangle.h"

namespace mzlib {
namespace law {
   
template <class VectorT>
class rectangles
{

public:
      
   optional<VectorT> m_top_right;
   optional<VectorT> m_bottom_left;   
   optional<VectorT> m_top_left;
   optional<VectorT> m_bottom_right;

   optional<double>  m_diagonal_length;
   optional<double>  m_width;
   optional<double>  m_height;

   void consider(const rectangle<VectorT>& rectangle)
   {
      // I am counting on compiler support here. All conditions in this branch are
      // well known in compile time and it is well known that they can't change while
      // program will run. I've given it enough information to know that it is safe
      // to optimise away the branches altogether, so I hope this is what will happen.
      if (VectorT::dimensions() == 2) {
         m_top_left = rectangle.get_top_left();
         m_bottom_right = rectangle.get_bottom_right();
      }
      else {
         throw ::mzlib::exception::not_implemented(); // Yet. Also, todo  
      }
   }
   
   const double& solve_for_diagonal_length()
   {
      if (m_diagonal_length.is_set()) {
         return m_diagonal_length.get();
      }
      
      // generic solution, valid for all rectangles
      m_diagonal_length = m_top_left.get().distance_to(m_bottom_right.get());
      return m_diagonal_length.get();      
   }
};
   
using rectangles2d = rectangles<vector2d>;
using rectangleS3d = rectangles<vector3d>;

} } // namespace

#endif /* MZLIB_LAWS_RECTANGLES_H */

