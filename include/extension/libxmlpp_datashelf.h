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

public:

   std::vector<attribute> attributes;
   std::vector<std::shared_ptr<node>> nodes;
   
   using node_it = std::vector<std::shared_ptr<node>>::iterator;

   std::shared_ptr<node> get_random (
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

   std::shared_ptr<node> get_first (std::string node_name)
   {
      for(auto node : nodes) {
         if(node->name == node_name) {
            return node;
         }
      }
      return std::make_shared<node>();
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

void fill_data_shelf(node& xml, const xmlpp::Node* node)
{
   // read common to all
   xml.name = node->get_name();
   xml.value = mzlib::get_content_or_default(node);
   if (mzlib::is_element(node)) {
      const auto element = dynamic_cast<const xmlpp::Element*>(node);

      // read attributes if any
      for (const xmlpp::Attribute* attribute : element->get_attributes()) {
         attribute new_attribute;
         new_attribute.name = attribute->get_name();
         new_attribute.value = attribute->get_value();
         xml.attributes.emplace_back(new_attribute);
      }

      // iteratively read child nodes if any
      for (const xmlpp::Node* child : element->get_children()) {
         xml.nodes.push_back(std::make_shared<node>());
         node& newly_inserted_node = *xml.nodes[xml.nodes.size()-1];
         fill_data_shelf(newly_inserted_node, child);
      }
   }
}

root create_data_shelf_from_string(std::string xml_string)
{
   xmlpp::DomParser parser;
   root data_shelf;
   // todo: when parsing doesn't succeed do something
   parser.parse_memory(xml_string);
   fill_data_shelf(data_shelf, parser.get_document()->get_root_node());

   return data_shelf;
}

root create_data_shelf_from_file(std::string path_to_xml_file)
{
   xmlpp::DomParser parser;
   root data_shelf;
   // todo: when parsing doesn't succeed do something
   parser.parse_file(path_to_xml_file);
   fill_data_shelf(data_shelf, parser.get_document()->get_root_node());

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
   
   mzlib::xml::root m_shelf;
};

TEST_F(fixture_datashelf, demo)
{  
   auto rating = m_shelf.get_first("book")->get_first("rating");
   ASSERT_EQ("Goodreads", rating->get_attribute("source")->value);
   ASSERT_EQ("4.29", rating->value);
}

TEST_F(fixture_datashelf, querying_root_node_works)
{  
   ASSERT_EQ("shelf", m_shelf.name);
   ASSERT_EQ("my bookshelf", m_shelf.get_attribute("title")->value);
}

TEST_F(fixture_datashelf, get_first_node)
{
   // note: first node is not a book
   auto first_book_node_name = m_shelf.get_first("book")->name;
   auto first_airplane_node_name = m_shelf.get_first("airplane")->name;
   
   ASSERT_EQ("book", first_book_node_name);
   ASSERT_EQ("airplane", first_airplane_node_name);
}

TEST_F(fixture_datashelf, get_first_node__no_such_node)
{
   auto does_not_exist = m_shelf.get_first("ufo evidence")->name;
   
   ASSERT_EQ("", does_not_exist);
}

TEST_F(fixture_datashelf, get_random_node)
{
   auto first_random_book = m_shelf.get_random("book", 
      // in-place mock
      [](const mzlib::xml::node::node_it& first, const mzlib::xml::node::node_it& last) -> mzlib::xml::node::node_it 
      {
         return first;
      });
   std::string first_random_book_title = first_random_book->get_attribute("title")->value;
   
   // note: there is a node between two books that is not a book
   // getting random book should not return non-book nodes
   
   auto second_random_book = m_shelf.get_random("book", 
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

