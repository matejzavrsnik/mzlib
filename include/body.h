//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_BODY_H
#define	MZLIB_BODY_H

#include "vector.h"
#include "mass_centre.h"
#include "unique.h"

namespace mzlib {
   
template <class VectorT>
class cbody_forces
{
   
public:
        
   VectorT gravity;
   VectorT velocity;

};

template <class VectorT>
class cbody_properties : public cbody_forces<VectorT>, public cunique 
{

public:
   
   bool operator== (const cbody_properties& other) const
   {
      if (&other == this) {
         return true;
      }
      return (this->id() == other.id());
   }
   
   bool operator!= (const cbody_properties& other) const
   {
      return !(*this == other);
   }
};

using cbody_properties2d = cbody_properties<cvector2d>;
using cbody_properties3d = cbody_properties<cvector3d>;
using cbody2d = cbinded_mass_centre2d<cbody_properties2d>;
using cbody3d = cbinded_mass_centre3d<cbody_properties3d>;

   // todo: find better place
   enum class edirection { ne, nw, se, sw };

template <class VectorT>
class crectangle
{
   
private:

   const double m_not_set_mark = -1;
   double m_diagonal_length = m_not_set_mark;
   double m_width = m_not_set_mark;
   double m_height = m_not_set_mark;
   
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
   
   const double& get_heigth () const
   {
      if (m_height == m_not_set_mark) {
         // todo: correct only in 2d and if straight but is easy to improve
         const_cast<double&>(m_height) = m_bottom_right[1] - m_top_left[1];
      }
      
      return m_height;
   }
   
   edirection direction_of_point (const cvector2d& point) const
   {
      VectorT centre_point = m_top_left + ((m_bottom_right - m_top_left) / 2);
      if (point[0] <= centre_point[0]) {
         if (point[1] <= centre_point[1]) {
            return edirection::se;
         }
         else {
            return edirection::sw;
         }
      }
      else {
         if (point[1] <= centre_point[1]) {
            return edirection::ne;
         }
         else {
            return edirection::nw;
         }
      }
   }
   
};

} // namespace

#endif	/* MZLIB_BODY_H */

