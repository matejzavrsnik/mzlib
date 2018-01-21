//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_DATASHELF_H
#define MZLIB_DATASHELF_H

#include "../iterators/get_random.h"
#include "../string/is_just_whitespace.h"

#include <memory> // for shared ptr
#include <algorithm> // find_if

// The point of this whole thing is to have an in-memory data shelf
// for basic data needs, like settings or a collection of books or
// whatever. Such that is most conveniently stored in xml, but then
// needs further editing once in memory. Like changing settings, adding
// reviews to books and such, and then after that you want it to be
// easy to persist that back on the xml file, either during the process
// or in the end.

// Features an extensive and non-orthogonal interface which goes against 
// best practices, but if I want to have fluent interface on this thing, this 
// is the fastest way.


namespace mzlib {

namespace ds {
   
class base
{

private:
   
   std::string m_name;
   std::string m_value;
   
public:
   
   base(std::string name = "", std::string value = "") :
      m_name(name),
      m_value(value)
   {
   }
   
   std::string get_name() const
   {
      return m_name;
   }
   
   std::string get_value() const
   {
      return m_value;
   }

   void set_name(std::string name)
   {
      m_name = name;
   }
   
   void set_value(std::string value)
   {
      m_value = value;
   }
   
   bool has_empty_name() const
   {
      return (m_name.empty()  || mzlib::is_just_whitespaces(m_name));
   }

   bool has_empty_value() const
   {
      return (m_value.empty()  || mzlib::is_just_whitespaces(m_value));
   }

   bool is_empty_node() const
   {
      return (has_empty_name() && has_empty_value());
   }

};

// a new name just to avoid confusion
class attribute : public base
{
   
public:
   
   using base::base;
};

class node : public base, public std::enable_shared_from_this<node>
{
private:

   std::shared_ptr<node> m_parent;
   std::vector<std::shared_ptr<attribute>> m_attributes;
   std::vector<std::shared_ptr<node>> m_nodes;
   
public:   
   
   using node_it = std::vector<std::shared_ptr<node>>::iterator;
   
   node(
      std::string name = "", 
      std::string value = "", 
      std::shared_ptr<node> parent = nullptr) :
         base(name, value), 
         m_parent(parent)
   {
   }
   
   // attributes
   
   std::shared_ptr<attribute> add_attribute(std::string name, std::string value)
   {
      auto new_attribute = std::make_shared<attribute>(name, value);
      m_attributes.push_back(new_attribute);
      return new_attribute;
   }
   
   std::vector<std::shared_ptr<attribute>>::iterator begin_attributes ()
   {
      return m_attributes.begin();
   }
   
   std::vector<std::shared_ptr<attribute>>::iterator end_attributes ()
   {
      return m_attributes.end();
   }
   
   std::shared_ptr<attribute> get_attribute (std::string attribute_name)
   {
      auto attribute_it = std::find_if(m_attributes.begin(), m_attributes.end(),
         [&attribute_name] (const std::shared_ptr<attribute> att) {
            return att->get_name() == attribute_name;
         });
      if (attribute_it != m_attributes.end())
         return *attribute_it;
      return std::make_shared<attribute>();
   }
   
   // nodes
   
   std::shared_ptr<node> add_node(std::string name = "", std::string value = "")
   {
      auto new_node = std::make_shared<node>(name, value, shared_from_this());
      m_nodes.push_back(new_node);
      return new_node;
   }
   
   std::vector<std::shared_ptr<node>>::iterator begin_nodes ()
   {
      return m_nodes.begin();
   }
   
   std::vector<std::shared_ptr<node>>::iterator end_nodes ()
   {
      return m_nodes.end();
   }
   
   std::shared_ptr<node> get_all_nodes (std::string node_name)
   {
      std::shared_ptr<node> filter_node = std::make_shared<node>();
      for(auto node : m_nodes) {
         if(node->get_name() == node_name) {
            filter_node->m_nodes.push_back(node);
         }
      }
      return filter_node;
   }
   
   std::shared_ptr<node> get_random_node (
      std::string node_name,
      decltype(get_random_element<node_it>) rnd = get_random_element<node_it>)
   {
      std::vector<std::shared_ptr<node>> filtered_nodes;
      for(auto node : m_nodes) {
         if(node->get_name() == node_name) {
            filtered_nodes.push_back(node);
         }
      }
      return *rnd(filtered_nodes.begin(), filtered_nodes.end());
   }

   std::shared_ptr<node> get_first_node (std::string node_name)
   {
      for(auto node : m_nodes) {
         if(node->get_name() == node_name) {
            return node;
         }
      }
      return std::make_shared<node>();
   }
   
   std::shared_ptr<node> get_next_node()
   {
      auto empty_node = std::make_shared<node>();
      if (m_parent == nullptr) return empty_node;
      
      auto peers = m_parent->get_all_nodes(get_name());
      
      auto this_node = std::find_if(
         peers->m_nodes.begin(), peers->m_nodes.end(),
         [this](std::shared_ptr<node> node_in_parent) {
            return node_in_parent.get() == this;
         });
      if (this_node == peers->m_nodes.end()) {
         return empty_node;
      }
      auto next_node = ++this_node;
      if (next_node == peers->m_nodes.end()) { 
         return empty_node;
      }
      
      return *next_node;
   }
   
};

} // namespace xml

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
      m_shelf->set_name("shelf");
      m_shelf->add_attribute("title", "my bookshelf");
      auto airplane_node = m_shelf->add_node("airplane");
         airplane_node->add_attribute("model", "spitfire");
         airplane_node->add_attribute("year", "1943");
         airplane_node->add_attribute("designer", "R. J. Mitchell");
      auto book1_node = m_shelf->add_node("book");
         book1_node->add_attribute("title", "Children of Time");
         book1_node->add_node("rating", "4.29")->add_attribute("source", "Goodreads");
         book1_node->add_node("rating", "4.5")->add_attribute("source", "Amazon");
         book1_node->add_node("author", "Adrian Tchaikovsky");
         book1_node->add_node("year", "2016");
      m_shelf->add_node("folder")->add_node("coin_collection");
      auto book2_node = m_shelf->add_node("book");
         book2_node->add_attribute("title", "Morning Star");
         book2_node->add_node("rating", "4.5")->add_attribute("source", "Goodreads");
         book2_node->add_node("rating", "4.6")->add_attribute("source", "Amazon");
         book2_node->add_node("author", "Pierce Brown");
   }
   
   virtual void TearDown() {}
   
   std::shared_ptr<mzlib::ds::node> m_shelf;
};

TEST_F(fixture_datashelf, demo)
{  
   auto rating = m_shelf->get_first_node("book")->get_first_node("rating");
   ASSERT_EQ("Goodreads", rating->get_attribute("source")->get_value());
   ASSERT_EQ("4.29", rating->get_value());
}

TEST_F(fixture_datashelf, add_node_to_existing_structure)
{
   auto added_node = m_shelf->get_first_node("book")
      ->add_node("new_node", "new_val");
   
   ASSERT_EQ(added_node, m_shelf->get_first_node("book")
      ->get_first_node("new_node"));
   ASSERT_EQ("new_val", m_shelf->get_first_node("book")
      ->get_first_node("new_node")->get_value());
}

TEST_F(fixture_datashelf, add_node_clean)
{
   auto root = std::make_shared<mzlib::ds::node>();
   auto added_node1 = root->add_node("book", "Children of Time");
   auto added_node2 = root->add_node("book", "Morning Star");
   
   ASSERT_EQ(added_node1, root->get_first_node("book"));
   ASSERT_EQ("Children of Time", root->get_first_node("book")->get_value());
 
   ASSERT_EQ(added_node2, root->get_first_node("book")->get_next_node());
   ASSERT_EQ("Morning Star", root->get_first_node("book")->get_next_node()->get_value());
}

TEST_F(fixture_datashelf, add_attribute_to_existing_structure)
{
   auto added_attr = m_shelf->get_first_node("book")
      ->add_attribute("pages", "like 500 or whatever");
   
   ASSERT_EQ(added_attr, m_shelf->get_first_node("book")->get_attribute("pages"));
   ASSERT_EQ("like 500 or whatever", m_shelf->get_first_node("book")
      ->get_attribute("pages")->get_value());
}

TEST_F(fixture_datashelf, add_attribute_clean)
{
   auto root = std::make_shared<mzlib::ds::node>();
   auto added_att1 = root->add_attribute("att1", "val1");
   auto added_att2 = root->add_attribute("att2", "val2");
   
   ASSERT_EQ(added_att1, root->get_attribute("att1"));
   ASSERT_EQ("val1", root->get_attribute("att1")->get_value());
 
   ASSERT_EQ(added_att2, root->get_attribute("att2"));
   ASSERT_EQ("val2", root->get_attribute("att2")->get_value());
}

TEST_F(fixture_datashelf, querying_root_node)
{  
   ASSERT_EQ("shelf", m_shelf->get_name());
   ASSERT_EQ("my bookshelf", m_shelf->get_attribute("title")->get_value());
}

TEST_F(fixture_datashelf, get_first_node)
{
   // note: first node is not a book
   auto first_book_node_name = m_shelf->get_first_node("book")->get_name();
   auto first_airplane_node_name = m_shelf->get_first_node("airplane")->get_name();
   
   ASSERT_EQ("book", first_book_node_name);
   ASSERT_EQ("airplane", first_airplane_node_name);
}

TEST_F(fixture_datashelf, get_first_node__no_such_node)
{
   auto does_not_exist = m_shelf->get_first_node("ufo evidence")->get_name();
   
   ASSERT_EQ("", does_not_exist);
}

TEST_F(fixture_datashelf, get_attribute)
{
   // note: first node is not a book
   auto book = m_shelf->get_first_node("book");
   ASSERT_EQ("Children of Time", book->get_attribute("title")->get_value());
}

TEST_F(fixture_datashelf, get_attribute__no_such_attribute)
{
   // note: first node is not a book
   auto book = m_shelf->get_first_node("book");
   ASSERT_EQ("", book->get_attribute("unattribute")->get_value());
}

TEST_F(fixture_datashelf, get_next_node)
{
   auto next_book_title = m_shelf
      ->get_first_node("book")
      ->get_next_node()
      ->get_attribute("title")->get_value();
   
   ASSERT_EQ("Morning Star", next_book_title);
}

TEST_F(fixture_datashelf, get_next_node__no_such_node)
{
   auto next_airplane_node = m_shelf
      ->get_first_node("airplane")
      ->get_next_node();
   
   // there is just one airplane on my shelf
   ASSERT_EQ("", next_airplane_node->get_name());
}

TEST_F(fixture_datashelf, get_all_nodes_named)
{
   auto all_books = m_shelf->get_all_nodes("book");
   auto first_book_node = all_books->get_first_node("book");
   auto next_book_node = first_book_node->get_next_node();
   auto end_book_node = next_book_node->get_next_node();
   
   ASSERT_EQ("Children of Time", first_book_node->get_attribute("title")->get_value());
   ASSERT_EQ("Morning Star", next_book_node->get_attribute("title")->get_value());
   ASSERT_EQ("", end_book_node->get_attribute("title")->get_value());
}

TEST_F(fixture_datashelf, get_random_node)
{
   auto first_random_book = m_shelf->get_random_node("book", 
      // in-place mock
      [](const mzlib::ds::node::node_it& first, const mzlib::ds::node::node_it& last) -> mzlib::ds::node::node_it 
      {
         return first;
      });
   std::string first_random_book_title = first_random_book->get_attribute("title")->get_value();
   
   // note: there is a node between two books that is not a book
   // getting random book should not return non-book nodes
   
   auto second_random_book = m_shelf->get_random_node("book", 
      // in-place mock
      [](const mzlib::ds::node::node_it& first, const mzlib::ds::node::node_it& last) -> mzlib::ds::node::node_it 
      {
         return std::next(first);
      });
   std::string second_random_book_title = second_random_book->get_attribute("title")->get_value();
      
   ASSERT_EQ("Children of Time", first_random_book_title);
   ASSERT_EQ("Morning Star", second_random_book_title);
}

TEST_F(fixture_datashelf, all_attributes_iteration)
{
   auto airplane_node = m_shelf->get_first_node("airplane");
   std::vector<std::shared_ptr<mzlib::ds::attribute>> 
      attributes(airplane_node->begin_attributes(), airplane_node->end_attributes());
   
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
   std::vector<std::shared_ptr<mzlib::ds::attribute>> 
      attributes(m_shelf->begin_attributes(), m_shelf->end_attributes());
   
   ASSERT_EQ(1, attributes.size());
   ASSERT_EQ("title", attributes[0]->get_name());
   ASSERT_EQ("my bookshelf", attributes[0]->get_value());
}

TEST_F(fixture_datashelf, all_nodes_iteration)
{
   auto all_book_nodes = m_shelf->get_all_nodes("book");
   std::vector<std::shared_ptr<mzlib::ds::node>> 
      all_books(all_book_nodes->begin_nodes(), all_book_nodes->end_nodes());
   
   ASSERT_EQ(2, all_books.size());
   ASSERT_EQ("Children of Time", all_books[0]->get_attribute("title")->get_value());
   ASSERT_EQ("Morning Star", all_books[1]->get_attribute("title")->get_value());
}


#endif // MZLIB_DATASHELF_TESTS_H
