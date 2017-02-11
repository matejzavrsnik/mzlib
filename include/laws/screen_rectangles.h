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

// Why did I think it's worth having screen rectangles operations separate from
// the class, you say? First is that something like diagonal_length is derived
// from top_right and bottom_left, and if it was stored next to the two defining
// points, it would be duplicate information and it would ruin the orthogonality
// of the class design. First problem with that is that it would need careful 
// and active maintenance to keep correct or risk bugs, and second problem is 
// that it consumes additional memory even in cases where the user of the class 
// doesn't need diagonal_length. And if it was just diagonal_length, then fine,
// but it isn't. Second, operations that can be implemented as a non-member non-
// friends, should be. This is slightly ideological point, but it is a good guideline
// in keeping everything simpler and also enforcing the first point.
   
template <class VectorT>
class screen_rectangles
{

public:
      
   optional<VectorT> m_top_right;
   optional<VectorT> m_bottom_left;   
   optional<VectorT> m_top_left;
   optional<VectorT> m_bottom_right;
   optional<VectorT> m_centre_point;

   optional<double>  m_diagonal_length;
   optional<double>  m_width;
   optional<double>  m_height;

   void consider(const screen_rectangle<VectorT>& rectangle)
   {
      m_top_left = rectangle.get_top_left();
      m_bottom_right = rectangle.get_bottom_right();
   }
   
   const double& solve_for_diagonal_length() const
   {
      if (m_diagonal_length.is_set()) {
         return m_diagonal_length.get();
      }
      
      const_cast<optional<double>&>(m_diagonal_length) = m_top_left.get().distance_to(m_bottom_right.get());
      return m_diagonal_length.get();      
   }
   
   const double& solve_for_width () const
   {
      if (m_width.is_set()) {
         return m_width.get();
      }

      const_cast<optional<double>&>(m_width) = m_bottom_right.get()[0] - m_top_left.get()[0];
      return m_width.get();
   }
   
   const double& solve_for_height () const
   {
      if (m_height.is_set()) {
         return m_height.get();
      }

      const_cast<optional<double>&>(m_height) = m_bottom_right.get()[1] - m_top_left.get()[1];
      return m_height.get();
   }
   
   bool is_in (const vector2d& location) const
   {  
      if (location[0] >  m_top_left.get()[0] && 
          location[1] >  m_top_left.get()[1] &&   // left and top are exclusive
          location[0] <= m_bottom_right.get()[0] && 
          location[1] <= m_bottom_right.get()[1]) // right and bottom are inclusive 
      { 
         return true;
      }
      
      return false;
   }
   
   VectorT solve_for_centre_point () const
   {
      if (m_centre_point.is_set()) {
         return m_centre_point.get();
      }

      const_cast<optional<VectorT>&>(m_centre_point) = m_top_left.get() + ((m_bottom_right.get() - m_top_left.get()) / 2);
      return m_centre_point.get();
   }
   
   direction solve_for_direction_of_point (const vector2d& point) const
   {
      solve_for_centre_point ();
      
      if (point[0] <= m_centre_point.get()[0]) {    // if on the edge, west wins
         if (point[1] < m_centre_point.get()[1]) {  // if on the edge, south wins
            return direction::nw;
         }
         else {
            return direction::sw;
         }
      }
      else {
         if (point[1] < m_centre_point.get()[1]) {
            return direction::ne;
         }
         else {
            return direction::se;
         }
      }
   }
   
   screen_rectangle<VectorT> enlarge_rectangle (direction direction, double factor) const
   {
      solve_for_height ();
      solve_for_width ();
      
      VectorT top_left = m_top_left.get();
      VectorT bottom_right = m_bottom_right.get();

      const double height_delta = factor * m_height.get() - m_height.get();
      const double width_delta = factor * m_width.get() - m_width.get();
      
      switch(direction) {
         case direction::ne:
            top_left[1] -= height_delta;
            bottom_right[0] += width_delta;
            break;
         case direction::nw:
            top_left[0] -= width_delta;
            top_left[1] -= height_delta;
            break;
         case direction::se: 
            bottom_right[0] += width_delta;
            bottom_right[1] += height_delta;
            break;
         case direction::sw: 
            top_left[0] -= width_delta;
            bottom_right[1] += height_delta;
            break;
         default:
            throw exception::not_implemented();
            break;
      }
      screen_rectangle<VectorT> rectangle(top_left, bottom_right);
      return rectangle;
   }
   
   screen_rectangle<VectorT> flip (direction direction) const
   {
      VectorT top_left = m_top_left.get();
      VectorT bottom_right = m_bottom_right.get();
      
      solve_for_height ();
      solve_for_width ();
      
      switch (direction) 
      {
         case direction::n:
            top_left    [1] -= m_height.get();
            bottom_right[1] -= m_height.get();
            break;
         case direction::s:
            top_left    [1] += m_height.get();
            bottom_right[1] += m_height.get();
            break;
         case direction::w: 
            top_left    [0] -= m_width.get();
            bottom_right[0] -= m_width.get();
            break;
         case direction::e:
            top_left    [0] += m_width.get();
            bottom_right[0] += m_width.get();
            break;
         case direction::ne:
            top_left    [0] += m_width.get();
            top_left    [1] -= m_height.get();
            bottom_right[0] += m_width.get();
            bottom_right[1] -= m_height.get();
            break;
         case direction::nw:
            top_left    [0] -= m_width.get();
            top_left    [1] -= m_height.get();
            bottom_right[0] -= m_width.get();
            bottom_right[1] -= m_height.get();
            break;
         case direction::se: 
            top_left    [0] += m_width.get();
            top_left    [1] += m_height.get();
            bottom_right[0] += m_width.get();
            bottom_right[1] += m_height.get();
            break;
         case direction::sw:
            top_left    [0] -= m_width.get();
            top_left    [1] += m_height.get();
            bottom_right[0] -= m_width.get();
            bottom_right[1] += m_height.get();
            break;
         default:
            throw exception::not_implemented();
            break;
      }
      screen_rectangle<VectorT> rectangle;
      rectangle.set_top_left(top_left);
      rectangle.set_bottom_right(bottom_right);
      return rectangle;
   }
   
};
   
using screen_rectangles2d = screen_rectangles<vector2d>;

} } // namespace

#endif /* MZLIB_LAWS_RECTANGLES_H */

