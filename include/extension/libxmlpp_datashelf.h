//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_EXTENSION_LIBXMLPP_DATASHELF_H
#define MZLIB_EXTENSION_LIBXMLPP_DATASHELF_H

#include "libxmlpp.h"

#include "../tools/datashelf.h"

namespace mzlib {

inline void fill_my_node_from_xmlpp(std::shared_ptr<ds::node> my_node, const xmlpp::Node* xmlpp_node)
{
   // read common to all
   if (!is_empty_node(xmlpp_node)) {
      my_node->set_name(xmlpp_node->get_name());
      my_node->set_value(mzlib::get_content_or_default(xmlpp_node));
   }
   
   if (mzlib::is_element(xmlpp_node)) {
      const auto xmlpp_element = dynamic_cast<const xmlpp::Element*>(xmlpp_node);

      // read attributes if any
      for (const xmlpp::Attribute* xmlpp_attribute : xmlpp_element->get_attributes()) {
         ds::fluent(my_node).add_attribute(
            xmlpp_attribute->get_name(), 
            xmlpp_attribute->get_value());
      }

      // iteratively read child nodes if any
      for (const xmlpp::Node* xmlpp_child_node : xmlpp_element->get_children()) {
         fill_my_node_from_xmlpp(
            ds::fluent(my_node).add_node().use().get(), 
            xmlpp_child_node);
      }
   }
}

inline void fill_xmlpp_node_from_mine(xmlpp::Element* xmlpp_element, const std::shared_ptr<ds::node> my_node)
{
   //todo: this part is basically conversion. make function for that
   if (!my_node->has_empty_name()) {
      xmlpp_element->set_name(my_node->get_name());
   }
   if (!my_node->has_empty_value()) {
      xmlpp_element->set_child_text(my_node->get_value());
   }

   // read attributes if any
   for(auto my_attribute = my_node->begin_attributes(); 
      my_attribute != my_node->end_attributes(); 
      ++my_attribute) 
   {
      const std::string& name = (*my_attribute)->get_name();
      const std::string& value = (*my_attribute)->get_value();
      xmlpp_element->set_attribute(name, value);
   }

   // iteratively read child nodes if any
   for(auto my_child = my_node->begin_nodes();
      my_child != my_node->end_nodes();
      ++my_child) 
   {
      if (!(*my_child)->is_empty_node()) {
         xmlpp::Element* xmlpp_child = xmlpp_element->add_child("");
         fill_xmlpp_node_from_mine(xmlpp_child, *my_child);
      }
   }

}

inline std::shared_ptr<ds::node> create_datashelf_from_xml_string(std::string xml_string)
{
   xmlpp::DomParser parser;
   std::shared_ptr<ds::node> data_shelf = std::make_shared<ds::node>();
   // todo: when parsing doesn't succeed do something
   parser.parse_memory(xml_string);
   fill_my_node_from_xmlpp(data_shelf, parser.get_document()->get_root_node());

   return data_shelf;
}

inline std::shared_ptr<ds::node> create_data_shelf_from_xml_file(std::string path_to_xml_file)
{
   xmlpp::DomParser parser;
   std::shared_ptr<ds::node> data_shelf = std::make_shared<ds::node>();
   // todo: when parsing doesn't succeed do something
   parser.parse_file(path_to_xml_file);
   fill_my_node_from_xmlpp(data_shelf, parser.get_document()->get_root_node());

   return data_shelf;
}

inline std::string save_datashelf_to_xml_string(std::shared_ptr<ds::node> shelf)
{
   xmlpp::DomParser parser;
   auto root = parser.get_document()->create_root_node("");
   fill_xmlpp_node_from_mine(root, shelf);
   const std::string doc = parser.get_document()->write_to_string_formatted();
   return doc;
}

inline void save_datashelf_to_xml_file(std::shared_ptr<ds::node> shelf, std::string path_to_xml_file)
{
   xmlpp::DomParser parser;
   auto root = parser.get_document()->create_root_node("");
   fill_xmlpp_node_from_mine(root, shelf);
   parser.get_document()->write_to_file_formatted(path_to_xml_file);
}

} // namespace mzlib

#endif // MZLIB_EXTENSION_LIBXMLPP_DATASHELF_H

#ifdef MZLIB_EXTENSION_LIBXMLPP_DATASHELF_TESTS_H
#undef MZLIB_EXTENSION_LIBXMLPP_DATASHELF_TESTS_H

class fixture_datashelf_former : public ::testing::Test 
{

protected:

   fixture_datashelf_former() {}
   virtual ~fixture_datashelf_former() {}
   
   virtual void SetUp() {}
   virtual void TearDown() {}
   
   std::string m_xml = R"(
      <shelf title="my bookshelf">
         <airplane model="spitfire" year="1943" designer="R. J. Mitchell"/>
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
};

TEST_F(fixture_datashelf_former, create_datashelf_from_xml_string_demo)
{  
   auto shelf = mzlib::create_datashelf_from_xml_string(m_xml);
   auto rating = shelf->get_first_node("book")->get_first_node("rating");
   ASSERT_EQ("Goodreads", rating->get_attribute("source")->get_value());
   ASSERT_EQ("4.29", rating->get_value());
}

TEST_F(fixture_datashelf_former, save_datashelf_to_xml_string_demo)
{  
   auto shelf = mzlib::create_datashelf_from_xml_string(m_xml);
   std::string created = mzlib::save_datashelf_to_xml_string(shelf);
   
   std::string expected = R"(<?xml version="1.0" encoding="UTF-8"?>
<shelf title="my bookshelf">
  <airplane model="spitfire" year="1943" designer="R. J. Mitchell"/>
  <book title="Children of Time">
    <rating source="Goodreads">4.29</rating>
    <rating source="Amazon">4.5</rating>
    <author>Adrian Tchaikovsky</author>
    <year>2016</year>
  </book>
  <folder>
    <coin_collection/>
  </folder>
  <book title="Morning Star">
    <rating source="Goodreads">4.5</rating>
    <rating source="Amazon">4.6</rating>
    <author>Pierce Brown</author>
  </book>
</shelf>
)";

   ASSERT_EQ(expected, created);
}

#endif // MZLIB_EXTENSION_LIBXMLPP_DATASHELF_TESTS_H

