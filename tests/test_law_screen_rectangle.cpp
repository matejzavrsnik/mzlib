//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "../include/laws/screen_rectangles.h"
#include "gtest/gtest.h"
#include "../include/dbl.h"

class fixture_law_screen_rectangle : public ::testing::Test 
{

protected:
   
   fixture_law_screen_rectangle () {}
   virtual ~fixture_law_screen_rectangle () {}
   
   virtual void SetUp() {}
   virtual void TearDown() {}
   
   const mzlib::screen_rectangle2d m_rectangle = mzlib::screen_rectangle2d({20,30}, {40,60}); 

   // regular everyday normal rectangle
   //
   //        20  40
   //    + + + + + +
   //    +   
   //    +
   // 30 +   o . .
   //    +   .   .
   //    +   .   .
   // 60 +   . . o
   //    +
};

TEST_F(fixture_law_screen_rectangle, is_in) 
{
   mzlib::screen_rectangle2d rect({-50,-50}, {50,50});
   mzlib::law::screen_rectangles2d law;
   law.consider(rect);
   
   struct t_coordinates {
      double x;
      double y;
      bool should_be_in;
   } coordinates_of_interest[] = {
      // on the border
      {-50,-50, false}, // upper-left corner
      {-50,  0, false}, // centre-left edge
      {-50, 50, false}, // bottom-left corner
      {  0, 50, true }, // bottom-centre edge
      {50,  50, true }, // bottom-right corner
      {50,   0, true }, // centre-right edge
      {50, -50, false}, // top-right corner
      { 0, -50, false}, // centre-top edge
      { 0,   0, true }, // centre
      // just about in
      {-49.99999999, -49.99999999, true}, // upper-left corner
      {-49.99999999,   0         , true}, // centre-left edge
      {-49.99999999,  49.99999999, true}, // bottom-left corner
      {  0,           49.99999999, true}, // bottom-centre edge
      { 49.99999999,  49.99999999, true}, // bottom-right corner
      { 49.99999999,   0         , true}, // centre-right edge
      { 49.99999999, -49.99999999, true}, // top-right corner
      {  0,          -49.99999999, true}, // centre-top edge
      {  0,            0         , true}, // centre
      // some additional edge cases
      {-49,-50, false}, // should just miss upper edge of upper left node
      { 49,-50, false}, // should just miss upper edge of upper right node
      {-50,-49, false}, // should just miss left edge of upper left node
      {-50, 49, false}, // should just miss left edge of bottom left node
      {-40,-40, true }, // should fit fine
      // way off
      {-500, -500, false}, // upper-left direction
      {-500,  0  , false}, // centre-left direction
      {-500,  500, false}, // bottom-left direction
      {   0,  500, false}, // bottom-centre direction
      { 500,  500, false}, // bottom-right direction
      { 500,  0  , false}, // centre-right direction
      { 500, -500, false}, // top-right direction
      {   0, -500, false}  // centre-top direction 
   };
   
   for (auto coor : coordinates_of_interest)
   {

      ASSERT_EQ(coor.should_be_in, law.is_in({coor.x, coor.y})) 
         << "for coordinates: " << coor.x << "," << coor.y;
   }
}

TEST_F(fixture_law_screen_rectangle, get_diagonal_length) 
{
   mzlib::law::screen_rectangles2d rect_law;
   rect_law.consider(m_rectangle);
   rect_law.solve_for_diagonal_length();
   double length = rect_law.m_diagonal_length.get();
   ASSERT_TRUE(mzlib::dbl(length).equals(36.055512754639892L));
}

TEST_F(fixture_law_screen_rectangle, get_width) 
{
   mzlib::law::screen_rectangles2d law;
   law.consider(m_rectangle);
   double width = law.solve_for_width();
   ASSERT_TRUE(mzlib::dbl(width).equals(20L));
}

TEST_F(fixture_law_screen_rectangle, get_heigth) 
{
   mzlib::law::screen_rectangles2d rect_law;
   rect_law.consider(m_rectangle);
   double height = rect_law.solve_for_height();
   ASSERT_TRUE(mzlib::dbl(height).equals(30L));
}


TEST_F(fixture_law_screen_rectangle, calculate_centre_point) 
{
   mzlib::law::screen_rectangles2d rect_law;
   rect_law.consider(m_rectangle);
   mzlib::vector2d centre_point = rect_law.solve_for_centre_point();
   ASSERT_EQ(mzlib::vector2d({30,45}), centre_point);
}

TEST_F(fixture_law_screen_rectangle, direction_of_point) 
{
   mzlib::screen_rectangle2d rect({-50,-50}, {50,50});
   mzlib::law::screen_rectangles2d rect_law;
   rect_law.consider(rect);
   
   struct t_coordinates {
      double x;
      double y;
      mzlib::direction direction;
   } coordinates_of_interest[] = {
      // on the border
      {-50,-50, mzlib::direction::nw}, // upper-left corner
      {-50,  0, mzlib::direction::sw}, // centre-left edge
      {-50, 50, mzlib::direction::sw}, // bottom-left corner
      {  0, 50, mzlib::direction::sw}, // bottom-centre edge
      {50,  50, mzlib::direction::se}, // bottom-right corner
      {50,   0, mzlib::direction::se}, // centre-right edge
      {50, -50, mzlib::direction::ne}, // top-right corner
      { 0, -50, mzlib::direction::nw}, // centre-top edge
      { 0,   0, mzlib::direction::sw}, // centre
      // just about in
      {-49.99999999, -49.99999999, mzlib::direction::nw}, // upper-left corner
      {-49.99999999,   0         , mzlib::direction::sw}, // centre-left edge
      {-49.99999999,  49.99999999, mzlib::direction::sw}, // bottom-left corner
      {  0,           49.99999999, mzlib::direction::sw}, // bottom-centre edge
      { 49.99999999,  49.99999999, mzlib::direction::se}, // bottom-right corner
      { 49.99999999,   0         , mzlib::direction::se}, // centre-right edge
      { 49.99999999, -49.99999999, mzlib::direction::ne}, // top-right corner
      {  0,          -49.99999999, mzlib::direction::nw}, // centre-top edge
      {  0,            0         , mzlib::direction::sw}, // center
      // some additional edge cases
      {-49,-50, mzlib::direction::nw}, // should just miss upper edge of upper left node
      { 49,-50, mzlib::direction::ne}, // should just miss upper edge of upper right node
      {-50,-49, mzlib::direction::nw}, // should just miss left edge of upper left node
      {-50, 49, mzlib::direction::sw}, // should just miss left edge of bottom left node
      {-40,-40, mzlib::direction::nw}, // should fit fine
      // way off
      {-500, -500, mzlib::direction::nw}, // upper-left direction
      {-500,  0  , mzlib::direction::sw}, // centre-left direction
      {-500,  500, mzlib::direction::sw}, // bottom-left direction
      {   0,  500, mzlib::direction::sw}, // bottom-centre direction
      { 500,  500, mzlib::direction::se}, // bottom-right direction
      { 500,  0  , mzlib::direction::se}, // centre-right direction
      { 500, -500, mzlib::direction::ne}, // top-right direction
      {   0, -500, mzlib::direction::nw}  // centre-top direction 
   };
   
   for (auto coor : coordinates_of_interest)
   {
      ASSERT_EQ(coor.direction, rect_law.solve_for_direction_of_point({coor.x, coor.y})) 
         << "for coordinates: " << coor.x << "," << coor.y;
   }
}

TEST_F(fixture_law_screen_rectangle, enlarge_rectangle) 
{
   struct t_parameters {
      mzlib::direction direction;
      double factor;
      mzlib::vector2d expected_top_left;
      mzlib::vector2d expected_bottom_right;
   } test_parameters[] = {
      {mzlib::direction::nw, 2, {0 ,0 }, {40,60}},
      {mzlib::direction::ne, 2, {20,0 }, {60,60}},
      {mzlib::direction::sw, 2, {0, 30}, {40,90}},
      {mzlib::direction::se, 2, {20,30}, {60,90}}
   };
   
   mzlib::law::screen_rectangles2d law;
   law.consider(m_rectangle);
   
   for (auto parameter : test_parameters) {
      auto new_rect = law.enlarge_rectangle(parameter.direction, parameter.factor);
      ASSERT_EQ(parameter.expected_top_left,     new_rect.get_top_left())
         << "unexpected value for top left for expansion in direction: " 
         << parameter.direction << " with factor " << parameter.factor;
      ASSERT_EQ(parameter.expected_bottom_right, new_rect.get_bottom_right())
         << "unexpected value for bottom right for expansion in direction: " 
         << parameter.direction << " with factor " << parameter.factor;
   }
}

TEST_F(fixture_law_screen_rectangle, flip) 
{
      //        20  40
      //    + + + + + +
      //    +   
      //    +
      // 30 +   o . .
      //    +   .   .
      //    +   .   .
      // 60 +   . . o
      //    +
    struct t_parameters {
      mzlib::direction direction;
      mzlib::vector2d expected_top_left;
      mzlib::vector2d expected_bottom_right;
   } test_parameters[] = {
      {mzlib::direction::n,  {20, 0}, {40,30}},
      {mzlib::direction::ne, {40, 0}, {60,30}},
      {mzlib::direction::e,  {40,30}, {60,60}},
      {mzlib::direction::se, {40,60}, {60,90}},
      {mzlib::direction::s,  {20,60}, {40,90}},
      {mzlib::direction::sw, { 0,60}, {20,90}},
      {mzlib::direction::w,  { 0,30}, {20,60}},
      {mzlib::direction::nw, { 0, 0}, {20,30}}
   };
   
   mzlib::law::screen_rectangles2d rect_law;
   rect_law.consider(m_rectangle);
   
   for (auto parameter : test_parameters) {
      auto result = rect_law.flip (parameter.direction);
      auto top_left = result.get_top_left();
      auto bottom_right = result.get_bottom_right();
      ASSERT_EQ(parameter.expected_top_left,     top_left)     << parameter.direction;
      ASSERT_EQ(parameter.expected_bottom_right, bottom_right) << parameter.direction;
   }
}