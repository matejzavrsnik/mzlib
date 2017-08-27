//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_QUADTREE_IT_MASSCENTRES_H
#define MZLIB_QUADTREE_IT_MASSCENTRES_H

#include <iterator>
#include <vector>

#include "quadtree.h"
#include "../nature/mass_centre.h"
#include "../nature/screen_rectangle.h"

namespace mzlib {

// Const iterator through all mass centres
class quadtree_it_masscentres : public std::iterator<std::forward_iterator_tag, body_core2d>
{

private:

   std::vector<mass_centre2d> m_mass_centres_queue;

   const body_core2d* m_body;
   
   std::vector<const quadnode*> m_nodes_queue;
   double m_quotient;
   mass_centre2d m_next_mass_centre;
   bool m_done = false;
   
   void set_done ()
   {
      // Instead of complicated set of interconnected clues about whether we are done or not,
      // why not instead have a simple flag and that's it. So here it is:
      m_done = true;
   }
   
   void prepare_next_mass_centre ()
   {
      //todo: this complicated function can probably be simplified and broken down.
      // This function is a bit logic-heavy ... ready? Here we go:
      if (m_mass_centres_queue.size() > 0) {
         // are mass centres in queue to return? Return those first
         m_next_mass_centre = m_mass_centres_queue.back();
         m_mass_centres_queue.pop_back(); // don't return same twice
         return; // nothing more to do for now
      }
      // By this point, queue of readily available mass centres is depleted. See the queued nodes.
      if (m_nodes_queue.size() == 0) {
         // No more nodes? This is the end. My only friend, the end.
         set_done();
         return; 
      }
      // By this point, queue of mass centres is depleted, but there are still nodes in need to be processed
      const quadnode* node = m_nodes_queue.back();
      m_nodes_queue.pop_back(); // don't use this node again
      // Calculate quotient that tells how far it is compared to its size
      double node_distance = m_body->centre.location.distance_to(node->get_mass_centre().location);
      double node_quotient = node->m_diagonal_length.value() / node_distance;
      // Now depending how far it is, we need to consider either just mass centre of the node, or individual bodies
      if (node_quotient < m_quotient) {
         // too far; we care nothing about this node beyond it's mass centre
         if (node->get_mass_centre().mass != 0) {
            // If it has any real mass at all, that is.
            m_next_mass_centre = node->get_mass_centre();
            return; // done; next mass centre prepared
         }
      }
      else {
         // not too far; need to consider it in details
         if (node->has_children()) {
            // Queue up the children nodes. Rinse. Repeat.
            if(node->m_child_nw->m_bodies.size()) m_nodes_queue.push_back(node->m_child_nw.get());
            if(node->m_child_ne->m_bodies.size()) m_nodes_queue.push_back(node->m_child_ne.get());
            if(node->m_child_sw->m_bodies.size()) m_nodes_queue.push_back(node->m_child_sw.get());
            if(node->m_child_se->m_bodies.size()) m_nodes_queue.push_back(node->m_child_se.get());
         }
         else if (node->m_bodies.size() > 0) {
            // So, by here, the node is not too far, is leaf, has bodies; line them up!
            for(auto body : node->m_bodies) {
               if (body->tag == m_body->tag) continue; // Skip original body
               m_mass_centres_queue.push_back(body->centre);
            }
         }
      }
      // Continue until you have the next m_next_mass_centre to show for it, or
      // there is no more nodes and iteration finished.
      prepare_next_mass_centre();
   }
   
public:

   explicit quadtree_it_masscentres (const quadnode* const node, const unique tag, double quotient)
   { 
      const body_core2d* found_body = node->find (tag);
      if (found_body == nullptr) 
      {
         set_done();
         return;
      }
      m_body = found_body;
      m_quotient = quotient;
      m_mass_centres_queue.reserve(100);
      m_nodes_queue.reserve(100);
      m_nodes_queue.push_back(node);
      prepare_next_mass_centre();
   }
   
   quadtree_it_masscentres ()
   { 
      set_done();
   }

   quadtree_it_masscentres (quadtree_it_masscentres&&) = default;
   quadtree_it_masscentres (const quadtree_it_masscentres&) = default;

   quadtree_it_masscentres* operator++ () 
   {
      prepare_next_mass_centre ();
      return this; 
   }
        
   quadtree_it_masscentres* operator++ (int) 
   { 
      //todo: I know, I lie about postfix. Will fix some day, I promise.
      prepare_next_mass_centre ();
      return this; 
   }

   mass_centre2d* operator-> ()
   {
      return &m_next_mass_centre;
   }

   mass_centre2d& operator* ()
   {
      return m_next_mass_centre; 
   }
   
   bool operator== (const quadtree_it_masscentres& other) const 
   {
      // Infinite recursion guard
      if (this == &other) return true;
      // Return equal only if they are both at the end. Other equalities are possible
      // but I don't see how they could be used for any meaningful purpose and the 
      // calculation would be expensive too.
      return (m_done == true && other.m_done == true);  
   }

   bool operator!= (const quadtree_it_masscentres& other) const 
   { 
      return !(*this == other); 
   }
};

} // namespace

#endif /* MZLIB_QUADTREE_IT_MASSCENTRES_H */

#ifdef MZLIB_BUILDING_TESTS

#ifndef MZLIB_QUADTREE_IT_MASSCENTRES_TESTS_H
#define MZLIB_QUADTREE_IT_MASSCENTRES_TESTS_H

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


#endif // MZLIB_QUADTREE_IT_MASSCENTRES_TESTS_H

#endif // MZLIB_BUILDING_TESTS
