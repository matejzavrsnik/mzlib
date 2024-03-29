//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_EXTENSION_LIBXMLPP_DATASHELF_H
#define MZLIB_EXTENSION_LIBXMLPP_DATASHELF_H

#include "libxmlpp.h"

#include "../../tools/datashelf.h"

namespace mzlib {

inline void fill_my_node_from_xmlpp(std::shared_ptr<ds::node> my_node, const xmlpp::Node* xmlpp_node)
{
   // read common to all
   if (!is_empty_node(xmlpp_node)) {
      my_node->set_name(convert<std::string_view>(xmlpp_node->get_name()));
      my_node->set_value(mzlib::get_content_or_default(xmlpp_node));
   }
   
   if (mzlib::is_element(xmlpp_node)) {
      const auto xmlpp_element = dynamic_cast<const xmlpp::Element*>(xmlpp_node);

      // read attributes if any
      for (const xmlpp::Attribute* xmlpp_attribute : xmlpp_element->get_attributes()) {
         my_node->add_attribute(
            convert<std::string_view>(xmlpp_attribute->get_name()), 
            convert<std::string_view>(xmlpp_attribute->get_value()));
      }

      // iteratively read child nodes if any
      for (const xmlpp::Node* xmlpp_child_node : xmlpp_element->get_children()) {
         fill_my_node_from_xmlpp(
            my_node->add_node(), 
            xmlpp_child_node);
      }
   }
}

inline void fill_xmlpp_node_from_mine(xmlpp::Element* xmlpp_element, const ds::node* const my_node)
{
   //todo: this part is basically conversion. make function for that
   if (!my_node->has_empty_name()) {
      xmlpp_element->set_name(
         convert<xmlpp::ustring>(my_node->name()));
   }
   if (!my_node->has_empty_value()) {
      xmlpp_element->set_first_child_text(
         convert<xmlpp::ustring>(my_node->value()));
   }

   // read attributes if any
   for(auto my_attribute : my_node->attributes()) 
   {
      std::string_view name = my_attribute->name();
      std::string_view value = my_attribute->value();
      xmlpp_element->set_attribute(
         convert<xmlpp::ustring>(name),
         convert<xmlpp::ustring>(value));
   }

   // iteratively read child nodes if any
   for(auto my_child : my_node->nodes()) 
   {
      if (!my_child->is_empty()) {
         xmlpp::Element* xmlpp_child = xmlpp_element->add_child_element("");
         fill_xmlpp_node_from_mine(xmlpp_child, my_child.get());
      }
   }

}

inline std::shared_ptr<ds::node> create_datashelf_from_xml_string(std::string_view xml_string)
{
   xmlpp::DomParser parser;
   std::shared_ptr<ds::node> data_shelf = std::make_shared<ds::node>();
   // todo: when parsing doesn't succeed do something
   parser.parse_memory(xml_string.data());
   fill_my_node_from_xmlpp(data_shelf, parser.get_document()->get_root_node());

   return data_shelf;
}

inline std::shared_ptr<ds::node> create_data_shelf_from_xml_file(std::string_view path_to_xml_file)
{
   xmlpp::DomParser parser;
   std::shared_ptr<ds::node> data_shelf = std::make_shared<ds::node>();
   // todo: when parsing doesn't succeed do something
   parser.parse_file(path_to_xml_file.data());
   fill_my_node_from_xmlpp(data_shelf, parser.get_document()->get_root_node());

   return data_shelf;
}

inline std::string save_datashelf_to_xml_string(std::shared_ptr<ds::node> shelf)
{
   xmlpp::DomParser parser;
   auto root = parser.get_document()->create_root_node("");
   fill_xmlpp_node_from_mine(root, shelf.get());
   std::string doc = parser.get_document()->write_to_string_formatted();
   return doc;
}

inline void save_datashelf_to_xml_file(std::shared_ptr<ds::node> shelf, std::string_view path_to_xml_file)
{
   xmlpp::DomParser parser;
   auto root = parser.get_document()->create_root_node("");
   fill_xmlpp_node_from_mine(root, shelf.get());
   parser.get_document()->write_to_file_formatted(path_to_xml_file.data());
}

} // namespace mzlib

#endif // MZLIB_EXTENSION_LIBXMLPP_DATASHELF_H
