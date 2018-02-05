//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_EXTENSION_LIBXMLPP_H
#define MZLIB_EXTENSION_LIBXMLPP_H

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

inline bool is_content_node(const xmlpp::Node* node)
{
   const auto p = dynamic_cast<const xmlpp::ContentNode*>(node);
   return p != nullptr;
}

inline bool is_text_node(const xmlpp::Node* node)
{
   const auto p = dynamic_cast<const xmlpp::TextNode*>(node);
   return p != nullptr;
}

inline bool is_element(const xmlpp::Node* node)
{
   const auto p = dynamic_cast<const xmlpp::Element*>(node);
   return p != nullptr;
}

inline bool is_attribute(const xmlpp::Node* node)
{
   const auto p = dynamic_cast<const xmlpp::Attribute*>(node);
   return p != nullptr;
}

inline bool is_attribute_node(const xmlpp::Node* node)
{
   const auto p = dynamic_cast<const xmlpp::AttributeNode*>(node);
   return p != nullptr;
}

inline bool is_attribute_declaration(const xmlpp::Node* node)
{
   const auto p = dynamic_cast<const xmlpp::AttributeDeclaration*>(node);
   return p != nullptr;
}

inline bool has_attribute(
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

inline bool has_attributes(const xmlpp::Node* node)
{
   if (is_element(node)) {
      const auto element = dynamic_cast<const xmlpp::Element*>(node);
      return (element->get_attributes().size() > 0);
   }
   return false;
}

inline bool has_children(const xmlpp::Node* node)
{
   if (is_element(node)) {
      const auto element = dynamic_cast<const xmlpp::Element*>(node);
      return (element->get_children().size() > 0);
   }
   return false;
}

inline bool has_text_node(const xmlpp::Node* node)
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

inline std::string get_attribute_or_default(
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

inline std::string get_content_or_default(
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

inline bool is_empty_node(const xmlpp::Node* xmlpp_node)
{
   const std::string& name = xmlpp_node->get_name();
   const std::string& value = mzlib::get_content_or_default(xmlpp_node);
   return (name == "text" && value.empty());
}

} // namespace

#endif // MZLIB_EXTENSION_LIBXMLPP_H
