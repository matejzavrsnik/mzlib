//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_EXTENSION_LIBXMLPP_DATASHELF_H
#define MZLIB_EXTENSION_LIBXMLPP_DATASHELF_H

#include "libxmlpp.h"

#include "../iterators/get_random.h"

// The point of this whole thing is to have an in-memory data shelf
// for basic data needs, like settings or a collection of books or
// whatever. Such that is most conveniently stored in xml, but then
// need further editing once in memory. Like changing settings, adding
// reviews to books and such, and then after that you want it to be
// easy to persist that back on the xml file, either during the process
// or in the end. (I have yet to add the saving part.)

namespace mzlib {

namespace xml {
   
class base
{

public:
   
   std::string name;
   std::string value;

};

// a new name just to avoid confusion
class attribute : public base
{
};

class node : public base
{
private:

   std::shared_ptr<node> m_parent;
   
public:

   std::vector<attribute> attributes;
   std::vector<std::shared_ptr<node>> nodes;
   
   using node_it = std::vector<std::shared_ptr<node>>::iterator;
   
   node(std::shared_ptr<node> parent = nullptr) :
      m_parent(parent)
   {
   }
   
   std::shared_ptr<node> get_all_nodes (std::string node_name)
   {
      std::shared_ptr<node> filter_node = std::make_shared<node>();
      for(auto node : nodes) {
         if(node->name == node_name) {
            filter_node->nodes.push_back(node);
         }
      }
      return filter_node;
   }
   
   std::shared_ptr<node> get_random_node (
      std::string node_name,
      decltype(get_random_element<node_it>) rnd = get_random_element<node_it>)
   {
      std::vector<std::shared_ptr<node>> filtered_nodes;
      for(auto node : nodes) {
         if(node->name == node_name) {
            filtered_nodes.push_back(node);
         }
      }
      return *rnd(filtered_nodes.begin(), filtered_nodes.end());
   }

   std::shared_ptr<node> get_first_node (std::string node_name)
   {
      for(auto node : nodes) {
         if(node->name == node_name) {
            return node;
         }
      }
      return std::make_shared<node>();
   }
   
   std::shared_ptr<node> get_next_node()
   {
      auto empty_node = std::make_shared<node>();
      if (m_parent == nullptr) return empty_node;
      
      auto peers = m_parent->get_all_nodes(name);
      
      auto this_node = std::find_if(
         peers->nodes.begin(), peers->nodes.end(),
         [this](std::shared_ptr<node> node_in_parent) {
            return node_in_parent.get() == this;
         });
      if (this_node == peers->nodes.end()) {
         return empty_node;
      }
      auto next_node = ++this_node;
      if (next_node == peers->nodes.end()) { 
         return empty_node;
      }
      
      return *next_node;
   }
   
   attribute* get_attribute (std::string attribute_name)
   {
      auto attribute_it = std::find_if(attributes.begin(), attributes.end(),
         [&attribute_name] (const attribute& att) {
            return att.name == attribute_name;
         });
      if (attribute_it != attributes.end())
         return &*attribute_it;
      return nullptr;
   }
};

// new name just to avoid confusion
class root : public node
{
};

void fill_node(std::shared_ptr<xml::node> xml_node, const xmlpp::Node* node)
{
   // read common to all
   xml_node->name = node->get_name();
   xml_node->value = mzlib::get_content_or_default(node);
   if (mzlib::is_element(node)) {
      const auto element = dynamic_cast<const xmlpp::Element*>(node);

      // read attributes if any
      for (const xmlpp::Attribute* attribute : element->get_attributes()) {
         xml::attribute new_attribute;
         new_attribute.name = attribute->get_name();
         new_attribute.value = attribute->get_value();
         xml_node->attributes.emplace_back(new_attribute);
      }

      // iteratively read child nodes if any
      for (const xmlpp::Node* child : element->get_children()) {
         xml_node->nodes.push_back(std::make_shared<xml::node>(xml_node));
         std::shared_ptr<xml::node> newly_inserted_node = *std::prev(xml_node->nodes.end());
         fill_node(newly_inserted_node, child);
      }
   }
}

std::shared_ptr<root> create_data_shelf_from_string(std::string xml_string)
{
   xmlpp::DomParser parser;
   std::shared_ptr<root> data_shelf = std::make_shared<root>();
   // todo: when parsing doesn't succeed do something
   parser.parse_memory(xml_string);
   fill_node(data_shelf, parser.get_document()->get_root_node());

   return data_shelf;
}

std::shared_ptr<root> create_data_shelf_from_file(std::string path_to_xml_file)
{
   xmlpp::DomParser parser;
   std::shared_ptr<root> data_shelf = std::make_shared<root>();
   // todo: when parsing doesn't succeed do something
   parser.parse_file(path_to_xml_file);
   fill_node(data_shelf, parser.get_document()->get_root_node());

   return data_shelf;
}

} // namespace xml

} // namespace mzlib

#endif // MZLIB_EXTENSION_LIBXMLPP_DATASHELF_H

#ifdef MZLIB_EXTENSION_LIBXMLPP_DATASHELF_TESTS_H
#undef MZLIB_EXTENSION_LIBXMLPP_DATASHELF_TESTS_H

class fixture_datashelf : public ::testing::Test 
{

protected:

   fixture_datashelf() {}
   virtual ~fixture_datashelf() {}
   
   virtual void SetUp() 
   {
      m_shelf = mzlib::xml::create_data_shelf_from_string(m_xml);
   }
   
   virtual void TearDown() {}
   
   std::string m_xml = R"(
      <shelf title="my bookshelf">
         <airplane model="spitfire"/>
         <book title="Children of Time">
            <rating source="Goodreads">4.29</rating>
            <rating source="Amazon">4.5</rating>
            <author>Adrian Tchaikovsky</author>
            <year>2016</year>
         </book>
         <folder>
            <coin_collection></coin_collection>
         </folder>
         <book title="Morning Star">
            <rating source="Goodreads">4.5</rating>
            <rating source="Amazon">4.6</rating>
            <author>Pierce Brown</author>
         </book>
      </shelf>
   )";
   
   std::shared_ptr<mzlib::xml::root> m_shelf;
};

TEST_F(fixture_datashelf, demo)
{  
   auto rating = m_shelf->get_first_node("book")->get_first_node("rating");
   ASSERT_EQ("Goodreads", rating->get_attribute("source")->value);
   ASSERT_EQ("4.29", rating->value);
}

TEST_F(fixture_datashelf, querying_root_node_works)
{  
   ASSERT_EQ("shelf", m_shelf->name);
   ASSERT_EQ("my bookshelf", m_shelf->get_attribute("title")->value);
}

TEST_F(fixture_datashelf, get_first_node)
{
   // note: first node is not a book
   auto first_book_node_name = m_shelf->get_first_node("book")->name;
   auto first_airplane_node_name = m_shelf->get_first_node("airplane")->name;
   
   ASSERT_EQ("book", first_book_node_name);
   ASSERT_EQ("airplane", first_airplane_node_name);
}

TEST_F(fixture_datashelf, get_first_node__no_such_node)
{
   auto does_not_exist = m_shelf->get_first_node("ufo evidence")->name;
   
   ASSERT_EQ("", does_not_exist);
}

TEST_F(fixture_datashelf, get_next_node)
{
   auto next_book_title = m_shelf
      ->get_first_node("book")
      ->get_next_node()
      ->get_attribute("title")->value;
   
   ASSERT_EQ("Morning Star", next_book_title);
}

TEST_F(fixture_datashelf, get_next_node__no_such_node)
{
   auto next_airplane_node = m_shelf
      ->get_first_node("airplane")
      ->get_next_node();
   
   // there is just one airplane on my shelf
   ASSERT_EQ("", next_airplane_node->name);
}

TEST_F(fixture_datashelf, get_all_nodes_named)
{
   auto all_books = m_shelf->get_all_nodes("book");
   auto first_book_node = all_books->get_first_node("book");
   auto next_book_node = first_book_node->get_next_node();
   auto end_book_node = next_book_node->get_next_node();
   
   ASSERT_EQ("Children of Time", first_book_node->get_attribute("title")->value);
   ASSERT_EQ("Morning Star", next_book_node->get_attribute("title")->value);
   ASSERT_EQ(nullptr, end_book_node->get_attribute("title"));
}

TEST_F(fixture_datashelf, get_random_node)
{
   auto first_random_book = m_shelf->get_random_node("book", 
      // in-place mock
      [](const mzlib::xml::node::node_it& first, const mzlib::xml::node::node_it& last) -> mzlib::xml::node::node_it 
      {
         return first;
      });
   std::string first_random_book_title = first_random_book->get_attribute("title")->value;
   
   // note: there is a node between two books that is not a book
   // getting random book should not return non-book nodes
   
   auto second_random_book = m_shelf->get_random_node("book", 
      // in-place mock
      [](const mzlib::xml::node::node_it& first, const mzlib::xml::node::node_it& last) -> mzlib::xml::node::node_it 
      {
         return std::next(first);
      });
   std::string second_random_book_title = second_random_book->get_attribute("title")->value;
      
   ASSERT_EQ("Children of Time", first_random_book_title);
   ASSERT_EQ("Morning Star", second_random_book_title);
}

#endif // MZLIB_EXTENSION_LIBXMLPP_DATASHELF_TESTS_H

