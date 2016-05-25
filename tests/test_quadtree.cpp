// 
// Author: Matej Zavrsnik (matejzavrsnik.com)
//

#include "../include/body.h"
#include "../include/quadtree.h"
#include "gtest/gtest.h"

// The fixture    
class test_cquadtree : public ::testing::Test 
{

protected:

   test_cquadtree () {}
   virtual ~test_cquadtree () {}
   virtual void SetUp () {}
   virtual void TearDown () {}

   double smallest_node_width = 50;
   mzlib::math::cvector2d m_top_left = {-50,-50};
   mzlib::math::cvector2d m_bottom_right = {50,50};
   mzlib::math::cvector2d m_centre = {0,0};
   mzlib::cquadtree<int> m_tree2 = {m_top_left, m_bottom_right, smallest_node_width};

};

// Tests

TEST_F(test_cquadtree, barnes_hut_simulation)
{
   const int node_width = 20;
   const int quadrant_width = 100;
   mzlib::cquadtree<int> tree3 = {
      {-quadrant_width,-quadrant_width}, 
      {quadrant_width, quadrant_width}, 
      node_width};
   //      -100 -60    0        100
   //        |-80|-40  |         |
   // -100 --o o o o o   o o o o o
   //  -80 --o o o o o   o o o o o
   //  -60 --o o o o o   o o o o o
   //  -40 --o o o o o   o o o o o
   //        o o o o o   o o o o o
   //    0 --
   //        o o o o o   o o o o o
   //        o o o o o   o o o o o
   //        o o o o o   o o o o o
   //        o o o o o   o o o o o
   //  100 --o o o o o   o o o o o
   tree3.add(0, {-89, -89}); // put three bodies into upper left most node
   tree3.add(1, {-90, -90});
   tree3.add(2, {-91, -91});
   mzlib::math::cvector2d source_body_loc = { 90,  90};
   int source_body = 3;
   tree3.add(source_body, source_body_loc); // put one into lower right most node
   mzlib::math::cvector2d nearby_body_loc = { 70,  70};
   int nearby_body = 4;
   tree3.add(nearby_body, nearby_body_loc); // put one into the neighbouring node
   
   /*
   double quotient = node_width / quadrant_width; // sort of covers own quadrant
   for(mzphysics::cquadtree<int>::mass_centres_iterator mass_centres = 
       tree.mc_begin(quotient, source_body_loc, source_body);
       mass_centres != tree.mc_end();
       ++mass_centres) {
     
   }
   */
}

TEST_F(test_cquadtree, add)
{
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
      { 0, -50, false}, // top-right corner
      { 0,   0, true }, // center
      // just about in
      {-49.99999999, -49.99999999, true}, // upper-left corner
      {-49.99999999,   0         , true}, // centre-left edge
      {-49.99999999,  49.99999999, true}, // bottom-left corner
      {  0,           49.99999999, true}, // bottom-centre edge
      { 49.99999999,  49.99999999, true}, // bottom-right corner
      { 49.99999999,   0         , true}, // centre-right edge
      { 49.99999999, -49.99999999, true}, // top-right corner
      {  0,          -49.99999999, true}, // top-right corner
      {  0,            0         , true}, // center
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
      {   0, -500, false}  // top-right direction
   };
   for (auto coor : coordinates_of_interest)
   {
      ASSERT_EQ(coor.should_be_in, m_tree2.is_in({coor.x, coor.y})) 
         << "for coordinates: " << coor.x << "," << coor.y;
      ASSERT_EQ(coor.should_be_in, m_tree2.add(0, {coor.x, coor.y}))
         << "for coordinates: " << coor.x << "," << coor.y;
   }
}

TEST_F(test_cquadtree, iterator_it_postorder)
{
   double node_width = 25;
   mzlib::cquadtree<int> tree3 = {m_top_left, m_bottom_right, node_width};
   
   struct t_expected {
      double top_left_0;
      double top_left_1;
      double bottom_right_0;
      double bottom_right_1;
   } expected[] = {
      // order of these matters, since it's a post-order iterator
      {-50, -50, -25, -25},
      {-25, -50,   0, -25},
      {-50, -25, -25,   0},
      {-25, -25,   0,   0},
      {-50, -50,   0,   0},
      {  0, -50,  25, -25},
      { 25, -50,  50, -25},
      {  0, -25,  25,   0},
      { 25, -25,  50,   0},
      {  0, -50,  50,   0},
      {-50,   0, -25,  25},
      {-25,   0,   0,  25},
      {-50,  25, -25,  50},
      {-25,  25,   0,  50},
      {-50,   0,   0,  50},
      {  0,   0,  25,  25},
      { 25,   0,  50,  25},
      {  0,  25,  25,  50},
      { 25,  25,  50,  50},
      {  0,   0,  50,  50},
      {-50, -50,  50,  50}
   };
    
   auto node = tree3.begin_nodes_postorder();
   mzlib::math::cvector2d top_left, bottom_right;
    
   for (auto exp : expected) {
      top_left = node->get_top_left();
      bottom_right = node->get_bottom_right();
      ASSERT_EQ(exp.top_left_0, top_left[0]);
      ASSERT_EQ(exp.top_left_1, top_left[1]);
      ASSERT_EQ(exp.bottom_right_0, bottom_right[0]);
      ASSERT_EQ(exp.bottom_right_1, bottom_right[1]);
      ++node;
   }
    
   ASSERT_TRUE(node == tree3.end_nodes_postorder());
}

TEST_F(test_cquadtree, iterator_it_breadthfirst)
{
   double node_width = 25;
   mzlib::cquadtree<int> tree3 = {m_top_left, m_bottom_right, node_width};
   
   struct t_expected {
      double top_left_0;
      double top_left_1;
      double bottom_right_0;
      double bottom_right_1;
   } expected[] = {
      // order of these matters, since it's a post-order iterator
      {-50, -50,  50,  50},
      {-50, -50,   0,   0},
      {  0, -50,  50,   0},
      {-50,   0,   0,  50},
      {  0,   0,  50,  50},
      {-50, -50, -25, -25},
      {-25, -50,   0, -25},
      {-50, -25, -25,   0},
      {-25, -25,   0,   0},
      {  0, -50,  25, -25},
      { 25, -50,  50, -25},
      {  0, -25,  25,   0},
      { 25, -25,  50,   0},
      {-50,   0, -25,  25},
      {-25,   0,   0,  25},
      {-50,  25, -25,  50},
      {-25,  25,   0,  50},
      {  0,   0,  25,  25},
      { 25,   0,  50,  25},
      {  0,  25,  25,  50},
      { 25,  25,  50,  50},
   };
   
   auto node = tree3.begin_nodes_breadthfirst();
   mzlib::math::cvector2d top_left, bottom_right;
    
   for(auto exp : expected) {
      top_left = node->get_top_left();
      bottom_right = node->get_bottom_right();
      ASSERT_EQ(exp.top_left_0, top_left[0]);
      ASSERT_EQ(exp.top_left_1, top_left[1]);
      ASSERT_EQ(exp.bottom_right_0, bottom_right[0]);
      ASSERT_EQ(exp.bottom_right_1, bottom_right[1]);
      ++node;
   }
    
   ASSERT_TRUE(node == tree3.end_nodes_breadthfirst());
}

TEST_F(test_cquadtree, iterator_order)
{
   mzlib::math::cvector2d se{ 25, 25};
   mzlib::math::cvector2d nw{-25,-25};
   mzlib::math::cvector2d sw{-25, 25};        
   mzlib::math::cvector2d ne{ 25,-25};
    
   int body_se = 0;
   int body_nw = 1;
   int body_sw = 2;
   int body_ne = 3;
    
   // Add them in mixed order
   m_tree2.add(body_se, se);
   m_tree2.add(body_nw, nw);
   m_tree2.add(body_sw, sw);
   m_tree2.add(body_ne, ne);

   // Check if they all turn out and in correct order nw -> ne -> sw -> se
   mzlib::cquadtree<int>::iterator it = m_tree2.begin();
   ASSERT_EQ(body_nw, *it); ++it;
   ASSERT_EQ(body_ne, *it); ++it;
   ASSERT_EQ(body_sw, *it); ++it;
   ASSERT_EQ(body_se, *it); ++it;
   ASSERT_EQ(m_tree2.end(), it);
}

TEST_F(test_cquadtree, iterator_one_node_many_bodies_other_nodes_none)
{
   // Add many bodies to the same node
   const int number_of_bodies_inserted = 10;
   for (double i=1; i<=number_of_bodies_inserted; i++)
   {
      m_tree2.add(i, m_top_left.move_by({i,i}));
   }
   // Are all of them iterated over
   int bodies_seen = 0;
   for (auto body = m_tree2.begin(); body != m_tree2.end(); ++body, ++bodies_seen);
   ASSERT_EQ(number_of_bodies_inserted, bodies_seen);
}

TEST_F(test_cquadtree, iterator_many_bodies_each_node)
{
   // just litter the tree with bodies
   int number_of_bodies_inserted = 0;
   for(double i=1; i<2*smallest_node_width; i++)
   {
      for(double j=1; j<2*smallest_node_width; j++)
      {
         m_tree2.add(0, m_top_left.move_by({i, j}));
         ++number_of_bodies_inserted;
      }
   }
   // Are all of them iterated over
   int bodies_seen = 0;
   for(auto body = m_tree2.begin(); body != m_tree2.end(); ++body, ++bodies_seen);
   ASSERT_EQ(number_of_bodies_inserted, bodies_seen);
}

