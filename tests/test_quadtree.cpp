//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#define private public
#define protected public

#include "../include/quadtree.h"
#include "gtest/gtest.h"

#include <functional>
#include <map>

class fixture_cquadtree : public ::testing::Test 
{

protected:

   fixture_cquadtree () {}
   virtual ~fixture_cquadtree () {}
   virtual void SetUp () {}
   virtual void TearDown () {}

   double smallest_node_width = 50;
   mzlib::math::cvector2d m_top_left = {-50,-50};
   mzlib::math::cvector2d m_bottom_right = {50,50};
   mzlib::math::cvector2d m_centre = {0,0};
   mzlib::cquadtree<int> m_tree = {m_top_left, m_bottom_right, smallest_node_width};

};

TEST_F(fixture_cquadtree, tree_is_built_correctly)
{
   mzlib::cquadtree<int> local_tree = {{-50,-50}, {50,50}, 25};

   ASSERT_TRUE(local_tree.m_root->has_children());
   ASSERT_EQ(mzlib::math::cvector2d({-50,-50}), local_tree.m_root->m_top_left);
   ASSERT_EQ(mzlib::math::cvector2d({ 50, 50}), local_tree.m_root->m_bottom_right);
   
   ASSERT_TRUE(local_tree.m_root->m_child_nw->has_children());
   ASSERT_TRUE(local_tree.m_root->m_child_ne->has_children());
   ASSERT_TRUE(local_tree.m_root->m_child_sw->has_children());
   ASSERT_TRUE(local_tree.m_root->m_child_se->has_children());

   // -50 _ 0 _ 50
   //   |nw |ne |
   // 0 ----+---- 0
   //   |sw |se |
   // -50 _ 0 _ -50
   
   ASSERT_EQ(mzlib::math::cvector2d({-50,-50}), local_tree.m_root->m_child_nw->m_top_left);
   ASSERT_EQ(mzlib::math::cvector2d({  0,  0}), local_tree.m_root->m_child_nw->m_bottom_right);
   ASSERT_EQ(mzlib::math::cvector2d({  0,-50}), local_tree.m_root->m_child_ne->m_top_left);
   ASSERT_EQ(mzlib::math::cvector2d({ 50,  0}), local_tree.m_root->m_child_ne->m_bottom_right);
   ASSERT_EQ(mzlib::math::cvector2d({-50,  0}), local_tree.m_root->m_child_sw->m_top_left);
   ASSERT_EQ(mzlib::math::cvector2d({  0, 50}), local_tree.m_root->m_child_sw->m_bottom_right);
   ASSERT_EQ(mzlib::math::cvector2d({  0,  0}), local_tree.m_root->m_child_se->m_top_left);
   ASSERT_EQ(mzlib::math::cvector2d({ 50, 50}), local_tree.m_root->m_child_se->m_bottom_right);
   
   ASSERT_FALSE(local_tree.m_root->m_child_nw->m_child_nw->has_children());
   ASSERT_FALSE(local_tree.m_root->m_child_nw->m_child_ne->has_children());
   ASSERT_FALSE(local_tree.m_root->m_child_nw->m_child_sw->has_children());
   ASSERT_FALSE(local_tree.m_root->m_child_nw->m_child_se->has_children());

   ASSERT_FALSE(local_tree.m_root->m_child_ne->m_child_nw->has_children());
   ASSERT_FALSE(local_tree.m_root->m_child_ne->m_child_ne->has_children());
   ASSERT_FALSE(local_tree.m_root->m_child_ne->m_child_sw->has_children());
   ASSERT_FALSE(local_tree.m_root->m_child_ne->m_child_se->has_children());
   
   ASSERT_FALSE(local_tree.m_root->m_child_sw->m_child_nw->has_children());
   ASSERT_FALSE(local_tree.m_root->m_child_sw->m_child_ne->has_children());
   ASSERT_FALSE(local_tree.m_root->m_child_sw->m_child_sw->has_children());
   ASSERT_FALSE(local_tree.m_root->m_child_sw->m_child_se->has_children());
   
   ASSERT_FALSE(local_tree.m_root->m_child_se->m_child_nw->has_children());
   ASSERT_FALSE(local_tree.m_root->m_child_se->m_child_ne->has_children());
   ASSERT_FALSE(local_tree.m_root->m_child_se->m_child_sw->has_children());
   ASSERT_FALSE(local_tree.m_root->m_child_se->m_child_se->has_children());
}

TEST_F(fixture_cquadtree, iterator_mass_centres_basic)
{
   // two nodes in top left node
   m_tree.add(1, {-45,-45}, 100);
   m_tree.add(2, {-46,-46}, 100);
   // two nodes in bottom right node
   m_tree.add(3, { 45, 45}, 100);
   m_tree.add(4, { 46, 46}, 100);
   
   double quotient = 1; // quotient 1 should barely cover the node the body is in
   mzlib::cquadtree<int>::it_masscentres mass_centres_it = m_tree.begin_masscentres(4, quotient);
   ASSERT_EQ(mzlib::math::cvector2d({-45.5,-45.5}), mass_centres_it->location);
   ++mass_centres_it;
   ASSERT_EQ(mzlib::math::cvector2d({45,45}), mass_centres_it->location);
   ++mass_centres_it;
   ASSERT_EQ(m_tree.end_masscentres(), mass_centres_it);
}

TEST_F(fixture_cquadtree, iterator_mass_centres_zero_quotient)
{
   const int node_width = 20;
   const int quadrant_width = 100;
   mzlib::cquadtree<int> local_tree = {
      {-quadrant_width,-quadrant_width}, 
      {quadrant_width, quadrant_width}, 
      node_width};
   
   // put one body into lower right most node
   local_tree.add(1, { 91,  91}, 11); 
   // put two body into the neighbouring node
   local_tree.add(2, { 72,  72}, 12);
   local_tree.add(3, { 73,  73}, 13);
   // finally, put three bodies into upper left most node
   local_tree.add(4, {-94, -94}, 14); 
   local_tree.add(5, {-95, -95}, 15);
   local_tree.add(6, {-96, -96}, 16);

   // sort of covers own quadrant, so from 0,0 to 100,100
   double quotient = 0;
   // first, a neighbouring body
   mzlib::cquadtree<int>::it_masscentres mass_centres_it = local_tree.begin_masscentres(1, quotient);
   std::vector<mzlib::cmass_centre2d> returned_mass_centres;
   for(; mass_centres_it != local_tree.end_masscentres(); ++mass_centres_it) {
      returned_mass_centres.push_back(*mass_centres_it);
   }
      
   // Should return all 5 other bodies
   ASSERT_EQ(5, returned_mass_centres.size());
}

TEST_F(fixture_cquadtree, iterator_mass_centres_body_not_in_tree)
{
   // put some bodies into the tree
   m_tree.add(1, { 25, 25}, 100);
   m_tree.add(2, {-25,-25}, 100);
   m_tree.add(3, { 25,-25}, 100);
   // then try to iterate mass centres around body that is not in
   mzlib::cquadtree<int>::it_masscentres mass_centres_it = m_tree.begin_masscentres(4, 0.2);
   // preferably doesn't outright segfault
   for(; mass_centres_it != m_tree.end_masscentres(); ++mass_centres_it) {
      FAIL(); // and also should not find any
   }
   SUCCEED();
}

TEST_F(fixture_cquadtree, add)
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
      ASSERT_EQ(coor.should_be_in, m_tree.is_in({coor.x, coor.y})) 
         << "for coordinates: " << coor.x << "," << coor.y;
      ASSERT_EQ(coor.should_be_in, m_tree.add(0, {coor.x, coor.y}))
         << "for coordinates: " << coor.x << "," << coor.y;
   }
}

TEST_F(fixture_cquadtree, find_body_basic)
{
   m_tree.add(1, {25,25}, 100);
   m_tree.add(2, {-25,-25}, 100);
   const mzlib::cbinded_mass_centre2d<int>* one = m_tree.find(1);
   const mzlib::cbinded_mass_centre2d<int>* two = m_tree.find(2);
   ASSERT_NE(nullptr, one);
   ASSERT_NE(nullptr, two);
   ASSERT_EQ(1, one->data);
   ASSERT_EQ(2, two->data);
}

TEST_F(fixture_cquadtree, find_body_when_data_some_other_type)
{
   mzlib::cquadtree<std::string> local_tree = {m_top_left, m_bottom_right, smallest_node_width};
   local_tree.add("one", { 25, 25}, 100);
   local_tree.add("two", {-25,-25}, 100);
   const mzlib::cbinded_mass_centre2d<std::string>* one = local_tree.find("one");
   const mzlib::cbinded_mass_centre2d<std::string>* two = local_tree.find("two");
   ASSERT_NE(nullptr, one);
   ASSERT_NE(nullptr, two);
   ASSERT_EQ("one", one->data);
   ASSERT_EQ("two", two->data);
}
   
TEST_F(fixture_cquadtree, find_body_not_found)
{
   m_tree.add(1, {25,25}, 100);
   m_tree.add(2, {-25,-25}, 100);
   const mzlib::cbinded_mass_centre2d<int>* three = m_tree.find(3);
   ASSERT_EQ(nullptr, three);
}

TEST_F(fixture_cquadtree, remove_body_when_tree_empty)
{
   bool success = m_tree.remove(2);
   ASSERT_FALSE(success);
}

TEST_F(fixture_cquadtree, remove_body_last_body)
{
   m_tree.add(1, {25,25}, 100);
   bool success = m_tree.remove(1);
   ASSERT_TRUE(success);
}

TEST_F(fixture_cquadtree, remove_body_that_doesnt_exist)
{
   m_tree.add(1, {25,25}, 100);
   bool success = m_tree.remove(2);
   ASSERT_FALSE(success);
}

TEST_F(fixture_cquadtree, move_basic)
{
   m_tree.add(1, {25,25}, 150);
   m_tree.add(2, {23,23}, 150);
   ASSERT_EQ(300, m_tree.get_mass_centre().mass);
   ASSERT_EQ(mzlib::math::cvector2d({24,24}), m_tree.get_mass_centre().location);
   m_tree.move(2, {21,21});
   ASSERT_EQ(300, m_tree.get_mass_centre().mass);
   ASSERT_EQ(mzlib::math::cvector2d({23,23}), m_tree.get_mass_centre().location);
}

TEST_F(fixture_cquadtree, move_nonexistent_data)
{
   m_tree.add(1, {25,25}, 150);
   m_tree.add(2, {23,23}, 150);
   // hopefully doesn't crash
   bool success = m_tree.move(3, {21,21});
   ASSERT_FALSE(success);
   // mass centre stays unchanged
   ASSERT_EQ(300, m_tree.get_mass_centre().mass);
   ASSERT_EQ(mzlib::math::cvector2d({24,24}), m_tree.get_mass_centre().location);
}

TEST_F(fixture_cquadtree, move_beyond_tree_size)
{
   m_tree.add(1, {25,25}, 150);
   m_tree.add(2, {23,23}, 150);
   // move out of tree
   bool is_in_tree = m_tree.move(2, m_bottom_right + mzlib::math::cvector2d({0,10}));
   ASSERT_FALSE(is_in_tree); // should signal that it is out of tree
   bool still_finds_the_tree = false;
   for(auto body : m_tree) { if (body.data == 2) { still_finds_the_tree = true; } }
   ASSERT_TRUE(still_finds_the_tree);
   
   // move even further out
   is_in_tree = m_tree.move(2, m_bottom_right + mzlib::math::cvector2d({0,12}));
   ASSERT_FALSE(is_in_tree);
   for(auto body : m_tree) { if (body.data == 2) { still_finds_the_tree = true; } }
   ASSERT_TRUE(still_finds_the_tree);
   
   // move back to where it was, in the tree
   is_in_tree = m_tree.move(2, mzlib::math::cvector2d({0,12}));
   ASSERT_TRUE(is_in_tree);
   for(auto body : m_tree) { if (body.data == 2) { still_finds_the_tree = true; } }
   ASSERT_TRUE(still_finds_the_tree);
   
}

TEST_F(fixture_cquadtree, change_mass_basic)
{
   m_tree.add(1, {5,5}, 100);
   m_tree.add(2, {25,25}, 100);
   ASSERT_EQ(200, m_tree.get_mass_centre().mass);
   ASSERT_EQ(mzlib::math::cvector2d({15,15}), m_tree.get_mass_centre().location);
   m_tree.change_mass(2, 300);
   ASSERT_EQ(400, m_tree.get_mass_centre().mass);
   ASSERT_EQ(mzlib::math::cvector2d({20,20}), m_tree.get_mass_centre().location);
}

TEST_F(fixture_cquadtree, change_mass_nonexistent_data)
{
   m_tree.add(1, {5,5}, 100);
   m_tree.add(2, {25,25}, 100);
   // hopefully doesn't crash
   bool success = m_tree.change_mass(3, 150);
   ASSERT_FALSE(success);
   // mass centre stays unchanged
   ASSERT_EQ(200, m_tree.get_mass_centre().mass);
   ASSERT_EQ(mzlib::math::cvector2d({15,15}), m_tree.get_mass_centre().location);
}

TEST_F(fixture_cquadtree, mass_centre_maintenance_basic)
{
   m_tree.add(1, {25,25}, 100);
   m_tree.add(2, {-25,-25}, 100);
   ASSERT_EQ(200, m_tree.get_mass_centre().mass);
   ASSERT_EQ(mzlib::math::cvector2d({0,0}), m_tree.get_mass_centre().location);
   bool success = m_tree.remove(1);
   ASSERT_EQ(100, m_tree.get_mass_centre().mass);
   ASSERT_EQ(mzlib::math::cvector2d({-25,-25}), m_tree.get_mass_centre().location);
}

TEST_F(fixture_cquadtree, iterator_it_postorder)
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

TEST_F(fixture_cquadtree, iterator_it_breadthfirst)
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

TEST_F(fixture_cquadtree, iterator_all_bodies)
{
   m_tree.add(0, { 25, 25});
   m_tree.add(1, {-25,-25});
   m_tree.add(2, {-25, 25});
   m_tree.add(3, { 25,-25});
   
   std::map<int, bool> bodies_retrieved;
   
   bodies_retrieved[0] = false;
   bodies_retrieved[1] = false;
   bodies_retrieved[2] = false;
   bodies_retrieved[3] = false;

   // Check if they can all be retrieved
   for(mzlib::cbinded_mass_centre2d<int> body : m_tree) {
      bodies_retrieved[body.data] = true;
   }
   
   for(auto entry : bodies_retrieved) {
      ASSERT_TRUE(entry.second); // assert retrieved
   }
}

TEST_F(fixture_cquadtree, iterator_one_node_many_bodies_other_nodes_none)
{
   // Add many bodies to the same node
   const int number_of_bodies_inserted = 10;
   for (double i=1; i<=number_of_bodies_inserted; i++)
   {
      m_tree.add(i, m_top_left.move_by({i,i}));
   }
   // Are all of them iterated over
   int bodies_seen = 0;
   for (auto body = m_tree.begin(); body != m_tree.end(); ++body, ++bodies_seen);
   ASSERT_EQ(number_of_bodies_inserted, bodies_seen);
}

TEST_F(fixture_cquadtree, iterator_many_bodies_each_node)
{
   // just litter the tree with bodies
   int number_of_bodies_inserted = 0;
   for(double i=1; i<2*smallest_node_width; i++)
   {
      for(double j=1; j<2*smallest_node_width; j++)
      {
         m_tree.add(0, m_top_left.move_by({i, j}));
         ++number_of_bodies_inserted;
      }
   }
   // Are all of them iterated over
   int bodies_seen = 0;
   for(auto body = m_tree.begin(); body != m_tree.end(); ++body, ++bodies_seen);
   ASSERT_EQ(number_of_bodies_inserted, bodies_seen);
}

