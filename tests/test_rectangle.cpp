//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "../include/rectangle.h"
#include "gtest/gtest.h"
#include "../include/dbl.h"

class fixture_rectangle : public ::testing::Test 
{

protected:
   
   fixture_rectangle () {}
   virtual ~fixture_rectangle () {}
   
   virtual void SetUp() 
   {
      m_rectangle.set_top_left    ({20,30});
      m_rectangle.set_bottom_right({40,60});

      //        20  40
      //    + + + + + +
      //    +   
      //    +
      // 30 +   o . .
      //    +   .   .
      //    +   .   .
      // 60 +   . . o
      //    +
   }
   
   virtual void TearDown() {}
   
   mzlib::crectangle2d m_rectangle; // regular everyday normal rectangle
};

TEST_F(fixture_rectangle, is_in) 
{
   mzlib::crectangle2d rect;
   rect.set_top_left({-50,-50});
   rect.set_bottom_right({50,50});
   
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
      ASSERT_EQ(coor.should_be_in, rect.is_in({coor.x, coor.y})) 
         << "for coordinates: " << coor.x << "," << coor.y;
   }
}

TEST_F(fixture_rectangle, get_diagonal_length) 
{
   double length = m_rectangle.get_diagonal_length();
   ASSERT_TRUE(mzlib::dbl(length).equals(36.055512754639892L));
}

TEST_F(fixture_rectangle, get_width) 
{
   double width = m_rectangle.get_width();
   ASSERT_TRUE(mzlib::dbl(width).equals(20L));
}

TEST_F(fixture_rectangle, get_heigth) 
{
   double height = m_rectangle.get_height();
   ASSERT_TRUE(mzlib::dbl(height).equals(30L));
}


TEST_F(fixture_rectangle, calculate_centre_point) 
{
   mzlib::cvector2d centre_point = m_rectangle.calculate_centre_point();
   ASSERT_EQ(mzlib::cvector2d({30,45}), centre_point);
}

TEST_F(fixture_rectangle, direction_of_point) 
{
   mzlib::crectangle2d rect;
   rect.set_top_left({-50,-50});
   rect.set_bottom_right({50,50});
   
   struct t_coordinates {
      double x;
      double y;
      mzlib::edirection direction;
   } coordinates_of_interest[] = {
      // on the border
      {-50,-50, mzlib::edirection::nw}, // upper-left corner
      {-50,  0, mzlib::edirection::sw}, // centre-left edge
      {-50, 50, mzlib::edirection::sw}, // bottom-left corner
      {  0, 50, mzlib::edirection::sw}, // bottom-centre edge
      {50,  50, mzlib::edirection::se}, // bottom-right corner
      {50,   0, mzlib::edirection::se}, // centre-right edge
      {50, -50, mzlib::edirection::ne}, // top-right corner
      { 0, -50, mzlib::edirection::nw}, // centre-top edge
      { 0,   0, mzlib::edirection::sw}, // centre
      // just about in
      {-49.99999999, -49.99999999, mzlib::edirection::nw}, // upper-left corner
      {-49.99999999,   0         , mzlib::edirection::sw}, // centre-left edge
      {-49.99999999,  49.99999999, mzlib::edirection::sw}, // bottom-left corner
      {  0,           49.99999999, mzlib::edirection::sw}, // bottom-centre edge
      { 49.99999999,  49.99999999, mzlib::edirection::se}, // bottom-right corner
      { 49.99999999,   0         , mzlib::edirection::se}, // centre-right edge
      { 49.99999999, -49.99999999, mzlib::edirection::ne}, // top-right corner
      {  0,          -49.99999999, mzlib::edirection::nw}, // centre-top edge
      {  0,            0         , mzlib::edirection::sw}, // center
      // some additional edge cases
      {-49,-50, mzlib::edirection::nw}, // should just miss upper edge of upper left node
      { 49,-50, mzlib::edirection::ne}, // should just miss upper edge of upper right node
      {-50,-49, mzlib::edirection::nw}, // should just miss left edge of upper left node
      {-50, 49, mzlib::edirection::sw}, // should just miss left edge of bottom left node
      {-40,-40, mzlib::edirection::nw}, // should fit fine
      // way off
      {-500, -500, mzlib::edirection::nw}, // upper-left direction
      {-500,  0  , mzlib::edirection::sw}, // centre-left direction
      {-500,  500, mzlib::edirection::sw}, // bottom-left direction
      {   0,  500, mzlib::edirection::sw}, // bottom-centre direction
      { 500,  500, mzlib::edirection::se}, // bottom-right direction
      { 500,  0  , mzlib::edirection::se}, // centre-right direction
      { 500, -500, mzlib::edirection::ne}, // top-right direction
      {   0, -500, mzlib::edirection::nw}  // centre-top direction 
   };
   
   for (auto coor : coordinates_of_interest)
   {
      ASSERT_EQ(coor.direction, rect.direction_of_point({coor.x, coor.y})) 
         << "for coordinates: " << coor.x << "," << coor.y;
   }
}

TEST_F(fixture_rectangle, enlarge_rectangle) 
{
   struct t_parameters {
      mzlib::edirection direction;
      double factor;
      mzlib::cvector2d expected_top_left;
      mzlib::cvector2d expected_bottom_right;
   } test_parameters[] = {
      {mzlib::edirection::nw, 2, {0 ,0 }, {40,60}},
      {mzlib::edirection::ne, 2, {20,0 }, {60,60}},
      {mzlib::edirection::sw, 2, {0, 30}, {40,90}},
      {mzlib::edirection::se, 2, {20,30}, {60,90}}
   };
   
   for (auto parameter : test_parameters) {
      auto new_rect = m_rectangle.enlarge_rectangle(parameter.direction, parameter.factor);
      ASSERT_EQ(parameter.expected_top_left,     new_rect.get_top_left())
         << "unexpected value for top left for expansion in direction: " 
         << parameter.direction << " with factor " << parameter.factor;
      ASSERT_EQ(parameter.expected_bottom_right, new_rect.get_bottom_right())
         << "unexpected value for bottom right for expansion in direction: " 
         << parameter.direction << " with factor " << parameter.factor;
   }
}

TEST_F(fixture_rectangle, flip) 
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
      mzlib::edirection direction;
      mzlib::cvector2d expected_top_left;
      mzlib::cvector2d expected_bottom_right;
   } test_parameters[] = {
      {mzlib::edirection::n,  {20, 0}, {40,30}},
      {mzlib::edirection::ne, {40, 0}, {60,30}},
      {mzlib::edirection::e,  {40,30}, {60,60}},
      {mzlib::edirection::se, {40,60}, {60,90}},
      {mzlib::edirection::s,  {20,60}, {40,90}},
      {mzlib::edirection::sw, { 0,60}, {20,90}},
      {mzlib::edirection::w,  { 0,30}, {20,60}},
      {mzlib::edirection::nw, { 0, 0}, {20,30}}
   };
   
   for (auto parameter : test_parameters) {
      auto result = m_rectangle.flip (parameter.direction);
      auto top_left = result.get_top_left();
      auto bottom_right = result.get_bottom_right();
      ASSERT_EQ(parameter.expected_top_left,     top_left)     << parameter.direction;
      ASSERT_EQ(parameter.expected_bottom_right, bottom_right) << parameter.direction;
   }
}