//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_TOOLS_LIBXMLPP_H
#define MZLIB_TOOLS_LIBXMLPP_H

#include <libxml++/libxml++.h>

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <locale>
#include <fstream>
#include <dirent.h>
#include <list>

namespace mzlib {

bool is_content_node(const xmlpp::Node* node)
{
   const auto p = dynamic_cast<const xmlpp::ContentNode*>(node);
   return p != nullptr;
}

bool is_text_node(const xmlpp::Node* node)
{
   const auto p = dynamic_cast<const xmlpp::TextNode*>(node);
   return p != nullptr;
}

bool is_element(const xmlpp::Node* node)
{
   const auto p = dynamic_cast<const xmlpp::Element*>(node);
   return p != nullptr;
}

bool is_attribute(const xmlpp::Node* node)
{
   const auto p = dynamic_cast<const xmlpp::Attribute*>(node);
   return p != nullptr;
}

bool is_attribute_node(const xmlpp::Node* node)
{
   const auto p = dynamic_cast<const xmlpp::AttributeNode*>(node);
   return p != nullptr;
}

bool is_attribute_declaration(const xmlpp::Node* node)
{
   const auto p = dynamic_cast<const xmlpp::AttributeDeclaration*>(node);
   return p != nullptr;
}

bool has_attribute(
   const xmlpp::Node* node, 
   std::string attribute_name)
{
   if (is_element(node)) {
      const auto element = dynamic_cast<const xmlpp::Element*>(node);
      const auto attribute = element->get_attribute(attribute_name);
      if (attribute) {
         return true;
      }
   }
   return false;
}

bool has_attributes(const xmlpp::Node* node)
{
   if (is_element(node)) {
      const auto element = dynamic_cast<const xmlpp::Element*>(node);
      return (element->get_attributes().size() > 0);
   }
   return false;
}

bool has_children(const xmlpp::Node* node)
{
   if (is_element(node)) {
      const auto element = dynamic_cast<const xmlpp::Element*>(node);
      return (element->get_children().size() > 0);
   }
   return false;
}

bool has_text_node(const xmlpp::Node* node)
{
   if (is_element(node)) {
      const auto element = dynamic_cast<const xmlpp::Element*>(node);
      const auto text_node = element->get_child_text();
      if (text_node) {
         return true;
      }
   }
   return false;
}

std::string get_attribute_or_default(
   const xmlpp::Node* node, 
   std::string attribute_name, 
   std::string default_value = "")
{
   if (has_attribute(node, attribute_name)) {
      const auto element = dynamic_cast<const xmlpp::Element*>(node);
      element->get_attribute(attribute_name)->get_value();
   }
   return default_value;
}

std::string get_content_or_default(
   const xmlpp::Node* node, 
   std::string default_value = "")
{
   if (has_text_node(node)) {
        const auto element = dynamic_cast<const xmlpp::Element*>(node);
        return element->get_child_text()->get_content();
    }
    return default_value;
}
   
inline void delete_all_children_except (std::vector<std::string> names, xmlpp::Node* from_node) 
{
   if (has_children(from_node)) {
      std::list<xmlpp::Node*> children = from_node->get_children();
      for (xmlpp::Node* child : children) {
         std::string child_name = child->get_name();
         bool found = (std::find(names.begin(), names.end(), child_name) != names.end());
         if (!found) {
             from_node->remove_child(child);
         }
      }
   }
}

inline void delete_all_attributes_except (std::vector<std::string> names, xmlpp::Node* from_node)
{
   if (has_attributes(from_node)) {
      xmlpp::Element* from_element = dynamic_cast<xmlpp::Element*>(from_node);
      std::list<xmlpp::Attribute*> attributes_list = from_element->get_attributes();
      for (xmlpp::Attribute* attribute : attributes_list) {
         std::string attribute_name = attribute->get_name();
         bool found = (std::find(names.begin(), names.end(), attribute_name) != names.end());
         if (!found) {
            from_node->remove_child(attribute);
         }
      }
   }
}

inline void delete_all_attributes (xmlpp::Node* from_node)
{
   delete_all_attributes_except({}, from_node);
}

inline void delete_all_xpath (std::string xpath, xmlpp::Node* from_node) 
{
   std::vector<xmlpp::Node*> nodes_found = from_node->find(xpath);
   for (xmlpp::Node* node_found : nodes_found) {
      xmlpp::Node* parent = node_found->get_parent();
      parent->remove_child(node_found);
   }
}
  
} // namespace

#endif // MZLIB_TOOLS_LIBXMLPP_H

#ifdef MZLIB_TOOLS_LIBXMLPP_TESTS_H
#undef MZLIB_TOOLS_LIBXMLPP_TESTS_H

TEST(delete_all_children_except, demo) 
{
   xmlpp::DomParser parser;
   xmlpp::Element* root;
   
   std::string xml_file = R"(
   <show title="The Expanse">
      <chrisjen>Shohreh Aghdashloo</chrisjen>
      <amos>Wes Chatham</amos>
      <naomi>Dominique Tipper</naomi>
      <miller>Thomas Jane</miller>
   </show>
   )";

   parser.parse_memory(xml_file);
   root = parser.get_document()->get_root_node();
   
   mzlib::delete_all_children_except({"chrisjen", "amos"}, root);
   
   ASSERT_TRUE (root->get_children("chrisjen").size() > 0);
   ASSERT_TRUE (root->get_children("amos").size() > 0);
   ASSERT_FALSE(root->get_children("naomi").size() > 0);
   ASSERT_FALSE(root->get_children("miller").size() > 0);
}

TEST(delete_all_children_except, empty) 
{
   xmlpp::DomParser parser;
   xmlpp::Element* root;
   
   std::string xml_file = R"(
   <show title="The Expanse">
      <chrisjen>Shohreh Aghdashloo</chrisjen>
      <amos>Wes Chatham</amos>
      <naomi>Dominique Tipper</naomi>
      <miller>Thomas Jane</miller>
   </show>
   )";

   parser.parse_memory(xml_file);
   root = parser.get_document()->get_root_node();
   
   mzlib::delete_all_children_except({}, root);
   
   ASSERT_FALSE(root->get_children("chrisjen").size() > 0);
   ASSERT_FALSE(root->get_children("amos").size() > 0);
   ASSERT_FALSE(root->get_children("naomi").size() > 0);
   ASSERT_FALSE(root->get_children("miller").size() > 0);
}

TEST(delete_all_attributes_except, demo) 
{
   xmlpp::DomParser parser;
   xmlpp::Element* root;
   
   std::string xml_file = R"(
   <show title="The Expanse" genre="scifi" channel="SyFy" on_netflix="yes">
   </show>
   )";

   parser.parse_memory(xml_file);
   root = parser.get_document()->get_root_node();
   
   mzlib::delete_all_attributes_except({"title", "genre"}, root);
   
   ASSERT_TRUE (root->get_attribute("title") != nullptr);
   ASSERT_TRUE (root->get_attribute("genre") != nullptr);
   ASSERT_FALSE(root->get_attribute("channel") != nullptr);
   ASSERT_FALSE(root->get_attribute("on_netflix") != nullptr);
}

TEST(delete_all_attributes, demo) 
{
   xmlpp::DomParser parser;
   xmlpp::Element* root;
   
   std::string xml_file = R"(
   <show title="The Expanse" genre="scifi" channel="SyFy" on_netflix="yes">
   </show>
   )";

   parser.parse_memory(xml_file);
   root = parser.get_document()->get_root_node();
   
   mzlib::delete_all_attributes(root);
   mzlib::delete_all_attributes(root);
   
   ASSERT_TRUE(root->get_attribute("title") == nullptr);
   ASSERT_TRUE(root->get_attribute("genre") == nullptr);
   ASSERT_TRUE(root->get_attribute("channel") == nullptr);
   ASSERT_TRUE(root->get_attribute("on_netflix") == nullptr);
}

TEST(delete_all_xpath, demo) 
{
   xmlpp::DomParser parser;
   xmlpp::Element* root;
   
   std::string xml_file = R"(
   <show title="The Expanse">
      <ships>
         <mars>Rocinante</mars>
         <mars>Donnager</mars>
         <mormons>Nauvoo</mormons>
         <unn>Arboghast</unn>
      </ships>
      <characters>
         <mars>Theresa Yao</mars>
         <mars>Sutton</mars>
         <mormons>Elder McCann</mormons>
         <unn>Chrisjen Avasarala</unn>
      </characters>
   </show>
   )";

   parser.parse_memory(xml_file);
   root = parser.get_document()->get_root_node();
   
   mzlib::delete_all_xpath("/show/*/mars", root);
   
   ASSERT_FALSE(root->find("/show/ships/mars").size() > 0);
   ASSERT_FALSE(root->find("/show/characters/mars").size() > 0);
   
   ASSERT_TRUE(root->find("/show/ships/mormons").size() > 0);
   ASSERT_TRUE(root->find("/show/ships/unn").size() > 0);
   ASSERT_TRUE(root->find("/show/characters/mormons").size() > 0);
   ASSERT_TRUE(root->find("/show/characters/unn").size() > 0);
}

#endif // MZLIB_TOOLS_LIBXMLPP_TESTS_H

