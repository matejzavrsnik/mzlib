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

namespace mzlib {
   
   // remove to own file and extract laws out of it
template <class VectorT>
class crectangle
{
   
private:

   // todo: this is all wrong, fix
   const double m_not_set_mark = -1;
   double m_diagonal_length = m_not_set_mark;
   double m_width = m_not_set_mark;
   double m_height = m_not_set_mark;
   VectorT m_top_right;
   VectorT m_bottom_left;
   
   
   VectorT m_top_left;
   VectorT m_bottom_right;
   
public:

   void set_top_left(const VectorT& top_left)
   {
      m_top_left = top_left;
      m_diagonal_length = m_not_set_mark;
   }

   const VectorT& get_top_left() const
   {
      return m_top_left;
   }
   
   void set_bottom_right(const VectorT& bottom_right)
   {
      m_bottom_right = bottom_right;
      m_diagonal_length = m_not_set_mark;
   }

   const VectorT& get_bottom_right() const
   {
      return m_bottom_right;
   }

   bool is_in (const cvector2d& location) const
   {
      if (location[0] >  m_top_left[0] && 
          location[1] >  m_top_left[1] &&   // left and top are exclusive
          location[0] <= m_bottom_right[0] && 
          location[1] <= m_bottom_right[1]) // right and bottom are inclusive 
      { 
         return true;
      }
      return false;
   }
   
   const double& get_diagonal_length() const
   {
      if(m_diagonal_length == m_not_set_mark) {
         const_cast<double&>(m_diagonal_length) = m_top_left.distance_to(m_bottom_right);
      }
      
      return m_diagonal_length;
   }
   
   const double& get_width () const
   {
      if (m_width == m_not_set_mark) {
         // todo: correct only in 2d and if straight but is easy to improve
         const_cast<double&>(m_width) = m_bottom_right[0] - m_top_left[0];
      }
      
      return m_width;
   }
   
   const double& get_height () const
   {
      if (m_height == m_not_set_mark) {
         // todo: correct only in 2d and if straight but is easy to improve
         const_cast<double&>(m_height) = m_bottom_right[1] - m_top_left[1];
      }
      
      return m_height;
   }
   
   VectorT calculate_centre_point () const
   {
      VectorT centre_point = m_top_left + ((m_bottom_right - m_top_left) / 2);
      return centre_point;
   }
   
   edirection direction_of_point (const cvector2d& point) const
   {
      VectorT centre_point = calculate_centre_point ();
      if (point[0] <= centre_point[0]) {    // if on the edge, west wins
         if (point[1] < centre_point[1]) {  // if on the edge, south wins
            return edirection::nw;
         }
         else {
            return edirection::sw;
         }
      }
      else {
         if (point[1] < centre_point[1]) {
            return edirection::ne;
         }
         else {
            return edirection::se;
         }
      }
   }
   
   crectangle enlarge_rectangle (edirection direction, double factor) const
   {
      VectorT top_left = m_top_left;
      VectorT bottom_right = m_bottom_right;
      double height = get_height ();
      double width = get_width ();
      double height_delta = factor * height - height;
      double width_delta = factor * width - width;
      switch(direction) {
         case edirection::ne:
            top_left[1] -= height_delta;
            bottom_right[0] += width_delta;
            break;
         case edirection::nw:
            top_left[0] -= width_delta;
            top_left[1] -= height_delta;
            break;
         case edirection::se: 
            bottom_right[0] += width_delta;
            bottom_right[1] += height_delta;
            break;
         case edirection::sw: 
            top_left[0] -= width_delta;
            bottom_right[1] += height_delta;
            break;
      }
      crectangle rectangle;
      rectangle.m_top_left = top_left;
      rectangle.m_bottom_right = bottom_right;
      return rectangle;
   }
   
};

using crectangle2d = crectangle<cvector2d>;
using crectangle3d = crectangle<cvector3d>;

} // namespace

#endif	/* MZLIB_RECTANGLE_H */

