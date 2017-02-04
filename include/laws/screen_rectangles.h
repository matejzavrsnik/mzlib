//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_LAWS_RECTANGLES_H
#define	MZLIB_LAWS_RECTANGLES_H

#include "../optional.h"
#include "../screen_rectangle.h"

namespace mzlib {
namespace law {
   
template <class VectorT>
class screen_rectangles
{

public:
      
   optional<VectorT> m_top_right;
   optional<VectorT> m_bottom_left;   
   optional<VectorT> m_top_left;
   optional<VectorT> m_bottom_right;

   optional<double>  m_diagonal_length;
   optional<double>  m_width;
   optional<double>  m_height;

   void consider(const screen_rectangle<VectorT>& rectangle)
   {
      m_top_left = rectangle.get_top_left();
      m_bottom_right = rectangle.get_bottom_right();
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
   
using screen_rectangles2d = screen_rectangles<vector2d>;

} } // namespace

#endif /* MZLIB_LAWS_RECTANGLES_H */

