//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "datashelf.h"

class fixture_ds_extended : public ::testing::Test 
{

protected:

   fixture_ds_extended () {}
   virtual ~fixture_ds_extended () {}
   virtual void SetUp () 
   {
      m_shelf = std::make_shared<mzlib::ds::node>();
      m_shelf->set_name("shelf");
      m_shelf->add_attribute("title", "my bookshelf");
      
      auto airplane = m_shelf->add_node("airplane");
         airplane->add_attribute("model", "spitfire");
         airplane->add_attribute("year", "1943");
         airplane->add_attribute("designer", "R. J. Mitchell");
      
      m_book1 = m_shelf->add_node("book");
         m_book1->add_attribute("title", "Children of Time");
         auto rating1 = m_book1->add_node("rating", "4.29");
            rating1->add_attribute("source", "Goodreads");
         auto rating2 = m_book1->add_node("rating", "4.5");
            rating2->add_attribute("source", "Amazon");
         m_book1->add_node("author", "Adrian Tchaikovsky");
         m_book1->add_node("year", "2016");
      
      auto folder = m_shelf->add_node("folder");
         folder->add_node("coin_collection");
      
      m_book2 = m_shelf->add_node("book");
         m_book2->add_attribute("title", "Morning Star");
         auto rating3 = m_book2->add_node("rating", "4.5");
            rating3->add_attribute("source", "Goodreads");
         auto rating4 = m_book2->add_node("rating", "4.6");
            rating4->add_attribute("source", "Amazon");
         m_book2->add_node("author", "Pierce Brown");
   }
   
   virtual void TearDown () {}
   
   std::shared_ptr<mzlib::ds::node> m_shelf;
   std::shared_ptr<mzlib::ds::node> m_book1;
   std::shared_ptr<mzlib::ds::node> m_book2;
};

std::vector<std::shared_ptr<mzlib::ds::node>>::const_iterator 
find_by_name(
   const std::vector<std::shared_ptr<mzlib::ds::node>>& nodes,
   std::string_view name)
{
   return std::find_if (nodes.cbegin(), nodes.cend(), 
      [&name] (const std::shared_ptr<mzlib::ds::node>& n) {
         return n->name() == name;
      });
}

TEST_F(fixture_ds_extended, get_peers)
{
   auto peers = mzlib::ds::get_peers(m_book1);
   
   auto node1 = find_by_name(peers, "airplane");
   auto node2 = find_by_name(peers, "folder");
   auto node3 = find_by_name(peers, "book");
   
   ASSERT_NE(peers.end(), node1);
   ASSERT_NE(peers.end(), node2);
   ASSERT_NE(peers.end(), node3);
}

TEST_F(fixture_ds_extended, filter_by_name)
{
   auto filtered = mzlib::ds::filter_by_name(m_shelf->nodes(), "book");
   
   auto node1 = find_by_name(filtered, "airplane");
   auto node2 = find_by_name(filtered, "folder");
   auto node3 = find_by_name(filtered, "book");
   
   ASSERT_EQ(filtered.end(), node1);
   ASSERT_EQ(filtered.end(), node2);
   ASSERT_NE(filtered.end(), node3);
   ASSERT_EQ(2, filtered.size());
   ASSERT_EQ("book", filtered[0]->name());
   ASSERT_EQ("book", filtered[1]->name());
}

TEST_F(fixture_ds_extended, find_next_of)
{
   auto next = mzlib::ds::find_next_of(m_shelf->nodes(), m_book1);
   ASSERT_EQ("folder", next->name());
}

TEST_F(fixture_ds_extended, find_next_of_last_item)
{
   auto next = mzlib::ds::find_next_of(m_shelf->nodes(), m_book2);
   ASSERT_TRUE(next->is_empty());
}

TEST_F(fixture_ds_extended, first)
{
   auto first = mzlib::ds::first(m_shelf->nodes(), "book");
   ASSERT_EQ(m_book1, first);
}

TEST_F(fixture_ds_extended, first_no_subnodes)
{
   auto first = mzlib::ds::first(m_shelf->nodes(), "doesn't exist");
   ASSERT_TRUE(first->is_empty());
}

TEST_F(fixture_ds_extended, first_with_attribute)
{
   auto book = mzlib::ds::first_with_attribute(
      m_shelf->nodes(), "book", "title", "Morning Star");
   ASSERT_EQ(m_book2, book);
}


TEST_F(fixture_ds_extended, random)
{
   auto first_book = mzlib::ds::random(m_shelf->nodes(), "book",
      // in-place mock
      [](const mzlib::ds::node::iterator& first, const mzlib::ds::node::iterator&) 
         -> mzlib::ds::node::iterator 
      {
         return first;
      });
   // note: there is a node between two books that is not a book
   // getting random book should not return non-book nodes
   auto second_book = mzlib::ds::random(m_shelf->nodes(), "book",
      // in-place mock
      [](const mzlib::ds::node::iterator& first, const mzlib::ds::node::iterator&)
         -> mzlib::ds::node::iterator 
      {
         return std::next(first);
      });
     
   ASSERT_EQ(m_book1, first_book);
   ASSERT_EQ(m_book2, second_book);
}

TEST_F(fixture_ds_extended, next)
{
   auto next = mzlib::ds::next(m_book1);
   ASSERT_EQ(m_book2, next);
}

TEST_F(fixture_ds_extended, next_last_item)
{
   auto next = mzlib::ds::next(m_book2);
   ASSERT_TRUE(next->is_empty());
}

TEST_F(fixture_ds_extended, get_attribute)
{
   auto attribute = mzlib::ds::get_attribute(m_book1, "title");
   ASSERT_EQ("Children of Time", attribute->value());
}

TEST_F(fixture_ds_extended, get_attribute_no_attributes)
{
   auto attribute = mzlib::ds::get_attribute(m_shelf, "doesn't exist");
   ASSERT_TRUE(attribute->is_empty());
}
