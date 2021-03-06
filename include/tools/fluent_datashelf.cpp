//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "fluent_datashelf.h"

class fixture_datashelf : public ::testing::Test 
{

protected:

   fixture_datashelf() {}
   virtual ~fixture_datashelf() {}
   
   virtual void SetUp() 
   {
      m_shelf = std::make_shared<mzlib::ds::node>();
      mzlib::ds::fluent(m_shelf)
         .set_name("shelf")
         .add_attribute("title", "my bookshelf")
         .add_node("airplane")
            .use()
            .add_attribute("model", "spitfire")
            .add_attribute("year", "1943")
            .add_attribute("designer", "R. J. Mitchell")
            .stop_using()
         .add_node("book")
            .use()
            .add_attribute("title", "Children of Time")
            .add_node("rating", "4.29")
               .use()
               .add_attribute("source", "Goodreads")
               .stop_using()
            .add_node("rating", "4.5")
               .use()
               .add_attribute("source", "Amazon")
               .stop_using()
            .add_node("author", "Adrian Tchaikovsky")
            .add_node("year", "2016")
            .stop_using()
         .add_node("folder")
            .use()
            .add_node("coin_collection")
            .stop_using()
         .add_node("book")
            .use()
            .add_attribute("title", "Morning Star")
            .add_node("rating", "4.5")
               .use()
               .add_attribute("source", "Goodreads")
               .stop_using()
            .add_node("rating", "4.6")
               .use()
               .add_attribute("source", "Amazon")
               .stop_using()
            .add_node("author", "Pierce Brown");
   }
   
   virtual void TearDown() {}
   
   std::shared_ptr<mzlib::ds::node> m_shelf;
   using node_ptr = std::shared_ptr<mzlib::ds::node>;
};

TEST_F(fixture_datashelf, demo)
{  
   ASSERT_EQ("4.29", mzlib::ds::fluent(m_shelf)
      .first("book")
      .first("rating")
      .value());
   
   ASSERT_EQ("Goodreads", mzlib::ds::fluent(m_shelf)
      .first("book")
      .first("rating")
      .get_attribute("source")
      .value());
}

TEST_F(fixture_datashelf, conversion_from_filter_one_to_node)
{  
   mzlib::ds::node rating_node = 
      mzlib::ds::fluent(m_shelf)
         .first("book")
         .first("rating");
   
   ASSERT_EQ("4.29", rating_node.value());
}

TEST_F(fixture_datashelf, conversion_from_filter_one_to_node_ref)
{  
   mzlib::ds::node& rating_node = mzlib::ds::fluent(m_shelf)
      .first("book")
      .first("rating");
   
   ASSERT_EQ("4.29", rating_node.value());
   
   rating_node.set_value("5");
   
   ASSERT_EQ("5", mzlib::ds::fluent(m_shelf)
      .first("book")
      .first("rating")
      .value());
}

TEST_F(fixture_datashelf, conversion_from_filter_one_to_node_ptr)
{  
   node_ptr rating_node = mzlib::ds::fluent(m_shelf)
      .first("book")
      .first("rating");
   
   ASSERT_EQ("4.29", rating_node->value());
}

TEST_F(fixture_datashelf, fluent_using_attribute)
{
   auto shelf = std::make_shared<mzlib::ds::node>();
   
   mzlib::ds::fluent(shelf)
      .add_node("node1", "node_value1")
         .use()
         .add_attribute("att1", "att_value1")
            .use_attribute()
            .set_name("att2")
            .set_value("att_value2")
            .stop_using()
         .set_name("node2")
         .set_value("node_value2")
         .stop_using();
   
   ASSERT_TRUE(mzlib::ds::fluent(shelf)
      .first("node1")
      .is_empty());
   
   ASSERT_EQ("node_value2", mzlib::ds::fluent(shelf)
      .first("node2")
      .value());
   
   ASSERT_TRUE(mzlib::ds::fluent(shelf)
      .first("node2")
      .get_attribute("att1")
      .is_empty());
   
   ASSERT_EQ("att_value2", mzlib::ds::fluent(shelf)
      .first("node2")
      .get_attribute("att2")
      .value());
}

TEST_F(fixture_datashelf, add_node_to_existing_structure)
{
   mzlib::ds::fluent(m_shelf)
      .first("book")
      .add_node("new_node", "new_val");
   
   ASSERT_EQ("new_val", mzlib::ds::fluent(m_shelf)
      .first("book")
      .first("new_node")
      .value());
}

TEST_F(fixture_datashelf, add_node_to_empty_shelf)
{
   auto root = std::make_shared<mzlib::ds::node>();
   
   mzlib::ds::fluent(root)
      .add_node("book", "Children of Time");
   
   mzlib::ds::fluent(root)
      .add_node("book", "Morning Star");
   
   ASSERT_EQ("Children of Time", mzlib::ds::fluent(root)
      .first("book")
      .value());
 
   ASSERT_EQ("Morning Star", mzlib::ds::fluent(root)
      .first("book")
      .next()
      .value());
}

TEST_F(fixture_datashelf, add_attribute_to_existing_structure)
{
   mzlib::ds::fluent(m_shelf)
      .first("book")
      .use()
         .add_attribute("pages", "like 500 or whatever");
   
   ASSERT_EQ("like 500 or whatever", mzlib::ds::fluent(m_shelf)
      .first("book")
      .get_attribute("pages")
      .value());
}

TEST_F(fixture_datashelf, add_attribute_clean)
{
   auto root = std::make_shared<mzlib::ds::node>();
   
   mzlib::ds::fluent(root)
      .add_attribute("att1", "val1");
   
   mzlib::ds::fluent(root)
      .add_attribute("att2", "val2");

   ASSERT_EQ("val1", mzlib::ds::fluent(root)
      .get_attribute("att1")
      .value());
 
   ASSERT_EQ("val2", mzlib::ds::fluent(root)
      .get_attribute("att2")
      .value());
}

TEST_F(fixture_datashelf, querying_root_node)
{  
   ASSERT_EQ("shelf", mzlib::ds::fluent(m_shelf)
      .name());
   
   ASSERT_EQ("my bookshelf", mzlib::ds::fluent(m_shelf)
      .get_attribute("title")
      .value());
}

TEST_F(fixture_datashelf, get_first_node)
{
   // note: first node is not a book
   auto fluent_shelf = mzlib::ds::fluent(m_shelf);
   auto first_book_node_name = fluent_shelf
      .first("book")
      .name();
   
   auto first_airplane_node_name = fluent_shelf
      .first("airplane")
      .name();
   
   ASSERT_EQ("book", first_book_node_name);
   ASSERT_EQ("airplane", first_airplane_node_name);
}

TEST_F(fixture_datashelf, filter_one_get_first_doesnt_change_state)
{
   auto first_book = mzlib::ds::fluent(m_shelf).first("book");

   auto book_author = first_book.first("author").value();
   auto book_year = first_book.first("year").value();
   
   ASSERT_EQ("Adrian Tchaikovsky", book_author);
   ASSERT_EQ("2016", book_year);
}

TEST_F(fixture_datashelf, filter_one_get_random_doesnt_change_state)
{
   auto first_book = mzlib::ds::fluent(m_shelf).random("book", 
      [](const mzlib::ds::node::iterator& first, const mzlib::ds::node::iterator&) -> mzlib::ds::node::iterator 
      {
         return first;
      });

   auto book_author = first_book.first("author").value();
   auto book_year = first_book.first("year").value();
   
   ASSERT_EQ("Adrian Tchaikovsky", book_author);
   ASSERT_EQ("2016", book_year);
}

TEST_F(fixture_datashelf, filter_one_get_next_doesnt_change_state)
{
   auto first_book = mzlib::ds::fluent(m_shelf).first("book");
   auto next_book = first_book.next();

   auto first_book_author = first_book.first("author").value();
   auto first_book_year = first_book.first("year").value();
   auto next_book_author = next_book.first("author").value();
   auto next_book_rating = next_book.first("rating").value();

   
   ASSERT_EQ("Adrian Tchaikovsky", first_book_author);
   ASSERT_EQ("2016", first_book_year);
   ASSERT_EQ("Pierce Brown", next_book_author);
   ASSERT_EQ("4.5", next_book_rating);
}

TEST_F(fixture_datashelf, get_first_node__no_such_node)
{
   auto does_not_exist = mzlib::ds::fluent(m_shelf)
      .first("ufo evidence")
      .name();
   
   ASSERT_EQ("", does_not_exist);
}

TEST_F(fixture_datashelf, get_attribute)
{
   // note: first node is not a book
   auto book_title = mzlib::ds::fluent(m_shelf)
      .first("book")
      .get_attribute("title")
      .value();
   
   ASSERT_EQ("Children of Time", book_title);
}

TEST_F(fixture_datashelf, get_attribute__no_such_attribute)
{
   // note: first node is not a book
   auto book_notattribute = mzlib::ds::fluent(m_shelf)
      .first("book")
      .get_attribute("unattribute")
      .value();
   
   ASSERT_EQ("", book_notattribute);
}

TEST_F(fixture_datashelf, get_next_node)
{
   auto next_book_title = mzlib::ds::fluent(m_shelf)
      .first("book")
      .next()
      .get_attribute("title")
      .value();
   
   ASSERT_EQ("Morning Star", next_book_title);
}

TEST_F(fixture_datashelf, get_next_node__no_such_node)
{
   auto next_airplane_node_name = mzlib::ds::fluent(m_shelf)
      .first("airplane")
      .next()
      .name();
   
   // there is just one airplane on my shelf
   ASSERT_EQ("", next_airplane_node_name);
}

TEST_F(fixture_datashelf, get_all_nodes)
{
   auto all_nodes = m_shelf->nodes();
   
   ASSERT_EQ(4, all_nodes.size());
   ASSERT_EQ("airplane", all_nodes[0]->name());
   ASSERT_EQ("book", all_nodes[1]->name());
   ASSERT_EQ("folder", all_nodes[2]->name());
   ASSERT_EQ("book", all_nodes[3]->name());
}

TEST_F(fixture_datashelf, get_all_nodes_named)
{
   auto all_nodes = m_shelf->nodes();
   
   auto all_books = mzlib::ds::filter_by_name(all_nodes, "book");
   ASSERT_EQ(2, all_books.size());
   
   auto book1_title = mzlib::ds::get_attribute(all_books[0], "title");
   auto book2_title = mzlib::ds::get_attribute(all_books[1], "title");
   ASSERT_EQ("Children of Time", book1_title->value());
   ASSERT_EQ("Morning Star", book2_title->value());
}

TEST_F(fixture_datashelf, get_random_node)
{
   auto first_random_book = mzlib::ds::fluent(m_shelf).random("book", 
      // in-place mock
      [](const mzlib::ds::node::iterator& first, const mzlib::ds::node::iterator&) -> mzlib::ds::node::iterator 
      {
         return first;
      });
   std::string_view first_random_book_title = first_random_book.get_attribute("title").value();
   
   // note: there is a node between two books that is not a book
   // getting random book should not return non-book nodes
   
   auto second_random_book = mzlib::ds::fluent(m_shelf).random("book", 
      // in-place mock
      [](const mzlib::ds::node::iterator& first, const mzlib::ds::node::iterator&) -> mzlib::ds::node::iterator 
      {
         return std::next(first);
      });
   std::string_view second_random_book_title = second_random_book.get_attribute("title").value();
      
   ASSERT_EQ("Children of Time", first_random_book_title);
   ASSERT_EQ("Morning Star", second_random_book_title);
}

TEST_F(fixture_datashelf, get_random_node_when_empty)
{
   auto random_ufo_evidence = mzlib::ds::fluent(m_shelf).random("ufo evidence", 
      // in-place mock
      [](const mzlib::ds::node::iterator& first, const mzlib::ds::node::iterator&) -> mzlib::ds::node::iterator 
      {
         return first;
      });
   
   // it didn't crash or anything like that
      
   ASSERT_TRUE(random_ufo_evidence.is_empty());
}

TEST_F(fixture_datashelf, all_attributes)
{
   auto airplane_node = mzlib::ds::fluent(m_shelf)
      .first("airplane")
      .get();
   
   auto attributes = airplane_node
      ->attributes();
   
   ASSERT_EQ(3, attributes.size());
   ASSERT_EQ("model", attributes[0]->name());
   ASSERT_EQ("spitfire", attributes[0]->value());
   ASSERT_EQ("year", attributes[1]->name());
   ASSERT_EQ("1943", attributes[1]->value());
   ASSERT_EQ("designer", attributes[2]->name());
   ASSERT_EQ("R. J. Mitchell", attributes[2]->value());
}

TEST_F(fixture_datashelf, all_attributes_iteration__root)
{
   auto attributes = m_shelf->attributes();
   
   ASSERT_EQ(1, attributes.size());
   ASSERT_EQ("title", attributes[0]->name());
   ASSERT_EQ("my bookshelf", attributes[0]->value());
}