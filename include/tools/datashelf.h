//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_DATASHELF_H
#define MZLIB_DATASHELF_H

#include "../string/is_just_whitespace.h"

#include <memory> // for shared ptr
#include <algorithm>
#include <stack> // find_if

namespace mzlib { 
namespace ds {

class fluent;
class fluent_state_attribute_added;
class fluent_state_attribute;
class fluent_state_filter_one;

}
}

#include "datashelf_foundation.h"

namespace mzlib {
namespace ds {

// when I grow up I am going to be a fluent interface

// "Certainly chaining is a common technique to use with fluent interfaces, 
// but true fluency is much more than that." (Martin Fowler)
//
// Here I am making it into a state machine, because it makes sense. When in state
// "working on attribute" function add_node makes no sense, because attributes
// can't have nested nodes, while add_node makes perfect sense in "working on
// nodes" state, because you can always add subnodes. This is simple example,
// more complicated are functions that change meaning with state. In "attribute"
// state get() should mean get me the attribute, whilst in "node" state it means
// get me the node. How would you otherwise overload for function return type?
// That, my friends, is impossible. Or when I start adding queries ... for example,
// when I have filtered all subnodes with certain name, what does add_node mean
// then? With state machine, all states can be programmed separately and I can
// get errors in compile time; for example, I can simply not implement add_node
// in a "filtered a collection of nodes" state. It all makes perfect sense at the
// moment, let's see the idea mature first before I brag too much :)
//
// Didn't expect fluent interface part of the project to be so interesting.

class fluent
{

private:
   
   // all the nodes that are actively used
   std::stack<std::shared_ptr<node>> m_using_nodes;
   // temporary storage for the next state
   std::unique_ptr<fluent_state_attribute_added> m_state_attribute_added;
   std::shared_ptr<fluent_state_filter_one> m_state_filter_one;
   
   std::shared_ptr<node> current_node()
   {
      if (m_using_nodes.size() == 0)
         return node::empty();
      
      return m_using_nodes.top();
   }
   
   std::shared_ptr<node> last_added_node()
   {
      if (current_node()->m_nodes.size() > 0) {
         return *std::prev(current_node()->m_nodes.end());
      }
      return nullptr;
   }
   
   std::shared_ptr<attribute> last_added_attribute()
   {
      if (current_node()->m_attributes.size() > 0) {
         return *std::prev(current_node()->m_attributes.end());
      }
      return nullptr;
   }
   
public:
   
   fluent(std::shared_ptr<node> shelf)
   {
      m_using_nodes.push(shelf);
   }
      
   fluent& set_name(std::string name)
   {
      current_node()->set_name(name);
      return *this;
   }
   
   fluent& set_value(std::string value)
   {
      current_node()->set_value(value);
      return *this;
   }
   
   fluent_state_attribute_added& add_attribute
      (std::string name, std::string value = "")
   {
      auto new_attribute = std::make_shared<attribute>(name, value);
      current_node()->m_attributes.push_back(new_attribute);
      m_state_attribute_added = std::make_unique<fluent_state_attribute_added>(*this);
      return *m_state_attribute_added.get();
   }
   
   fluent& add_node(std::string name = "", std::string value = "")
   {
      auto parent = current_node();
      auto new_node = std::make_shared<node>(name, value, parent);
      parent->m_nodes.push_back(new_node);
      return *this;
   }
   
   fluent& use()
   {
      auto last = last_added_node();
      if (last != nullptr) {
         m_using_nodes.push(last);
      }
      return *this;
   }
   
   fluent& stop_using()
   {
      if(m_using_nodes.size()>1) {
         m_using_nodes.pop();
      }
      return *this;
   }
   
   // queries
   
   std::shared_ptr<node> get()
   {
      return current_node();
   }
   
   fluent_state_filter_one& first(std::string name)
   {
      m_state_filter_one = std::make_unique<fluent_state_filter_one>(
         ::mzlib::ds::first(
            current_node()->nodes(), 
            name));
      return *m_state_filter_one.get();
   }
   
   fluent_state_filter_one& random (
      std::string name,
      decltype(get_random_element<typename node::iterator>) rnd = 
         get_random_element<typename node::iterator>)
   {
      m_state_filter_one = std::make_unique<fluent_state_filter_one>(
         ::mzlib::ds::random(
            current_node()->nodes(), 
            name, 
            rnd));
      return *m_state_filter_one.get();
   }
   
   std::shared_ptr<attribute> get_attribute(std::string name)
   {
      return ::mzlib::ds::get_attribute(
         current_node(),
         name);
   }
   
   friend class fluent_state_attribute_added;
   friend class fluent_state_attribute;
};

class fluent_state_filter_one
{
private:
   
   std::shared_ptr<fluent> m_state_node;
   std::shared_ptr<node> m_filtered_one;
   
public:
   fluent_state_filter_one(std::shared_ptr<node> origin)
   {
      m_filtered_one = origin;
   }
   
   std::shared_ptr<node> get()
   {
      return m_filtered_one;
   }
      
   fluent_state_filter_one& first(std::string name)
   {
      m_filtered_one = ::mzlib::ds::first(
         m_filtered_one->nodes(), 
         name);
      return *this;
   }
   
   fluent_state_filter_one& random (
      std::string name,
      decltype(get_random_element<typename node::iterator>) rnd = 
         get_random_element<typename node::iterator>)
   {
      m_filtered_one = ::mzlib::ds::random(
         m_filtered_one->nodes(), 
         name, 
         rnd);
      return *this;
   }
   
   fluent_state_filter_one& next(std::string name)
   {
      m_filtered_one = ::mzlib::ds::next(
         m_filtered_one,
         name);
      return *this;
   }
   
   std::shared_ptr<attribute> get_attribute(std::string name)
   {
      return ::mzlib::ds::get_attribute(
         m_filtered_one,
         name);
   }
   
   fluent& use()
   {
      m_state_node = std::make_shared<fluent>(m_filtered_one);
      return *m_state_node.get();
   }
   
   operator mzlib::ds::node& ()
   {
      return *m_filtered_one;
   }
   
   operator std::shared_ptr<mzlib::ds::node> ()
   {
      return m_filtered_one;
   }
};
        
class fluent_state_attribute_added
{
private:
   
   // origin state for going back
   fluent& m_state_node;
   // temporary storage for the next state
   std::unique_ptr<fluent_state_attribute> m_attribute_state;
   
public:
   
   fluent_state_attribute_added(fluent& origin) :
      m_state_node(origin)
   {
   }
      
   fluent& set_name(std::string name)
   {
      return m_state_node.set_name(name);
   }
   
   fluent& set_value(std::string value)
   {
      return m_state_node.set_value(value);
   }
   
   fluent_state_attribute_added& add_attribute(std::string name, std::string value = "")
   {
      return m_state_node.add_attribute(name, value);
   }
   
   fluent& add_node(std::string name = "", std::string value = "")
   {
      return m_state_node.add_node(name, value);
   }
   
   fluent_state_attribute& use()
   {
      m_attribute_state = std::make_unique<fluent_state_attribute>(m_state_node);
      return *m_attribute_state.get();
   }
   
   fluent& stop_using()
   {
      return m_state_node.stop_using();
   }
   
   friend class fluent_state_attribute;
   
};


class fluent_state_attribute
{
private:
   
   // origin state for going back
   fluent& m_state_node;
   
public:

   fluent_state_attribute(fluent& origin) :
      m_state_node(origin)
   {
   }

   
   fluent_state_attribute& set_name(std::string name)
   {
      auto attribute = m_state_node.last_added_attribute();
      if (attribute) {
         attribute->set_name(name);
      }
      return *this;
   }
   
   fluent_state_attribute& set_value(std::string value)
   {
      auto attribute = m_state_node.last_added_attribute();
      if (attribute) {
         attribute->set_value(value);
      }
      return *this;
   }

   std::shared_ptr<attribute> get()
   {
      return m_state_node.last_added_attribute();
   }
   
   fluent& stop_using()
   {
      return m_state_node;
   }
   
};


} // namespace ds

} // namespace mzlib

#endif // MZLIB_DATASHELF_H

#ifdef MZLIB_DATASHELF_TESTS_H
#undef MZLIB_DATASHELF_TESTS_H

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
   node_ptr rating_node = mzlib::ds::fluent(m_shelf)
      .first("book")
      .first("rating");
   auto rating_attribute_source = mzlib::ds::fluent(m_shelf)
      .first("book")
      .first("rating")
      .get_attribute("source");
   ASSERT_EQ("Goodreads", rating_attribute_source->get_value());
   ASSERT_EQ("4.29", rating_node->get_value());
}

TEST_F(fixture_datashelf, conversion_from_filter_one_to_node)
{  
   mzlib::ds::node rating_node = 
      mzlib::ds::fluent(m_shelf)
         .first("book")
         .first("rating");
   
   ASSERT_EQ("4.29", rating_node.get_value());
}

TEST_F(fixture_datashelf, conversion_from_filter_one_to_node_ref)
{  
   mzlib::ds::node& rating_node = mzlib::ds::fluent(m_shelf)
      .first("book")
      .first("rating");
   
   ASSERT_EQ("4.29", rating_node.get_value());
   
   rating_node.set_value("5");
   
   ASSERT_EQ("5", mzlib::ds::fluent(m_shelf)
      .first("book")
      .first("rating")
      .get()->get_value());
}

TEST_F(fixture_datashelf, conversion_from_filter_one_to_node_ptr)
{  
   node_ptr rating_node = mzlib::ds::fluent(m_shelf)
      .first("book")
      .first("rating");
   
   ASSERT_EQ("4.29", rating_node->get_value());
}

TEST_F(fixture_datashelf, fluent_using_attribute)
{
   auto shelf = std::make_shared<mzlib::ds::node>();
   
   mzlib::ds::fluent(shelf)
      .add_node("node1", "node_value1")
         .use()
         .add_attribute("att1", "att_value1")
            .use()
            .set_name("att2")
            .set_value("att_value2")
            .stop_using()
         .set_name("node2")
         .set_value("node_value2")
         .stop_using();
   
   ASSERT_TRUE(mzlib::ds::fluent(shelf)
      .first("node1")
      .get()
      ->is_empty_node());
   
   ASSERT_EQ("node_value2", mzlib::ds::fluent(shelf)
      .first("node2")
      .get()
      ->get_value());
   
   ASSERT_TRUE(mzlib::ds::fluent(shelf)
      .first("node2")
      .get_attribute("att1")
      ->is_empty_node());
   
   ASSERT_EQ("att_value2", mzlib::ds::fluent(shelf)
      .first("node2")
      .get_attribute("att2")
      ->get_value());
}

TEST_F(fixture_datashelf, add_node_to_existing_structure)
{
   auto added_node = mzlib::ds::fluent(m_shelf)
      .first("book")
      .use()
      .add_node("new_node", "new_val")
      .use()
      .get();
   
   ASSERT_EQ(added_node, mzlib::ds::fluent(m_shelf)
      .first("book")
      .first("new_node")
      .get());
   
   ASSERT_EQ("new_val", mzlib::ds::fluent(m_shelf)
      .first("book")
      .first("new_node")
      .get()
      ->get_value());
}

TEST_F(fixture_datashelf, add_node_clean)
{
   auto root = std::make_shared<mzlib::ds::node>();
   auto added_node1 = mzlib::ds::fluent(root)
      .add_node("book", "Children of Time")
      .use()
      .get();
   
   auto added_node2 = mzlib::ds::fluent(root)
      .add_node("book", "Morning Star")
      .use()
      .get();
   
   ASSERT_EQ(added_node1, mzlib::ds::fluent(root)
      .first("book")
      .get());
   
   ASSERT_EQ("Children of Time", mzlib::ds::fluent(root)
      .first("book")
      .get()
      ->get_value());
 
   ASSERT_EQ(added_node2, mzlib::ds::fluent(root)
      .first("book")
      .next("book")
      .get());
   
   ASSERT_EQ("Morning Star", mzlib::ds::fluent(root)
      .first("book")
      .next("book")
      .get()
      ->get_value());
}

TEST_F(fixture_datashelf, add_attribute_to_existing_structure)
{
   auto added_attr = mzlib::ds::fluent(m_shelf)
      .first("book")
      .use()
         .add_attribute("pages", "like 500 or whatever")
         .use().get();
   
   ASSERT_EQ(added_attr, mzlib::ds::fluent(m_shelf)
      .first("book")
      .get_attribute("pages"));
   
   ASSERT_EQ("like 500 or whatever", mzlib::ds::fluent(m_shelf)
      .first("book")
      .get_attribute("pages")
      ->get_value());
}

TEST_F(fixture_datashelf, add_attribute_clean)
{
   auto root = std::make_shared<mzlib::ds::node>();
   auto added_att1 = mzlib::ds::fluent(root)
      .add_attribute("att1", "val1")
      .use()
      .get();
   
   auto added_att2 = mzlib::ds::fluent(root)
      .add_attribute("att2", "val2")
      .use()
      .get();
   
   ASSERT_EQ(added_att1, mzlib::ds::fluent(root)
      .get_attribute("att1"));

   ASSERT_EQ("val1", mzlib::ds::fluent(root)
      .get_attribute("att1")
      ->get_value());
 
   ASSERT_EQ(added_att2, mzlib::ds::fluent(root)
      .get_attribute("att2"));
   
   ASSERT_EQ("val2", mzlib::ds::fluent(root)
      .get_attribute("att2")
      ->get_value());
}

TEST_F(fixture_datashelf, querying_root_node)
{  
   ASSERT_EQ("shelf", m_shelf
      ->get_name());
   
   ASSERT_EQ("my bookshelf", mzlib::ds::fluent(m_shelf)
      .get_attribute("title")
      ->get_value());
}

TEST_F(fixture_datashelf, get_first_node)
{
   // note: first node is not a book
   auto first_book_node_name = mzlib::ds::fluent(m_shelf)
      .first("book")
      .get()
      ->get_name();
   
   auto first_airplane_node_name = mzlib::ds::fluent(m_shelf)
      .first("airplane")
      .get()
      ->get_name();
   
   ASSERT_EQ("book", first_book_node_name);
   ASSERT_EQ("airplane", first_airplane_node_name);
}

TEST_F(fixture_datashelf, get_first_node__no_such_node)
{
   auto does_not_exist = mzlib::ds::fluent(m_shelf)
      .first("ufo evidence")
      .get()
      ->get_name();
   
   ASSERT_EQ("", does_not_exist);
}

TEST_F(fixture_datashelf, get_attribute)
{
   // note: first node is not a book
   auto book_title = mzlib::ds::fluent(m_shelf)
      .first("book")
      .get_attribute("title")
      ->get_value();
   
   ASSERT_EQ("Children of Time", book_title);
}

TEST_F(fixture_datashelf, get_attribute__no_such_attribute)
{
   // note: first node is not a book
   auto book_notattribute = mzlib::ds::fluent(m_shelf)
      .first("book")
      .get_attribute("unattribute")
      ->get_value();
   
   ASSERT_EQ("", book_notattribute);
}

TEST_F(fixture_datashelf, get_next_node)
{
   auto next_book_title = mzlib::ds::fluent(m_shelf)
      .first("book")
      .next("book")
      .get_attribute("title")
      ->get_value();
   
   ASSERT_EQ("Morning Star", next_book_title);
}

TEST_F(fixture_datashelf, get_next_node__no_such_node)
{
   auto next_airplane_node_name = mzlib::ds::fluent(m_shelf)
      .first("airplane")
      .next("airplane")
      .get()
      ->get_name();
   
   // there is just one airplane on my shelf
   ASSERT_EQ("", next_airplane_node_name);
}

TEST_F(fixture_datashelf, get_all_nodes)
{
   auto all_nodes = m_shelf->nodes();
   
   ASSERT_EQ(4, all_nodes.size());
   ASSERT_EQ("airplane", all_nodes[0]->get_name());
   ASSERT_EQ("book", all_nodes[1]->get_name());
   ASSERT_EQ("folder", all_nodes[2]->get_name());
   ASSERT_EQ("book", all_nodes[3]->get_name());
}

TEST_F(fixture_datashelf, get_all_nodes_named)
{
   auto all_nodes = m_shelf->nodes();
   
   auto all_books = mzlib::ds::filter_by_name(all_nodes, "book");
   ASSERT_EQ(2, all_books.size());
   
   auto book1_title = mzlib::ds::get_attribute(all_books[0], "title");
   auto book2_title = mzlib::ds::get_attribute(all_books[1], "title");
   ASSERT_EQ("Children of Time", book1_title->get_value());
   ASSERT_EQ("Morning Star", book2_title->get_value());
}

TEST_F(fixture_datashelf, get_random_node)
{
   auto first_random_book = mzlib::ds::fluent(m_shelf).random("book", 
      // in-place mock
      [](const mzlib::ds::node::iterator& first, const mzlib::ds::node::iterator& last) -> mzlib::ds::node::iterator 
      {
         return first;
      });
   std::string first_random_book_title = first_random_book.get_attribute("title")->get_value();
   
   // note: there is a node between two books that is not a book
   // getting random book should not return non-book nodes
   
   auto second_random_book = mzlib::ds::fluent(m_shelf).random("book", 
      // in-place mock
      [](const mzlib::ds::node::iterator& first, const mzlib::ds::node::iterator& last) -> mzlib::ds::node::iterator 
      {
         return std::next(first);
      });
   std::string second_random_book_title = second_random_book.get_attribute("title")->get_value();
      
   ASSERT_EQ("Children of Time", first_random_book_title);
   ASSERT_EQ("Morning Star", second_random_book_title);
}

TEST_F(fixture_datashelf, get_random_node_when_empty)
{
   auto random_ufo_evidence = mzlib::ds::fluent(m_shelf).random("ufo evidence", 
      // in-place mock
      [](const mzlib::ds::node::iterator& first, const mzlib::ds::node::iterator& last) -> mzlib::ds::node::iterator 
      {
         return first;
      });
   
   // it didn't crash or anything like that
      
   ASSERT_TRUE(random_ufo_evidence.get()->is_empty_node());
}

TEST_F(fixture_datashelf, all_attributes)
{
   auto airplane_node = mzlib::ds::fluent(m_shelf)
      .first("airplane")
      .get();
   
   auto attributes = airplane_node
      ->attributes();
   
   ASSERT_EQ(3, attributes.size());
   ASSERT_EQ("model", attributes[0]->get_name());
   ASSERT_EQ("spitfire", attributes[0]->get_value());
   ASSERT_EQ("year", attributes[1]->get_name());
   ASSERT_EQ("1943", attributes[1]->get_value());
   ASSERT_EQ("designer", attributes[2]->get_name());
   ASSERT_EQ("R. J. Mitchell", attributes[2]->get_value());
}

TEST_F(fixture_datashelf, all_attributes_iteration__root)
{
   auto attributes = m_shelf->attributes();
   
   ASSERT_EQ(1, attributes.size());
   ASSERT_EQ("title", attributes[0]->get_name());
   ASSERT_EQ("my bookshelf", attributes[0]->get_value());
}



#endif // MZLIB_DATASHELF_TESTS_H
