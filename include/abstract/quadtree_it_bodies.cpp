//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "quadtree_it_bodies.h"

#include "quadtree.h"
#include <map>

class fixture_quadtree_it_bodies : public ::testing::Test 
{

protected:

   fixture_quadtree_it_bodies () {}
   virtual ~fixture_quadtree_it_bodies () {}
   virtual void SetUp () {}
   virtual void TearDown () {}

   double m_min_node_size = 50;
   double m_max_tree_size = 1000;
   mzlib::vector2d m_centre = {0,0};
   mzlib::vector2d m_top_left = {-50,-50};
   mzlib::quadtree m_tree = {
      {m_top_left, {50,50}},
      m_min_node_size, 
      m_max_tree_size};
   mzlib::unique nonexistent_tag;

};

TEST_F(fixture_quadtree_it_bodies, demo)
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

TEST_F(fixture_quadtree_it_bodies, one_node_many_bodies_other_nodes_none)
{
   // Add many bodies to the same node
   const int number_of_bodies_inserted = 10;
   for (double i=1; i<=number_of_bodies_inserted; i++)
   {
      m_tree.add_create(mzlib::law::vector::move_by(m_top_left, {i,i}));
   }
   // Are all of them iterated over
   int bodies_seen = 0;
   for (auto body = m_tree.begin(); body != m_tree.end(); ++body, ++bodies_seen);
   ASSERT_EQ(number_of_bodies_inserted, bodies_seen);
}

TEST_F(fixture_quadtree_it_bodies, many_bodies_each_node)
{
   // just litter the tree with bodies
   int number_of_bodies_inserted = 0;
   for(double i=1; i<2*m_min_node_size; i++)
   {
      for(double j=1; j<2*m_min_node_size; j++)
      {
         m_tree.add_create(mzlib::law::vector::move_by(m_top_left, {i, j}));
         ++number_of_bodies_inserted;
      }
   }
   // Are all of them iterated over
   int bodies_seen = 0;
   for(auto body = m_tree.begin(); body != m_tree.end(); ++body, ++bodies_seen);
   ASSERT_EQ(number_of_bodies_inserted, bodies_seen);
}
