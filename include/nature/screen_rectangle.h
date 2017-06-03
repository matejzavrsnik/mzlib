//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_RECTANGLE_H
#define	MZLIB_RECTANGLE_H

#include "vector.h"
#include "../abstract/direction.h"
#include "../lang/exceptions.h"
#include "../lang/optional.h"

namespace mzlib {
   
template <class VectorT>
class screen_rectangle
{
   
private:
   
   optional<VectorT> m_top_left;
   optional<VectorT> m_bottom_right;
   
public:

   screen_rectangle (
      const VectorT& top_left, 
      const VectorT& bottom_right) :
         m_top_left (top_left),
         m_bottom_right (bottom_right)
   { 
   }

   screen_rectangle () = default;
   screen_rectangle& operator= (const screen_rectangle<VectorT>&) = default;
   screen_rectangle (const screen_rectangle<VectorT>&) = default; 
   screen_rectangle (screen_rectangle<VectorT> && ) = default;
   screen_rectangle& operator= (screen_rectangle<VectorT>&&) = default;
   ~screen_rectangle () = default;
   
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
   
   bool is_defined() const
   {
      return m_top_left.is_set() && m_bottom_right.is_set();
   }
   
};

using screen_rectangle2d = screen_rectangle<vector2d>;
using screen_rectangle3d = screen_rectangle<vector3d>;

} // namespace

#endif	/* MZLIB_RECTANGLE_H */

