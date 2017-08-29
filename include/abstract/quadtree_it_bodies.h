//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_QUADTREE_IT_BODIES_H
#define MZLIB_QUADTREE_IT_BODIES_H

#include <iterator>
#include <memory>
#include <vector>
#include "quadtree.h"

namespace mzlib {

// Const iterator through all bodies
// The purpouse if this custom iterator is to peel object reference out of 
// unique_ptr structure that is actually stored in vector
class quadtree_it_bodies : public std::iterator<std::forward_iterator_tag, body_core2d>
{

private:

   using iterator_type = typename std::vector<std::unique_ptr<body_core2d>>::const_iterator;
   iterator_type m_body_it;

public:

   explicit quadtree_it_bodies (iterator_type it) : 
      m_body_it(it) 
   { 
   }

   quadtree_it_bodies (quadtree_it_bodies&&) = default;
   quadtree_it_bodies (const quadtree_it_bodies&) = default;

   quadtree_it_bodies* operator++ () 
   { 
      ++m_body_it;
      return this; 
   }
        
   quadtree_it_bodies* operator++ (int) 
   {
      ++m_body_it; //todo: lies, damned lies!!
      return this; 
   }

   body_core2d const * operator-> () const
   { 
      return (*m_body_it).get();
   }

   const body_core2d& operator* () const
   { 
      return *(*m_body_it); 
   }
   
   bool operator== (const quadtree_it_bodies& other) const 
   { 
      // Infinite recursion guard
      if(this == &other) return true;
      // forward equality to actual iterator
      return (this->m_body_it == other.m_body_it);  
   }

   bool operator!= (const quadtree_it_bodies& other) const 
   { 
      return !(*this == other); 
   }
};

} // namespace

#endif /* MZLIB_QUADTREE_IT_BODIES_H */

#ifdef MZLIB_BUILDING_TESTS

#ifndef MZLIB_QUADTREE_IT_BODIES_TESTS_H
#define MZLIB_QUADTREE_IT_BODIES_TESTS_H

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
      m_tree.add_create(mzlib::vec_op::move_by(m_top_left, {i,i}));
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
         m_tree.add_create(mzlib::vec_op::move_by(m_top_left, {i, j}));
         ++number_of_bodies_inserted;
      }
   }
   // Are all of them iterated over
   int bodies_seen = 0;
   for(auto body = m_tree.begin(); body != m_tree.end(); ++body, ++bodies_seen);
   ASSERT_EQ(number_of_bodies_inserted, bodies_seen);
}

#endif // MZLIB_QUADTREE_IT_BODIES_TESTS_H

#endif // MZLIB_BUILDING_TESTS
