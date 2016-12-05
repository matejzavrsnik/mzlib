//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_RECTANGLE_H
#define	MZLIB_RECTANGLE_H

#include "vector.h"
#include "direction.h"
#include "exceptions.h"
#include "optional.h"

namespace mzlib {
   
template <class VectorT>
class rectangle
{
   
private:

   optional<double>  m_diagonal_length;
   optional<double>  m_width;
   optional<double>  m_height;
   optional<VectorT> m_top_right;
   optional<VectorT> m_bottom_left;
   
   optional<VectorT> m_top_left;
   optional<VectorT> m_bottom_right;
   
public:

   rectangle (
      const VectorT& top_left, 
      const VectorT& bottom_right) :
         m_top_left (top_left),
         m_bottom_right (bottom_right)
   { 
   }

   rectangle () = default;
   rectangle& operator= (const rectangle<VectorT>&) = default;
   rectangle (const rectangle<VectorT>&) = default; 
   rectangle (rectangle<VectorT> && ) = default;
   rectangle& operator= (rectangle<VectorT>&&) = default;
   ~rectangle () = default;
   
   bool is_defined() const
   {
      return m_top_left.is_set() && m_bottom_right.is_set();
   }
   
   void set_top_left(const VectorT& top_left)
   {
      m_top_left = top_left;
   }

   const VectorT& get_top_left() const
   {
      return m_top_left.get();
   }
   
   void set_bottom_right(const VectorT& bottom_right)
   {
      m_bottom_right = bottom_right;
   }

   const VectorT& get_bottom_right() const
   {
      return m_bottom_right.get();
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
   
   const double& get_width () const
   {
      if (m_width.is_set()) {
         return m_width.get();
      }
      // todo: correct only in 2d and if straight but is easy to improve
      const_cast<optional<double>&>(m_width) = m_bottom_right.get()[0] - m_top_left.get()[0];
      return m_width.get();
   }
   
   const double& get_height () const
   {
      if (m_height.is_set()) {
         return m_height.get();
      }
      // todo: correct only in 2d and if straight but is easy to improve
      const_cast<optional<double>&>(m_height) = m_bottom_right.get()[1] - m_top_left.get()[1];
      return m_height.get();
   }
   
   VectorT calculate_centre_point () const
   {
      VectorT centre_point = m_top_left.get() + ((m_bottom_right.get() - m_top_left.get()) / 2);
      return centre_point;
   }
   
   direction direction_of_point (const vector2d& point) const
   {
      VectorT centre_point = calculate_centre_point ();
      if (point[0] <= centre_point[0]) {    // if on the edge, west wins
         if (point[1] < centre_point[1]) {  // if on the edge, south wins
            return direction::nw;
         }
         else {
            return direction::sw;
         }
      }
      else {
         if (point[1] < centre_point[1]) {
            return direction::ne;
         }
         else {
            return direction::se;
         }
      }
   }
   
   rectangle<VectorT> enlarge_rectangle (direction direction, double factor) const
   {
      VectorT top_left = m_top_left.get();
      VectorT bottom_right = m_bottom_right.get();
      const double& height = get_height ();
      const double& width = get_width ();
      const double height_delta = factor * height - height;
      const double width_delta = factor * width - width;
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
      rectangle<VectorT> rectangle(top_left, bottom_right);
      return rectangle;
   }
   
   rectangle<VectorT> flip (direction direction) const
   {
      VectorT top_left = m_top_left.get();
      VectorT bottom_right = m_bottom_right.get();
      const double& height = get_height ();
      const double& width = get_width ();
      switch (direction) 
      {
         case direction::n:
            top_left    [1] -= height;
            bottom_right[1] -= height;
            break;
         case direction::s:
            top_left    [1] += height;
            bottom_right[1] += height;
            break;
         case direction::w: 
            top_left    [0] -= width;
            bottom_right[0] -= width;
            break;
         case direction::e:
            top_left    [0] += width;
            bottom_right[0] += width;
            break;
         case direction::ne:
            top_left    [0] += width;
            top_left    [1] -= height;
            bottom_right[0] += width;
            bottom_right[1] -= height;
            break;
         case direction::nw:
            top_left    [0] -= width;
            top_left    [1] -= height;
            bottom_right[0] -= width;
            bottom_right[1] -= height;
            break;
         case direction::se: 
            top_left    [0] += width;
            top_left    [1] += height;
            bottom_right[0] += width;
            bottom_right[1] += height;
            break;
         case direction::sw:
            top_left    [0] -= width;
            top_left    [1] += height;
            bottom_right[0] -= width;
            bottom_right[1] += height;
            break;
         default:
            throw exception::not_implemented();
            break;
      }
      rectangle<VectorT> rectangle;
      rectangle.m_top_left = top_left;
      rectangle.m_bottom_right = bottom_right;
      return rectangle;
   }
   
};

using crectangle2d = rectangle<vector2d>;
using crectangle3d = rectangle<vector3d>;

} // namespace

#endif	/* MZLIB_RECTANGLE_H */

