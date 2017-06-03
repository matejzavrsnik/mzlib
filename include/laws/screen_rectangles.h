//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_LAWS_SCREEN_RECTANGLES_H
#define	MZLIB_LAWS_SCREEN_RECTANGLES_H

#include "../lang/optional.h"
#include "../nature/screen_rectangle.h"

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
      
   optional<VectorT> top_right;
   optional<VectorT> bottom_left;   
   optional<VectorT> top_left;
   optional<VectorT> bottom_right;
   optional<VectorT> centre_point;

   optional<double>  diagonal_length;
   optional<double>  width;
   optional<double>  height;

   void consider(const screen_rectangle<VectorT>& rectangle)
   {
      top_left = rectangle.get_top_left();
      bottom_right = rectangle.get_bottom_right();
   }
   
   const double& solve_for_diagonal_length() const
   {
      if (diagonal_length.is_set()) {
         return diagonal_length.get();
      }
      
      const_cast<optional<double>&>(diagonal_length) = top_left.get().distance_to(bottom_right.get());
      return diagonal_length.get();      
   }
   
   const double& solve_for_width () const
   {
      if (width.is_set()) {
         return width.get();
      }

      const_cast<optional<double>&>(width) = bottom_right.get()[0] - top_left.get()[0];
      return width.get();
   }
   
   const double& solve_for_height () const
   {
      if (height.is_set()) {
         return height.get();
      }

      const_cast<optional<double>&>(height) = bottom_right.get()[1] - top_left.get()[1];
      return height.get();
   }
   
   bool is_in (const vector2d& location) const
   {  
      if (location[0] >  top_left.get()[0] && 
          location[1] >  top_left.get()[1] &&   // left and top are exclusive
          location[0] <= bottom_right.get()[0] && 
          location[1] <= bottom_right.get()[1]) // right and bottom are inclusive 
      { 
         return true;
      }
      
      return false;
   }
   
   VectorT solve_for_centre_point () const
   {
      if (centre_point.is_set()) {
         return centre_point.get();
      }

      const_cast<optional<VectorT>&>(centre_point) = top_left.get() + ((bottom_right.get() - top_left.get()) / 2);
      return centre_point.get();
   }
   
   direction solve_for_direction_of_point (const vector2d& point) const
   {
      solve_for_centre_point ();
      
      if (point[0] <= centre_point.get()[0]) {    // if on the edge, west wins
         if (point[1] < centre_point.get()[1]) {  // if on the edge, south wins
            return direction::nw;
         }
         else {
            return direction::sw;
         }
      }
      else {
         if (point[1] < centre_point.get()[1]) {
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
      
      VectorT new_top_left = top_left.get();
      VectorT new_bottom_right = bottom_right.get();

      const double height_delta = factor * height.get() - height.get();
      const double width_delta = factor * width.get() - width.get();
      
      switch(direction) {
         case direction::ne:
            new_top_left[1] -= height_delta;
            new_bottom_right[0] += width_delta;
            break;
         case direction::nw:
            new_top_left[0] -= width_delta;
            new_top_left[1] -= height_delta;
            break;
         case direction::se: 
            new_bottom_right[0] += width_delta;
            new_bottom_right[1] += height_delta;
            break;
         case direction::sw: 
            new_top_left[0] -= width_delta;
            new_bottom_right[1] += height_delta;
            break;
         default:
            throw exception::not_implemented();
            break;
      }
      screen_rectangle<VectorT> new_rectangle(new_top_left, new_bottom_right);
      return new_rectangle;
   }
   
   screen_rectangle<VectorT> flip (direction direction) const
   {
      VectorT new_top_left = top_left.get();
      VectorT new_bottom_right = bottom_right.get();
      
      solve_for_height ();
      solve_for_width ();
      
      switch (direction) 
      {
         case direction::n:
            new_top_left    [1] -= height.get();
            new_bottom_right[1] -= height.get();
            break;
         case direction::s:
            new_top_left    [1] += height.get();
            new_bottom_right[1] += height.get();
            break;
         case direction::w: 
            new_top_left    [0] -= width.get();
            new_bottom_right[0] -= width.get();
            break;
         case direction::e:
            new_top_left    [0] += width.get();
            new_bottom_right[0] += width.get();
            break;
         case direction::ne:
            new_top_left    [0] += width.get();
            new_top_left    [1] -= height.get();
            new_bottom_right[0] += width.get();
            new_bottom_right[1] -= height.get();
            break;
         case direction::nw:
            new_top_left    [0] -= width.get();
            new_top_left    [1] -= height.get();
            new_bottom_right[0] -= width.get();
            new_bottom_right[1] -= height.get();
            break;
         case direction::se: 
            new_top_left    [0] += width.get();
            new_top_left    [1] += height.get();
            new_bottom_right[0] += width.get();
            new_bottom_right[1] += height.get();
            break;
         case direction::sw:
            new_top_left    [0] -= width.get();
            new_top_left    [1] += height.get();
            new_bottom_right[0] -= width.get();
            new_bottom_right[1] += height.get();
            break;
         default:
            throw exception::not_implemented();
            break;
      }
      screen_rectangle<VectorT> new_rectangle;
      new_rectangle.set_top_left(new_top_left);
      new_rectangle.set_bottom_right(new_bottom_right);
      return new_rectangle;
   }
   
};
   
using screen_rectangles2d = screen_rectangles<vector2d>;

} } // namespace

#endif /* MZLIB_LAWS_SCREEN_RECTANGLES_H */

