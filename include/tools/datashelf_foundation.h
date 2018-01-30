/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   datashelf_foundation.h
 * Author: matej
 *
 * Created on January 28, 2018, 10:33 AM
 */

#ifndef DATASHELF_FOUNDATION_H
#define DATASHELF_FOUNDATION_H

#include <vector>


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

   static const std::shared_ptr<node> empty()
   {
      static std::shared_ptr<node> empty = std::make_shared<node>();
      return empty;
   }
   
   node(
      std::string name = "", 
      std::string value = "", 
      std::shared_ptr<node> parent = nullptr) :
         base(name, value), 
         m_parent(parent)
   {
   }
   
   // attributes
   
   //std::vector<std::shared_ptr<attribute>>::iterator begin_attributes ()
   //{
   //   return m_attributes.begin();
   //}
   
   //std::vector<std::shared_ptr<attribute>>::iterator end_attributes ()
   //{
   //   return m_attributes.end();
   //}
   
   std::vector<std::shared_ptr<attribute>> attributes ()
   {
      std::vector<std::shared_ptr<attribute>> all(
         m_attributes.begin(), 
         m_attributes.end());
      return all;
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
   
   std::shared_ptr<node> parent ()
   {
      return m_parent;
   }
   
   std::vector<std::shared_ptr<node>> nodes ()
   {
      std::vector<std::shared_ptr<node>> all(
         m_nodes.begin(), 
         m_nodes.end());
      return all;
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
      
      if (filtered_nodes.size() == 0)
         return empty();
              
      return *rnd(filtered_nodes.begin(), filtered_nodes.end());
   }

  
   friend class fluent;
   friend class fluent_state_filter_one;
   
};

inline std::vector<std::shared_ptr<node>> get_peers(
   std::shared_ptr<node> this_node)
{
   std::vector<std::shared_ptr<node>> no_peers;
   if (this_node == nullptr) return no_peers;
   auto parent = this_node->parent();
   if (parent == nullptr) return no_peers;
   return parent->nodes();
}

inline std::vector<std::shared_ptr<node>> filter_by_name(
   std::vector<std::shared_ptr<node>> all_nodes, 
   std::string name)
{
   std::vector<std::shared_ptr<node>> filtered_by_name;
   std::copy_if (
      all_nodes.begin(), all_nodes.end(), 
      std::back_inserter(filtered_by_name), 
      [&](const std::shared_ptr<node> n){
         return n->get_name() == name;
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

} // namespace ds

} // namespace mzlib

#endif /* DATASHELF_FOUNDATION_H */

