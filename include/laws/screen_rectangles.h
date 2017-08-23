//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_LAWS_SCREEN_RECTANGLES_H
#define	MZLIB_LAWS_SCREEN_RECTANGLES_H

#include <optional>

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
      
   std::optional<VectorT> top_right;
   std::optional<VectorT> bottom_left;   
   std::optional<VectorT> top_left;
   std::optional<VectorT> bottom_right;
   std::optional<VectorT> centre_point;

   std::optional<double>  diagonal_length;
   std::optional<double>  width;
   std::optional<double>  height;

   void consider(const screen_rectangle<VectorT>& rectangle)
   {
      top_left = rectangle.get_top_left();
      bottom_right = rectangle.get_bottom_right();
   }
   
   const double& solve_for_diagonal_length() const
   {
      if (diagonal_length.has_value()) {
         return diagonal_length.value();
      }
      
      const_cast<std::optional<double>&>(diagonal_length) = top_left.value().distance_to(bottom_right.value());
      return diagonal_length.value();      
   }
   
   const double& solve_for_width () const
   {
      if (width.has_value()) {
         return width.value();
      }

      const_cast<std::optional<double>&>(width) = bottom_right.value()[0] - top_left.value()[0];
      return width.value();
   }
   
   const double& solve_for_height () const
   {
      if (height.has_value()) {
         return height.value();
      }

      const_cast<std::optional<double>&>(height) = bottom_right.value()[1] - top_left.value()[1];
      return height.value();
   }
   
   bool is_in (const vector2d& location) const
   {  
      if (location[0] >  top_left.value()[0] && 
          location[1] >  top_left.value()[1] &&   // left and top are exclusive
          location[0] <= bottom_right.value()[0] && 
          location[1] <= bottom_right.value()[1]) // right and bottom are inclusive 
      { 
         return true;
      }
      
      return false;
   }
   
   VectorT solve_for_centre_point () const
   {
      if (centre_point.has_value()) {
         return centre_point.value();
      }

      const_cast<std::optional<VectorT>&>(centre_point) = top_left.value() + ((bottom_right.value() - top_left.value()) / 2);
      return centre_point.value();
   }
   
   direction solve_for_direction_of_point (const vector2d& point) const
   {
      solve_for_centre_point ();
      
      if (point[0] <= centre_point.value()[0]) {    // if on the edge, west wins
         if (point[1] < centre_point.value()[1]) {  // if on the edge, south wins
            return direction::nw;
         }
         else {
            return direction::sw;
         }
      }
      else {
         if (point[1] < centre_point.value()[1]) {
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
      
      VectorT new_top_left = top_left.value();
      VectorT new_bottom_right = bottom_right.value();

      const double height_delta = factor * height.value() - height.value();
      const double width_delta = factor * width.value() - width.value();
      
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
      VectorT new_top_left = top_left.value();
      VectorT new_bottom_right = bottom_right.value();
      
      solve_for_height ();
      solve_for_width ();
      
      switch (direction) 
      {
         case direction::n:
            new_top_left    [1] -= height.value();
            new_bottom_right[1] -= height.value();
            break;
         case direction::s:
            new_top_left    [1] += height.value();
            new_bottom_right[1] += height.value();
            break;
         case direction::w: 
            new_top_left    [0] -= width.value();
            new_bottom_right[0] -= width.value();
            break;
         case direction::e:
            new_top_left    [0] += width.value();
            new_bottom_right[0] += width.value();
            break;
         case direction::ne:
            new_top_left    [0] += width.value();
            new_top_left    [1] -= height.value();
            new_bottom_right[0] += width.value();
            new_bottom_right[1] -= height.value();
            break;
         case direction::nw:
            new_top_left    [0] -= width.value();
            new_top_left    [1] -= height.value();
            new_bottom_right[0] -= width.value();
            new_bottom_right[1] -= height.value();
            break;
         case direction::se: 
            new_top_left    [0] += width.value();
            new_top_left    [1] += height.value();
            new_bottom_right[0] += width.value();
            new_bottom_right[1] += height.value();
            break;
         case direction::sw:
            new_top_left    [0] -= width.value();
            new_top_left    [1] += height.value();
            new_bottom_right[0] -= width.value();
            new_bottom_right[1] += height.value();
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

