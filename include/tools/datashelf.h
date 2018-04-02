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

#include <vector>
#include <memory> // for smart ptrs
#include <algorithm>

// The point of this whole thing is to have an in-memory data shelf
// for basic data needs, like settings or a collection of books or
// whatever. Such that is most conveniently stored in xml, but then
// needs further editing once in memory. Like changing settings, adding
// reviews to books and such, and then after that you want it to be
// easy to persist that back on the xml file, either during the process
// or in the end.

namespace mzlib {
namespace ds {
   
class base
{

private:
   
   std::string m_name;
   std::string m_value;
   
public:
   
   base(std::string_view name = "", std::string_view value = "") :
      m_name(name),
      m_value(value)
   {
   }
   
   std::string_view name() const
   {
      return m_name;
   }
   
   std::string_view value() const
   {
      return m_value;
   }

   void set_name(std::string_view name)
   {
      m_name = name;
   }
   
   void set_value(std::string_view value)
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

   bool is_empty() const
   {
      return (has_empty_name() && has_empty_value());
   }

};

// a new name just to avoid confusion
class attribute : public base
{
   
public:
   
   static const std::shared_ptr<attribute> empty()
   {
      return std::make_shared<attribute>();
   }
   
   using base::base;
};

class node : public base, public std::enable_shared_from_this<node>
{
private:

   std::shared_ptr<node> m_parent;
   std::vector<std::shared_ptr<attribute>> m_attributes;
   std::vector<std::shared_ptr<node>> m_nodes;
   
public:   
   
   using iterator = std::vector<std::shared_ptr<node>>::iterator;

   static const std::shared_ptr<node> empty()
   {
      return std::make_shared<node>();
   }
   
   node(
      std::string_view name = "", 
      std::string_view value = "", 
      std::shared_ptr<node> parent = nullptr) :
         base(name, value), 
         m_parent(parent)
   {
   }
   
   // In a way this const is a bit misleading. It is true that the
   // caller can't change anything in this object, ie this node, but
   // through the returned values they can change child nodes. On some
   // level a node is defined by child nodes too, so in turn this did
   // change it.
   const std::vector<std::shared_ptr<node>>& nodes () const
   {
      return m_nodes;
   }
   
   const std::vector<std::shared_ptr<attribute>>& attributes () const
   {
      return m_attributes;
   }
   
   std::shared_ptr<node> parent ()
   {
      return m_parent;
   }

   std::shared_ptr<node> add_node(std::string_view name = "", std::string_view value = "")
   {
      auto new_node = std::make_shared<node>(
         name, 
         value, 
         shared_from_this());
      m_nodes.push_back(new_node);
      return new_node;
   }
   
   std::shared_ptr<attribute> add_attribute(std::string_view name, std::string_view value)
   {
      auto new_attribute = std::make_shared<attribute>(name, value);
      m_attributes.push_back(new_attribute);
      return new_attribute;
   }

};

inline std::vector<std::shared_ptr<node>> get_peers(
   std::shared_ptr<node> the_node)
{
   std::vector<std::shared_ptr<node>> no_peers;
   if (the_node == nullptr) return no_peers;
   auto parent = the_node->parent();
   if (parent == nullptr) return no_peers;
   return parent->nodes();
}

inline std::vector<std::shared_ptr<node>> filter_by_name(
   std::vector<std::shared_ptr<node>> all, 
   std::string_view name)
{
   std::vector<std::shared_ptr<node>> filtered_by_name;
   std::copy_if (
      all.begin(), all.end(), 
      std::back_inserter(filtered_by_name), 
      [&](const std::shared_ptr<node> n){
         return n->name() == name;
      });
   return filtered_by_name;
}

inline std::shared_ptr<node> find_next_of(
   std::vector<std::shared_ptr<node>> all_nodes, 
   std::shared_ptr<node> this_node)
{
   
   auto this_node_it = std::find_if(
      all_nodes.begin(), all_nodes.end(),
      [&](std::shared_ptr<node> n) {
         return n == this_node;
      });

   if (this_node_it == all_nodes.end()) {
      return node::empty();
   }
   auto next_node_it = ++this_node_it;
   if (next_node_it == all_nodes.end()) { 
      return node::empty();
   }
   
   return *next_node_it;
}

inline std::shared_ptr<node> first(
   std::vector<std::shared_ptr<node>> all_nodes, 
   std::string_view name)
{
   for(auto n : all_nodes) {
      if(n->name() == name) {
         return n;
      }
   }
   return node::empty();
}

inline std::shared_ptr<node> first_with_attribute(
   std::vector<std::shared_ptr<node>> all_nodes, 
   std::string_view node_name,
   std::string_view attr_name,
   std::string_view attr_value)
{
   for(auto n : all_nodes) {
      if(n->name() == node_name) {
         for(auto a : n->attributes()) {
            if(a->name() == attr_name && a->value() == attr_value) {
               return n;
            }
         }
      }
   }
   return node::empty();
}

inline std::shared_ptr<node> random (
   std::vector<std::shared_ptr<node>> all_nodes,
   std::string_view name,
   decltype(get_random_element<typename node::iterator>) rnd = 
      get_random_element<typename node::iterator>)
{
   auto namesakes = filter_by_name(all_nodes, name);

   if (namesakes.size() == 0)
      return node::empty();

   return *rnd(namesakes.begin(), namesakes.end());
}

inline std::shared_ptr<node> next (std::shared_ptr<node> the_node)
{
   auto all_peers = get_peers(the_node);
   auto namesakes = filter_by_name(all_peers, the_node->name());
   return find_next_of(namesakes, the_node);
}

inline std::shared_ptr<attribute> get_attribute (
   std::shared_ptr<node> the_node,
   std::string_view name)
{
   auto all_attributes = the_node->attributes();
   
   auto attribute_it = std::find_if(
      all_attributes.begin(), 
      all_attributes.end(),
      [&name] (const std::shared_ptr<attribute> a) {
         return a->name() == name;
      });
      
   if (attribute_it != all_attributes.end())
      return *attribute_it;
      
   return attribute::empty();
}

inline std::shared_ptr<attribute> add_or_edit_attribute(
   std::shared_ptr<node> the_node,
   std::string_view attribute_name, 
   std::string_view attribute_value)
{
   auto att = get_attribute(the_node, attribute_name);
   if (att->is_empty())
      att = the_node->add_attribute(attribute_name, "");
   att->set_value(attribute_value);
   return att;
}

} // namespace ds
} // namespace mzlib

#endif // MZLIB_DATASHELF_FOUNDATION_H

