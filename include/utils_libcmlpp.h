//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef UTILS_LIBXMLPP_H
#define UTILS_LIBXMLPP_H

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

namespace mzlib {
namespace util {

// defined in libxml++.h
// if project includes libxml++ lib, it will see, compile, and be able to use the following functions
#ifdef __LIBXMLCPP_H

inline void delete_all_but (std::vector<std::string> names, xmlpp::Node* from_node) 
{
   if (from_node == nullptr) return;
   std::list<xmlpp::Node*> children = from_node->get_children();
   for (xmlpp::Node* child : children) {
      std::string child_name = child->get_name();
      bool found = (std::find(names.begin(), names.end(), child_name) != names.end());
      if (!found) {
          from_node->remove_child(child);
      }
   }
}

inline void delete_all_attributes_but (std::vector<std::string> names, xmlpp::Node* from_node)
{
   xmlpp::Element* from_element = dynamic_cast<xmlpp::Element*>(from_node);
   if (from_element == nullptr) return;
   std::list<xmlpp::Attribute*> attributes_list = from_element->get_attributes();
   for (xmlpp::Attribute* attribute : attributes_list) {
      std::string attribute_name = attribute->get_name();
      bool found = (std::find(names.begin(), names.end(), attribute_name) != names.end());
      if (!found) {
         from_node->remove_child(attribute);
      }
   }
}

inline void delete_all_attributes (xmlpp::Node* from_node)
{
   delete_all_attributes_but({}, from_node);
}

inline void delete_all_but_xpath (std::string xpath, xmlpp::Node* from_node) 
{
   std::vector<xmlpp::Node*> content_div = from_node->find(xpath);
   if(content_div.size() > 0) {
      xmlpp::Document tempXmlDocument;
      tempXmlDocument.create_root_node_by_import(content_div[0]);
      delete_all_but({}, from_node);
      from_node->import_node(tempXmlDocument.get_root_node());
   }
}

inline void delete_all_xpath (std::string xpath, xmlpp::Node* from_node) 
{
   std::vector<xmlpp::Node*> nodes_found = from_node->find(xpath);
   for (xmlpp::Node* node_found : nodes_found) {
      xmlpp::Node* parent = node_found->get_parent();
      parent->remove_child(node_found);
   }
}

inline std::string get_content (std::string xpath, xmlpp::Node* from_node)
{
   if (from_node == nullptr) return "";
   std::string content;
   std::vector<xmlpp::Node*> nodes_found = from_node->find(xpath);
   if (nodes_found.size() > 0) {
      std::list<xmlpp::Node*> children = nodes_found[0]->get_children();
      if (children.size() > 0) {
         xmlpp::ContentNode* content_node = dynamic_cast<xmlpp::ContentNode*>(children.front());
         if (content_node != nullptr) {
            content = content_node->get_content();
         }
      }
   }
   return content;
}
#endif
    
} } // namespace mzlib::util

#endif // UTILS_LIBXMLPP_H

