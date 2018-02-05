//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "quadtree_it_masscentres.h"

#include "quadtree.h"

class fixture_quadtree_it_masscentres : public ::testing::Test 
{

protected:

   fixture_quadtree_it_masscentres () {}
   virtual ~fixture_quadtree_it_masscentres () {}
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

TEST_F(fixture_quadtree_it_masscentres, basic)
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

TEST_F(fixture_quadtree_it_masscentres, zero_quotient)
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

TEST_F(fixture_quadtree_it_masscentres, body_not_in_tree)
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