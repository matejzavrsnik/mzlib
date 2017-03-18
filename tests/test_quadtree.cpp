//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#define private public
#define protected public
#include "../include/abstract/quadtree.h"
#undef private
#undef protected


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

   double m_min_node_size = 50;
   double m_max_tree_size = 1000;
   mzlib::vector2d m_centre = {0,0};
   mzlib::quadtree m_tree = {
      {{-50,-50}, {50,50}},
      m_min_node_size, 
      m_max_tree_size};
   mzlib::unique nonexistent_tag;

};

TEST_F(fixture_cquadtree, tree_is_built_when_rectangle_not_provided)
{
   mzlib::quadtree local_tree(m_min_node_size, m_max_tree_size);
   auto tag = local_tree.add_create({50,50}, 50);
   auto found = local_tree.find(tag);
   ASSERT_EQ(tag, found->tag);
}

TEST_F(fixture_cquadtree, tree_is_built_correctly)
{
   mzlib::quadtree local_tree = {{{-50,-50}, {50,50}}, 25, 1000};

   ASSERT_TRUE(local_tree.m_root->m_rectangle.is_defined());
   
   ASSERT_TRUE(local_tree.m_root->has_children());
   ASSERT_EQ(mzlib::vector2d({-50,-50}), local_tree.m_root->m_rectangle.m_top_left.get());
   ASSERT_EQ(mzlib::vector2d({ 50, 50}), local_tree.m_root->m_rectangle.m_bottom_right.get());

   ASSERT_TRUE(local_tree.m_root->m_child_nw->has_children());
   ASSERT_TRUE(local_tree.m_root->m_child_ne->has_children());
   ASSERT_TRUE(local_tree.m_root->m_child_sw->has_children());
   ASSERT_TRUE(local_tree.m_root->m_child_se->has_children());

   // -50 _ 0 _ 50
   //   |nw |ne |
   // 0 ----+---- 0
   //   |sw |se |
   // -50 _ 0 _ -50

   ASSERT_EQ(mzlib::vector2d({-50,-50}), local_tree.m_root->m_child_nw->m_rectangle.m_top_left.get());
   ASSERT_EQ(mzlib::vector2d({  0,  0}), local_tree.m_root->m_child_nw->m_rectangle.m_bottom_right.get());
   ASSERT_EQ(mzlib::vector2d({  0,-50}), local_tree.m_root->m_child_ne->m_rectangle.m_top_left.get());
   ASSERT_EQ(mzlib::vector2d({ 50,  0}), local_tree.m_root->m_child_ne->m_rectangle.m_bottom_right.get());
   ASSERT_EQ(mzlib::vector2d({-50,  0}), local_tree.m_root->m_child_sw->m_rectangle.m_top_left.get());
   ASSERT_EQ(mzlib::vector2d({  0, 50}), local_tree.m_root->m_child_sw->m_rectangle.m_bottom_right.get());
   ASSERT_EQ(mzlib::vector2d({  0,  0}), local_tree.m_root->m_child_se->m_rectangle.m_top_left.get());
   ASSERT_EQ(mzlib::vector2d({ 50, 50}), local_tree.m_root->m_child_se->m_rectangle.m_bottom_right.get());
   
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
   m_tree.add_create({-45,-45}, 100);
   m_tree.add_create({-46,-46}, 100);
   // two nodes in bottom right node
   m_tree.add_create({ 45, 45}, 100);
   auto tag_4 = m_tree.add_create({ 46, 46}, 100);
   
   double quotient = 1; // quotient 1 should barely cover the node the body is in
   mzlib::quadtree::it_masscentres mass_centres_it = m_tree.begin_masscentres(tag_4, quotient);
   ASSERT_EQ(mzlib::vector2d({45,45}), mass_centres_it->location);
   ++mass_centres_it;
   ASSERT_EQ(mzlib::vector2d({-45.5,-45.5}), mass_centres_it->location);
   ++mass_centres_it;
   ASSERT_EQ(m_tree.end_masscentres(), mass_centres_it);
}

TEST_F(fixture_cquadtree, iterator_mass_centres_zero_quotient)
{
   const int node_width = 20;
   const int quadrant_width = 100;
   mzlib::quadtree local_tree = {
      {
         {-quadrant_width,-quadrant_width}, 
         {quadrant_width, quadrant_width}
      }, 
      node_width,
      m_max_tree_size};
   
   // put one body into lower right most node
   auto tag_1 = local_tree.add_create({ 91,  91}, 11); 
   // put two body into the neighbouring node
   local_tree.add_create({ 72,  72}, 12);
   local_tree.add_create({ 73,  73}, 13);
   // finally, put three bodies into upper left most node
   local_tree.add_create({-94, -94}, 14); 
   local_tree.add_create({-95, -95}, 15);
   local_tree.add_create({-96, -96}, 16);

   // sort of covers own quadrant, so from 0,0 to 100,100
   double quotient = 0;
   // first, a neighbouring body
   mzlib::quadtree::it_masscentres mass_centres_it = local_tree.begin_masscentres(tag_1, quotient);
   std::vector<mzlib::mass_centre2d> returned_mass_centres;
   for(; mass_centres_it != local_tree.end_masscentres(); ++mass_centres_it) {
      returned_mass_centres.push_back(*mass_centres_it);
   }
      
   // Should return all 5 other bodies
   ASSERT_EQ(5, returned_mass_centres.size());
}

TEST_F(fixture_cquadtree, iterator_mass_centres_body_not_in_tree)
{
   // put some bodies into the tree
   m_tree.add_create({ 25, 25}, 100);
   m_tree.add_create({-25,-25}, 100);
   m_tree.add_create({ 25,-25}, 100);

   // then try to iterate mass centres around body that is not in
   mzlib::quadtree::it_masscentres mass_centres_it = m_tree.begin_masscentres(nonexistent_tag, 0.2);
   // preferably doesn't outright segfault
   for(; mass_centres_it != m_tree.end_masscentres(); ++mass_centres_it) {
      FAIL(); // and also should not find any
   }
   SUCCEED();
}

/*


todo: This whole thing is now tested as rectangle function; reconsider 
 

TEST_F(fixture_cquadtree, add)
{
   struct t_coordinates {
      double x;
      double y;
      bool should_be_in;
   } coordinates_of_interest[] = {
      // todo: all false here can effectively be "does it expand properly" tests; convert
      // on the border
      //{-50,-50, false}, // upper-left corner
      //{-50,  0, false}, // centre-left edge
      //{-50, 50, false}, // bottom-left corner
      {  0, 50, true }, // bottom-centre edge
      {50,  50, true }, // bottom-right corner
      {50,   0, true }, // centre-right edge
      //{50, -50, false}, // top-right corner
      //{ 0, -50, false}, // top-right corner
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
      //{-49,-50, false}, // should just miss upper edge of upper left node
      //{ 49,-50, false}, // should just miss upper edge of upper right node
      //{-50,-49, false}, // should just miss left edge of upper left node
      //{-50, 49, false}, // should just miss left edge of bottom left node
      {-40,-40, true }, // should fit fine
      // way off
      //{-500, -500, false}, // upper-left direction
      //{-500,  0  , false}, // centre-left direction
      //{-500,  500, false}, // bottom-left direction
      //{   0,  500, false}, // bottom-centre direction
      //{ 500,  500, false}, // bottom-right direction
      //{ 500,  0  , false}, // centre-right direction
      //{ 500, -500, false}, // top-right direction
      //{   0, -500, false}  // top-right direction
   };
   for (auto coor : coordinates_of_interest)
   {
      ASSERT_EQ(coor.should_be_in, m_tree.is_in({coor.x, coor.y})) 
         << "for coordinates: " << coor.x << "," << coor.y;
      ASSERT_EQ(coor.should_be_in, m_tree.add(0, {coor.x, coor.y}))
         << "for coordinates: " << coor.x << "," << coor.y;
   }
}
*/

TEST_F(fixture_cquadtree, find_body_basic)
{
   auto tag_1 = m_tree.add_create({25,25}, 100);
   auto tag_2 = m_tree.add_create({-25,-25}, 100);
   const mzlib::body_core2d* one = m_tree.find(tag_1);
   const mzlib::body_core2d* two = m_tree.find(tag_2);
   ASSERT_NE(nullptr, one);
   ASSERT_NE(nullptr, two);
   ASSERT_EQ(tag_1, one->tag);
   ASSERT_EQ(tag_2, two->tag);
}
   
TEST_F(fixture_cquadtree, find_body_not_found)
{
   m_tree.add_create({25,25}, 100);
   m_tree.add_create({-25,-25}, 100);
   const mzlib::body_core2d* three = m_tree.find(nonexistent_tag);
   ASSERT_EQ(nullptr, three);
}

TEST_F(fixture_cquadtree, remove_body_when_tree_empty)
{
   ASSERT_EQ(mzlib::option::removed::no, m_tree.remove(nonexistent_tag));
}

TEST_F(fixture_cquadtree, remove_body_last_body)
{
   auto tag = m_tree.add_create({25,25}, 100);
   ASSERT_EQ(mzlib::option::removed::yes, m_tree.remove(tag));
}

TEST_F(fixture_cquadtree, remove_body_that_doesnt_exist)
{
   m_tree.add_create({25,25}, 100);
   ASSERT_EQ(mzlib::option::removed::no, m_tree.remove(nonexistent_tag));
}

TEST_F(fixture_cquadtree, move_does_not_cross_any_node_borders)
{
   //    -50    0     50
   // -50 +--+--+--+--+ 
   //     |  |  |  |  |   x means from
   //     +--+--+--+--+   o means to
   //     |  |  |  |  |
   //   0 +--+--+--+--+ 
   //     |  |  |xo|  |   -> move crosses no node borders
   //     +--+--+--+--+
   //     |  |  |  |  |
   //  50 +--+--+--+--+ 
   
   mzlib::quadtree local_tree = {m_tree.m_root->m_rectangle, 25, m_max_tree_size};
   local_tree.add_create({5,5}, 150);
   auto tag_2 = local_tree.add_create({3,3}, 150);
   
   ASSERT_NE(nullptr, local_tree.m_root->m_child_se->m_child_nw->find(tag_2));
   ASSERT_EQ(mzlib::vector2d({4,4}), local_tree.get_mass_centre().location);
   ASSERT_EQ(mzlib::vector2d({4,4}), local_tree.m_root->m_child_se->get_mass_centre().location);
   
   local_tree.move(tag_2, {1,1});
   
   // body hasn't moved out of node, mass centres are updated
   ASSERT_NE(nullptr, local_tree.m_root->m_child_se->m_child_nw->find(tag_2));
   ASSERT_EQ(mzlib::vector2d({3,3}), local_tree.get_mass_centre().location);
   ASSERT_EQ(mzlib::vector2d({3,3}), local_tree.m_root->m_child_se->get_mass_centre().location);
   ASSERT_EQ(mzlib::vector2d({3,3}), local_tree.m_root->m_child_se->m_child_nw->get_mass_centre().location);
}

TEST_F(fixture_cquadtree, move_crosses_2nd_level_node_borders)
{
   //    -50    0     50
   // -50 +--+--+--+--+ 
   //     |  |  |  |  |   x means from
   //     +--+--+--+--+   o means to
   //     |  |  |  |  |
   //   0 +--+--+--+--+ 
   //     |  |  |x |o |   -> move crosses lower node borders, but not higher
   //     +--+--+--+--+
   //     |  |  |  |  |
   //  50 +--+--+--+--+ 
   
   mzlib::quadtree local_tree = {m_tree.m_root->m_rectangle, 25, m_max_tree_size};
   local_tree.add_create({5,5}, 150);
   auto tag_2 = local_tree.add_create({3,3}, 150);
   
   ASSERT_NE(nullptr, local_tree.m_root->m_child_se->m_child_nw->find(tag_2));
   ASSERT_EQ(mzlib::vector2d({4,4}), local_tree.get_mass_centre().location);
   ASSERT_EQ(mzlib::vector2d({4,4}), local_tree.m_root->m_child_se->get_mass_centre().location);
   
   local_tree.move(tag_2, {30,1});
   
   // body hasn't moved out of node, mass centres are updated
   ASSERT_NE(nullptr, local_tree.m_root->m_child_se->m_child_ne->find(tag_2));
   ASSERT_EQ(mzlib::vector2d({17.5,3}), local_tree.get_mass_centre().location);
   ASSERT_EQ(mzlib::vector2d({17.5,3}), local_tree.m_root->m_child_se->get_mass_centre().location);
   ASSERT_EQ(mzlib::vector2d({5,5}), local_tree.m_root->m_child_se->m_child_nw->get_mass_centre().location);
   ASSERT_EQ(mzlib::vector2d({30,1}), local_tree.m_root->m_child_se->m_child_ne->get_mass_centre().location);
}

TEST_F(fixture_cquadtree, move_crosses_borders_on_all_levels_of_nodes)
{
   //    -50    0     50
   // -50 +--+--+--+--+ 
   //     |  |  |  |  |   x means from
   //     +--+--+--+--+   o means to
   //     |  |  |o |  |     -> move crosses lower and higher node borders
   //   0 +--+--+--+--+ 
   //     |  |  |x |  |
   //     +--+--+--+--+
   //     |  |  |  |  |
   //  50 +--+--+--+--+ 
   
   mzlib::quadtree local_tree = {m_tree.m_root->m_rectangle, 25, m_max_tree_size};
   local_tree.add_create({5,5}, 150);
   auto tag_2 = local_tree.add_create({3,3}, 150);
   
   ASSERT_NE(nullptr, local_tree.m_root->m_child_se->m_child_nw->find(tag_2));
   ASSERT_EQ(mzlib::vector2d({4,4}), local_tree.get_mass_centre().location);
   ASSERT_EQ(mzlib::vector2d({4,4}), local_tree.m_root->m_child_se->get_mass_centre().location);
   
   local_tree.move(tag_2, {1,-5});
   
   // body hasn't moved out of node, mass centres are updated
   ASSERT_NE(nullptr, local_tree.m_root->m_child_ne->m_child_sw->find(tag_2));
   ASSERT_EQ(mzlib::vector2d({3,0}), local_tree.get_mass_centre().location);
   ASSERT_EQ(mzlib::vector2d({5,5}), local_tree.m_root->m_child_se->get_mass_centre().location);
   ASSERT_EQ(mzlib::vector2d({1,-5}), local_tree.m_root->m_child_ne->get_mass_centre().location);
   ASSERT_EQ(mzlib::vector2d({5,5}), local_tree.m_root->m_child_se->m_child_nw->get_mass_centre().location);
   ASSERT_EQ(mzlib::vector2d({1,-5}), local_tree.m_root->m_child_ne->m_child_sw->get_mass_centre().location);
}

TEST_F(fixture_cquadtree, move_nonexistent_tag)
{
   m_tree.add_create({25,25}, 150);
   m_tree.add_create({23,23}, 150);
   // hopefully doesn't crash
   mzlib::option::exists exists = m_tree.move(nonexistent_tag, {21,21});
   ASSERT_EQ(mzlib::option::exists::no, exists);
   // mass centre stays unchanged
   ASSERT_EQ(300, m_tree.get_mass_centre().mass);
   ASSERT_EQ(mzlib::vector2d({24,24}), m_tree.get_mass_centre().location);
}

TEST_F(fixture_cquadtree, move_beyond_tree_size)
{
   m_tree.add_create({25,25}, 150);
   auto tag_2 = m_tree.add_create({23,23}, 150);
   
   // move out of tree
   m_tree.move(tag_2, m_tree.m_root->m_rectangle.get_bottom_right() + mzlib::vector2d({0,10}));
   ASSERT_NE(nullptr, m_tree.find(tag_2));
   
   // move back to where it was
   m_tree.move(tag_2, mzlib::vector2d({0,12}));
   ASSERT_NE(nullptr, m_tree.find(tag_2));
}

TEST_F(fixture_cquadtree, change_mass_basic)
{
   m_tree.add_create({5,5}, 100);
   auto tag_2 = m_tree.add_create({25,25}, 100);
   ASSERT_EQ(200, m_tree.get_mass_centre().mass);
   ASSERT_EQ(mzlib::vector2d({15,15}), m_tree.get_mass_centre().location);
   auto changed = m_tree.change_mass(tag_2, 300);
   ASSERT_EQ(mzlib::option::changed::yes, changed);
   ASSERT_EQ(400, m_tree.get_mass_centre().mass);
   ASSERT_EQ(mzlib::vector2d({20,20}), m_tree.get_mass_centre().location);
}

TEST_F(fixture_cquadtree, change_mass_nonexistent_tag)
{
   m_tree.add_create({5,5}, 100);
   m_tree.add_create({25,25}, 100);
   // hopefully doesn't crash
   auto changed = m_tree.change_mass(nonexistent_tag, 150);
   ASSERT_EQ(mzlib::option::changed::no, changed);
   // mass centre stays unchanged
   ASSERT_EQ(200, m_tree.get_mass_centre().mass);
   ASSERT_EQ(mzlib::vector2d({15,15}), m_tree.get_mass_centre().location);
}

TEST_F(fixture_cquadtree, mass_centre_maintenance_basic)
{
   auto tag_1 = m_tree.add_create({25,25}, 100);
   m_tree.add_create({-25,-25}, 100);
   ASSERT_EQ(200, m_tree.get_mass_centre().mass);
   ASSERT_EQ(mzlib::vector2d({0,0}), m_tree.get_mass_centre().location);
   auto removed = m_tree.remove(tag_1);
   ASSERT_EQ(mzlib::option::removed::yes, removed);
   ASSERT_EQ(100, m_tree.get_mass_centre().mass);
   ASSERT_EQ(mzlib::vector2d({-25,-25}), m_tree.get_mass_centre().location);
}

TEST_F(fixture_cquadtree, iterator_all_bodies)
{
   auto tag_1 = m_tree.add_create({ 25, 25});
   auto tag_2 = m_tree.add_create({-25,-25});
   auto tag_3 = m_tree.add_create({-25, 25});
   auto tag_4 = m_tree.add_create({ 25,-25});
   
   std::map<mzlib::unique, bool> bodies_retrieved;
   
   bodies_retrieved[tag_1] = false;
   bodies_retrieved[tag_2] = false;
   bodies_retrieved[tag_3] = false;
   bodies_retrieved[tag_4] = false;

   // Check if they can all be retrieved
   for(mzlib::body_core2d body : m_tree) {
      bodies_retrieved[body.tag] = true;
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
      m_tree.add_create(m_tree.m_root->m_rectangle.get_top_left().move_by({i,i}));
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
   for(double i=1; i<2*m_min_node_size; i++)
   {
      for(double j=1; j<2*m_min_node_size; j++)
      {
         m_tree.add_create(m_tree.m_root->m_rectangle.get_top_left().move_by({i, j}));
         ++number_of_bodies_inserted;
      }
   }
   // Are all of them iterated over
   int bodies_seen = 0;
   for(auto body = m_tree.begin(); body != m_tree.end(); ++body, ++bodies_seen);
   ASSERT_EQ(number_of_bodies_inserted, bodies_seen);
}

TEST_F(fixture_cquadtree, dynamic_tree_at_beginning_nodes_null)
{
   mzlib::quadtree tree(50,1000);
   
   ASSERT_EQ(nullptr, tree.m_root->m_parent);
   ASSERT_EQ(nullptr, tree.m_root->m_child_nw);
   ASSERT_EQ(nullptr, tree.m_root->m_child_ne);
   ASSERT_EQ(nullptr, tree.m_root->m_child_sw);
   ASSERT_EQ(nullptr, tree.m_root->m_child_se);
}

TEST_F(fixture_cquadtree, dynamic_tree_after_add_nodes_are_correct)
{
   mzlib::quadtree tree(50,1000);
   tree.add_create({25, 25});
   
   // child nodes are created at this point
   ASSERT_EQ(nullptr, tree.m_root->m_parent);
   ASSERT_NE(nullptr, tree.m_root->m_child_nw);
   ASSERT_NE(nullptr, tree.m_root->m_child_ne);
   ASSERT_NE(nullptr, tree.m_root->m_child_sw);
   ASSERT_NE(nullptr, tree.m_root->m_child_se);
   
   // they have no child nodes of their own, because they are the smallest possible
   ASSERT_FALSE(tree.m_root->m_child_nw->has_children());
   ASSERT_FALSE(tree.m_root->m_child_ne->has_children());
   ASSERT_FALSE(tree.m_root->m_child_sw->has_children());
   ASSERT_FALSE(tree.m_root->m_child_se->has_children());

   // newly added mass centre is set into the centre of newly created root node
   //
   //    -25    25    75
   // -25 +-----+-----+ 
   //     |     |     |  
   //     | nw  | ne  |  
   //     |     |     |
   //  25 +-----+-----+ 
   //     |     |     | 
   //     | sw  | se  |
   //     |     |     |
   //  75 +-----+-----+ 
   
   ASSERT_TRUE(tree.m_root->m_child_nw->m_rectangle.m_top_left.get()     == mzlib::vector2d({-25,-25}));
   ASSERT_TRUE(tree.m_root->m_child_nw->m_rectangle.m_bottom_right.get() == mzlib::vector2d({ 25, 25}));
   ASSERT_TRUE(tree.m_root->m_child_ne->m_rectangle.m_top_left.get()     == mzlib::vector2d({ 25,-25}));
   ASSERT_TRUE(tree.m_root->m_child_ne->m_rectangle.m_bottom_right.get() == mzlib::vector2d({ 75, 25}));
   ASSERT_TRUE(tree.m_root->m_child_sw->m_rectangle.m_top_left.get()     == mzlib::vector2d({-25, 25}));
   ASSERT_TRUE(tree.m_root->m_child_sw->m_rectangle.m_bottom_right.get() == mzlib::vector2d({ 25, 75}));
   ASSERT_TRUE(tree.m_root->m_child_se->m_rectangle.m_top_left.get()     == mzlib::vector2d({ 25, 25}));
   ASSERT_TRUE(tree.m_root->m_child_se->m_rectangle.m_bottom_right.get() == mzlib::vector2d({ 75, 75}));   
}

TEST_F(fixture_cquadtree, dynamic_tree_after_add_body_in_correct_node)
{
   mzlib::quadtree tree(50,1000);
   tree.add_create({ 25, 25});

   ASSERT_EQ(1, tree.m_root->m_child_nw->m_bodies.size());
   ASSERT_EQ(0, tree.m_root->m_child_ne->m_bodies.size());
   ASSERT_EQ(0, tree.m_root->m_child_sw->m_bodies.size());
   ASSERT_EQ(0, tree.m_root->m_child_se->m_bodies.size());
}

TEST_F(fixture_cquadtree, dynamic_tree_single_level_adds_all_in_correct_node)
{
   mzlib::quadtree tree(50,1000);

   // newly added mass centre is set into the centre of newly created root node
   //
   //    -25    25    75
   // -25 +-----+-----+ 
   //     |     |     |  
   //     | nw  | ne  |  
   //     |     |     |
   //  25 +-----+-----+ 
   //     |     |     |  
   //     | sw  | se  |
   //     |     |     |
   //  75 +-----+-----+ 

   tree.add_create({ 25, 25});   
   ASSERT_EQ(1, tree.m_root->m_child_nw->m_bodies.size());
   ASSERT_EQ(0, tree.m_root->m_child_ne->m_bodies.size());
   ASSERT_EQ(0, tree.m_root->m_child_sw->m_bodies.size());
   ASSERT_EQ(0, tree.m_root->m_child_se->m_bodies.size());
   
   tree.add_create({ 30, -20});   
   ASSERT_EQ(1, tree.m_root->m_child_nw->m_bodies.size());
   ASSERT_EQ(1, tree.m_root->m_child_ne->m_bodies.size());
   ASSERT_EQ(0, tree.m_root->m_child_sw->m_bodies.size());
   ASSERT_EQ(0, tree.m_root->m_child_se->m_bodies.size());

   tree.add_create({ -20, 30});   
   ASSERT_EQ(1, tree.m_root->m_child_nw->m_bodies.size());
   ASSERT_EQ(1, tree.m_root->m_child_ne->m_bodies.size());
   ASSERT_EQ(1, tree.m_root->m_child_sw->m_bodies.size());
   ASSERT_EQ(0, tree.m_root->m_child_se->m_bodies.size());   

   tree.add_create({ 30, 30});   
   ASSERT_EQ(1, tree.m_root->m_child_nw->m_bodies.size());
   ASSERT_EQ(1, tree.m_root->m_child_ne->m_bodies.size());
   ASSERT_EQ(1, tree.m_root->m_child_sw->m_bodies.size());
   ASSERT_EQ(1, tree.m_root->m_child_se->m_bodies.size());
}

TEST_F(fixture_cquadtree, dynamic_tree_make_it_expand)
{
   mzlib::quadtree tree(50,1000);

   auto tag_1 = tree.add_create({ 25, 25});
   
   //   X
   //       -25    25    75
   //    -25 +-----+-----+ 
   //        |     |     |  
   //        | nw  | ne  |  
   //        |     |     |
   //     25 +-----+-----+ 
   //        |     |     |  
   //        | sw  | se  |
   //        |     |     |
   //     75 +-----+-----+ 
 
   auto tag_2 = tree.add_create({-30, -30});
   
   // check the coordinates of root node match
   ASSERT_EQ(mzlib::vector2d({-125,-125}), tree.m_root->m_rectangle.get_top_left());
   ASSERT_EQ(mzlib::vector2d({  75,  75}), tree.m_root->m_rectangle.get_bottom_right());
   
   // check the bodies copied from former root to new one
   ASSERT_NE(tree.m_root->m_bodies.end(), tree.m_root->find_body(tag_1));
   ASSERT_NE(tree.m_root->m_bodies.end(), tree.m_root->find_body(tag_2));
   
   // and coordinates of 1st level children
   ASSERT_EQ(mzlib::vector2d({-125,-125}), tree.m_root->m_child_nw->m_rectangle.get_top_left());
   ASSERT_EQ(mzlib::vector2d({ -25, -25}), tree.m_root->m_child_nw->m_rectangle.get_bottom_right());
   ASSERT_EQ(mzlib::vector2d({ -25,-125}), tree.m_root->m_child_ne->m_rectangle.get_top_left());
   ASSERT_EQ(mzlib::vector2d({  75, -25}), tree.m_root->m_child_ne->m_rectangle.get_bottom_right());
   ASSERT_EQ(mzlib::vector2d({-125, -25}), tree.m_root->m_child_sw->m_rectangle.get_top_left());
   ASSERT_EQ(mzlib::vector2d({ -25,  75}), tree.m_root->m_child_sw->m_rectangle.get_bottom_right());
   ASSERT_EQ(mzlib::vector2d({ -25, -25}), tree.m_root->m_child_se->m_rectangle.get_top_left());
   ASSERT_EQ(mzlib::vector2d({  75,  75}), tree.m_root->m_child_se->m_rectangle.get_bottom_right());
   
   // and two bodies are in correct nodes in expanded tree
   ASSERT_EQ(1, tree.m_root->m_child_nw->m_child_se->m_bodies.size());
   ASSERT_EQ(0, tree.m_root->m_child_nw->m_child_sw->m_bodies.size());
   ASSERT_EQ(0, tree.m_root->m_child_nw->m_child_nw->m_bodies.size());
   ASSERT_EQ(0, tree.m_root->m_child_nw->m_child_ne->m_bodies.size());
   ASSERT_EQ(1, tree.m_root->m_child_se->m_child_nw->m_bodies.size());
   ASSERT_EQ(0, tree.m_root->m_child_se->m_child_ne->m_bodies.size());
   ASSERT_EQ(0, tree.m_root->m_child_se->m_child_se->m_bodies.size());
   ASSERT_EQ(0, tree.m_root->m_child_se->m_child_sw->m_bodies.size());
   ASSERT_EQ(0, tree.m_root->m_child_ne->m_bodies.size());
   ASSERT_EQ(0, tree.m_root->m_child_sw->m_bodies.size());
   
   // correct bodies are in those two nodes
   ASSERT_EQ(tag_2, tree.m_root->m_child_nw->m_child_se->m_bodies[0]->tag);
   ASSERT_EQ(tag_1, tree.m_root->m_child_se->m_child_nw->m_bodies[0]->tag);
}

TEST_F(fixture_cquadtree, dynamic_tree_move_out_to_up_left)
{
   mzlib::quadtree tree(50, m_max_tree_size);

   auto tag_one = tree.add_create({ 25, 25});
   
   //   X
   //       -25    25    75
   //    -25 +-----+-----+ 
   //        |     |     |  
   //        | nw  | ne  |  
   //        |     |     |
   //     25 +-----+-----+ 
   //        |     |     |  
   //        | sw  | se  |
   //        |     |     |
   //     75 +-----+-----+ 
 
   auto tag_two = tree.add_create({20, 20}); // no changes to tree structure yet
   tree.move(tag_two, {-30, -30}); // moved out of tree, which should resize
   
   // check the coordinates of root node match
   ASSERT_EQ(mzlib::vector2d({-125,-125}), tree.m_root->m_rectangle.get_top_left());
   ASSERT_EQ(mzlib::vector2d({  75,  75}), tree.m_root->m_rectangle.get_bottom_right());
   
   // and coordinates of 1st level children
   ASSERT_EQ(mzlib::vector2d({-125,-125}), tree.m_root->m_child_nw->m_rectangle.get_top_left());
   ASSERT_EQ(mzlib::vector2d({ -25, -25}), tree.m_root->m_child_nw->m_rectangle.get_bottom_right());
   ASSERT_EQ(mzlib::vector2d({ -25,-125}), tree.m_root->m_child_ne->m_rectangle.get_top_left());
   ASSERT_EQ(mzlib::vector2d({  75, -25}), tree.m_root->m_child_ne->m_rectangle.get_bottom_right());
   ASSERT_EQ(mzlib::vector2d({-125, -25}), tree.m_root->m_child_sw->m_rectangle.get_top_left());
   ASSERT_EQ(mzlib::vector2d({ -25,  75}), tree.m_root->m_child_sw->m_rectangle.get_bottom_right());
   ASSERT_EQ(mzlib::vector2d({ -25, -25}), tree.m_root->m_child_se->m_rectangle.get_top_left());
   ASSERT_EQ(mzlib::vector2d({  75,  75}), tree.m_root->m_child_se->m_rectangle.get_bottom_right());
   
   // and two bodies are in correct nodes in expanded tree
   ASSERT_EQ(1, tree.m_root->m_child_nw->m_child_se->m_bodies.size());
   ASSERT_EQ(0, tree.m_root->m_child_nw->m_child_sw->m_bodies.size());
   ASSERT_EQ(0, tree.m_root->m_child_nw->m_child_nw->m_bodies.size());
   ASSERT_EQ(0, tree.m_root->m_child_nw->m_child_ne->m_bodies.size());
   ASSERT_EQ(1, tree.m_root->m_child_se->m_child_nw->m_bodies.size());
   ASSERT_EQ(0, tree.m_root->m_child_se->m_child_ne->m_bodies.size());
   ASSERT_EQ(0, tree.m_root->m_child_se->m_child_se->m_bodies.size());
   ASSERT_EQ(0, tree.m_root->m_child_se->m_child_sw->m_bodies.size());
   ASSERT_EQ(0, tree.m_root->m_child_ne->m_bodies.size());
   ASSERT_EQ(0, tree.m_root->m_child_sw->m_bodies.size());
   
   // correct bodies are in those two nodes
   ASSERT_EQ(tag_two, tree.m_root->m_child_nw->m_child_se->m_bodies[0]->tag);
   ASSERT_EQ(tag_one, tree.m_root->m_child_se->m_child_nw->m_bodies[0]->tag);
}

TEST_F(fixture_cquadtree, dynamic_tree_doesnt_exceed_max_size_on_add)
{
   mzlib::quadtree tree(50, 100);

   auto tag_one = tree.add_create({ 25, 25});
   
   //   X
   //       -25    25    75
   //    -25 +-----+-----+ 
   //        |     |     |  
   //        | nw  | ne  |  
   //        |     |     |
   //     25 +-----+-----+ 
   //        |     |     |  
   //        | sw  | se  |
   //        |     |     |
   //     75 +-----+-----+ 
 
   auto tag_two = tree.add_create({-30, -30});
   
   // coordinates of root node remained the same
   ASSERT_EQ(mzlib::vector2d({-25,-25}), tree.m_root->m_rectangle.get_top_left());
   ASSERT_EQ(mzlib::vector2d({ 75, 75}), tree.m_root->m_rectangle.get_bottom_right());
   
   // despite, both bodies are in the tree, just that body_two did not fit in quadtree part of it
   ASSERT_NE(nullptr, tree.find(tag_one));
   ASSERT_NE(nullptr, tree.find(tag_two));
   ASSERT_EQ(1, tree.m_root->m_bodies.size());
   ASSERT_EQ(tag_one, tree.m_root->m_bodies[0]->tag);
}

TEST_F(fixture_cquadtree, dynamic_tree_doesnt_exceed_max_size_on_move)
{
   mzlib::quadtree tree(50, 100);

   auto tag_one = tree.add_create({ 25, 25});
   
   //   X
   //       -25    25    75
   //    -25 +-----+-----+ 
   //        |     |     |  
   //        | nw  | ne  |  
   //        |     |     |
   //     25 +-----+-----+ 
   //        |     |     |  
   //        | sw  | se  |
   //        |     |     |
   //     75 +-----+-----+ 
 
   auto tag_two = tree.add_create({20, 20}); // no changes to tree structure yet
   
   // moved out of tree, which should resize, but max size setting prevents it
   tree.move(tag_two, {-30, -30});
   
   // coordinates of root node remained the same
   ASSERT_EQ(mzlib::vector2d({-25,-25}), tree.m_root->m_rectangle.get_top_left());
   ASSERT_EQ(mzlib::vector2d({ 75, 75}), tree.m_root->m_rectangle.get_bottom_right());
   
   // despite, both bodies are in the tree, just that body_two did not fit in quadtree part of it
   ASSERT_NE(nullptr, tree.find(tag_two));
   ASSERT_NE(nullptr, tree.find(tag_one));
   ASSERT_EQ(1, tree.m_root->m_bodies.size());
   ASSERT_EQ(tag_one, tree.m_root->m_bodies[0]->tag);
}