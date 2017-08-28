//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_QUADREEE_H
#define MZLIB_QUADREEE_H

#include <optional>

#include "quadtree_node.h"
#include "quadtree_it_bodies.h"
#include "quadtree_it_masscentres.h"
#include "../nature/vector.h"
#include "../nature/body.h"
#include "../tools/missing_std.h"
#include "../nature/screen_rectangle.h"
#include "../lang/binary_options.h"
#include "unique.h"

namespace mzlib {
   
class quadtree
{
    
private:
    
   const double m_min_node_size;
   const double m_max_tree_size;
   std::shared_ptr<quadnode> m_root = nullptr;
   
   // A container for all bodies, even ones that didn't get into the tree itself.
   // Every self respecting container should store stuff it promises.
   std::vector<std::unique_ptr<body_core2d>> m_all_bodies;
   
   void create_root_from_location(const vector2d& location)
   {
      // todo: implement with operations over rectangles
      vector2d top_left    {location[0]-m_min_node_size, location[1]-m_min_node_size};
      vector2d bottom_right{location[0]+m_min_node_size, location[1]+m_min_node_size};
      m_root->create({top_left, bottom_right}, m_min_node_size);
   }
   
   void expand_tree_towards_location(const vector2d& location)
   {
      // get coordinates for new root
      const auto& old_root_rect = m_root->get_node_rectangle();
      mzlib::law::screen_rectangles2d law;
      law.consider(old_root_rect);
      direction expansion_direction = law.solve_for_direction_of_point(location);
      const auto enlarged_rectangle = law.enlarge_rectangle (expansion_direction, 2);
      
      if (law.solve_for_width()  >= m_max_tree_size ||
          law.solve_for_height() >= m_max_tree_size) {
         return; // don/t enlarge if it would make tree larger than max size
      }
      
      // create and groom new root
      std::shared_ptr<quadnode> new_root = std::make_shared<quadnode>();
      new_root->create(
         enlarged_rectangle,
         m_min_node_size);
      new_root->m_bodies.insert(
         new_root->m_bodies.begin(),
         m_root->m_bodies.begin(),
         m_root->m_bodies.end());

      // finally, substitute old root with new
      new_root->attach_child_node(
         the_opposite_direction(expansion_direction), 
         m_root);
      m_root = new_root;
   }
      
   void adjust_dynamic_tree (const vector2d& location)
   {
      if (!is_in(location)) {
         if (!m_root->has_children()) {
            create_root_from_location (location);
         }
         else {
            expand_tree_towards_location (location);
         }
      }
   }
   
   std::optional<int> find_index (const unique tag) const
   {
      std::optional<int> index;
      for (size_t i=0; i<m_all_bodies.size(); ++i) {
         if (m_all_bodies[i]->tag == tag) {
            index = i;
            break;
         }
      }
      return index;
   }
    
public:
       
   typedef quadtree_it_bodies      it_bodies;
   typedef quadtree_it_masscentres it_masscentres;
      
   explicit quadtree (
      const double min_node_size,
      const double max_tree_size) : 
         m_min_node_size (min_node_size),
         m_max_tree_size (max_tree_size),
         m_root (std::make_shared<quadnode>())
   {
   }
   
   quadtree (
      const screen_rectangle2d& rectangle, 
      const double min_node_size,
      const double max_tree_size) :
         quadtree (
            min_node_size,
            max_tree_size)
   {
      m_root->create(rectangle, m_min_node_size);
   }
        
   // can't allow copying due to std::unique_ptrs that are used
   quadtree (const quadtree&) = delete;
   quadtree& operator= (const quadtree&) = delete;
   
   // allow moving
   quadtree (quadtree && ) = default;
   quadtree& operator= (quadtree&&) = default;
   
   virtual ~quadtree () = default;
   
   unique add (std::unique_ptr<body_core2d> body)
   {
      unique tag = body->tag;
      adjust_dynamic_tree (body->centre.location);
      
      // Can still be out of the tree even after it has been resized, because it
      // might not have been: there is a defined limitation to the maximum tree
      // that will be respected by above function.
      
      // The fact that there is no check whether the location of body is in the tree
      // or not is because the quadtree_node::add function is resilient enough to
      // check this anyway, so there is not need to check twice. Especially so,
      // because nothing in particular needs to be done if it is not.
      
      m_root->add(body.get());
      m_all_bodies.push_back(std::move(body));
      return tag;
   }
   
   unique add_copy (const body_core2d& body_core) 
   {
      auto body_core_ptr = std::make_unique<body_core2d>(body_core);
      unique tag = add (std::move(body_core_ptr));
      return tag;
   }
   
   unique add_create (const vector2d location, const double mass = 0) 
   { 
      auto body_ptr = std::make_unique<body_core2d>();
      body_ptr->centre = {location, mass};
      unique tag = add (std::move(body_ptr));
      return tag;
   }
   
   option::exists move (const unique tag, vector2d new_location)
   {
      auto index = find_index (tag);
      if (!index.has_value()) return option::exists::no;
      
      adjust_dynamic_tree (new_location);
      m_root->move (tag,new_location);
      m_all_bodies[index.value()]->centre.location = new_location;
      return option::exists::yes;
   }
   
   option::changed change_mass (const unique tag, double new_mass)
   {
      return m_root->change_mass(tag,new_mass);
   }
   
   option::removed remove (const unique tag)
   {
      if(m_root->remove(tag) == option::removed::yes) {
         for(size_t i=0; i!=m_all_bodies.size(); ++i) {
            if( m_all_bodies[i]->tag == tag) {
               m_all_bodies.erase(m_all_bodies.begin() + i);
               return option::removed::yes;
            }
         }
      }
      return option::removed::no;
   }
   
   const mass_centre2d& get_mass_centre () const
   {
      return m_root->get_mass_centre();
   }
   
   const body_core2d* find (const unique tag) const
   {
      auto index = find_index (tag);
      if (index.has_value()) {
         return m_all_bodies[index.value()].get();
      }
      else {
         return nullptr;
      }
   }
   
   bool is_in (vector2d location) const 
   { 
      return m_root->is_in(location); 
   }

   it_bodies begin () const
   { 
      return it_bodies(m_all_bodies.begin()); 
   }
   
   it_bodies end () const
   { 
      return it_bodies(m_all_bodies.end()); 
   }
        
   it_masscentres begin_masscentres (const unique tag, double quotient)
   {
      return it_masscentres(m_root.get(), tag, quotient);
   }
   
   const it_masscentres end_masscentres () const
   {
      static it_masscentres end;
      return end; // to avoid creating new ends every time; I know they are all the same
   }
   
#ifdef FRIEND_TEST
   FRIEND_TEST(fixture_cquadtree, tree_is_built_correctly);
   FRIEND_TEST(fixture_cquadtree, move_does_not_cross_any_node_borders);
   FRIEND_TEST(fixture_cquadtree, move_crosses_2nd_level_node_borders);
   FRIEND_TEST(fixture_cquadtree, move_crosses_borders_on_all_levels_of_nodes);
   FRIEND_TEST(fixture_cquadtree, move_beyond_tree_size);
   FRIEND_TEST(fixture_cquadtree, dynamic_tree_at_beginning_nodes_null);
   FRIEND_TEST(fixture_cquadtree, dynamic_tree_after_add_nodes_are_correct);
   FRIEND_TEST(fixture_cquadtree, dynamic_tree_after_add_body_in_correct_node);
   FRIEND_TEST(fixture_cquadtree, dynamic_tree_single_level_adds_all_in_correct_node);
   FRIEND_TEST(fixture_cquadtree, dynamic_tree_make_it_expand);
   FRIEND_TEST(fixture_cquadtree, dynamic_tree_move_out_to_up_left);
   FRIEND_TEST(fixture_cquadtree, dynamic_tree_doesnt_exceed_max_size_on_add);
   FRIEND_TEST(fixture_cquadtree, dynamic_tree_doesnt_exceed_max_size_on_move);
#endif
   
}; 
    
} // namespace

#endif	/* MZLIB_QUADREEE_H */

#ifdef MZLIB_BUILDING_TESTS

#ifndef MZLIB_QUADREEE_TESTS_H
#define MZLIB_QUADREEE_TESTS_H

namespace mzlib {

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
   ASSERT_EQ(mzlib::vector2d({-50,-50}), local_tree.m_root->m_rectangle.get_top_left());
   ASSERT_EQ(mzlib::vector2d({ 50, 50}), local_tree.m_root->m_rectangle.get_bottom_right());

   ASSERT_TRUE(local_tree.m_root->m_child_nw->has_children());
   ASSERT_TRUE(local_tree.m_root->m_child_ne->has_children());
   ASSERT_TRUE(local_tree.m_root->m_child_sw->has_children());
   ASSERT_TRUE(local_tree.m_root->m_child_se->has_children());

   // -50 _ 0 _ 50
   //   |nw |ne |
   // 0 ----+---- 0
   //   |sw |se |
   // -50 _ 0 _ -50

   ASSERT_EQ(mzlib::vector2d({-50,-50}), local_tree.m_root->m_child_nw->m_rectangle.get_top_left());
   ASSERT_EQ(mzlib::vector2d({  0,  0}), local_tree.m_root->m_child_nw->m_rectangle.get_bottom_right());
   ASSERT_EQ(mzlib::vector2d({  0,-50}), local_tree.m_root->m_child_ne->m_rectangle.get_top_left());
   ASSERT_EQ(mzlib::vector2d({ 50,  0}), local_tree.m_root->m_child_ne->m_rectangle.get_bottom_right());
   ASSERT_EQ(mzlib::vector2d({-50,  0}), local_tree.m_root->m_child_sw->m_rectangle.get_top_left());
   ASSERT_EQ(mzlib::vector2d({  0, 50}), local_tree.m_root->m_child_sw->m_rectangle.get_bottom_right());
   ASSERT_EQ(mzlib::vector2d({  0,  0}), local_tree.m_root->m_child_se->m_rectangle.get_top_left());
   ASSERT_EQ(mzlib::vector2d({ 50, 50}), local_tree.m_root->m_child_se->m_rectangle.get_bottom_right());
   
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
   
   ASSERT_TRUE(tree.m_root->m_child_nw->m_rectangle.get_top_left()     == mzlib::vector2d({-25,-25}));
   ASSERT_TRUE(tree.m_root->m_child_nw->m_rectangle.get_bottom_right() == mzlib::vector2d({ 25, 25}));
   ASSERT_TRUE(tree.m_root->m_child_ne->m_rectangle.get_top_left()     == mzlib::vector2d({ 25,-25}));
   ASSERT_TRUE(tree.m_root->m_child_ne->m_rectangle.get_bottom_right() == mzlib::vector2d({ 75, 25}));
   ASSERT_TRUE(tree.m_root->m_child_sw->m_rectangle.get_top_left()     == mzlib::vector2d({-25, 25}));
   ASSERT_TRUE(tree.m_root->m_child_sw->m_rectangle.get_bottom_right() == mzlib::vector2d({ 25, 75}));
   ASSERT_TRUE(tree.m_root->m_child_se->m_rectangle.get_top_left()     == mzlib::vector2d({ 25, 25}));
   ASSERT_TRUE(tree.m_root->m_child_se->m_rectangle.get_bottom_right() == mzlib::vector2d({ 75, 75}));   
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

} // namespace

#endif // MZLIB_QUADREEE_TESTS_H

#endif // MZLIB_BUILDING_TESTS
