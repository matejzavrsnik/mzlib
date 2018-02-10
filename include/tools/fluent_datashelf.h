//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_FLUENT_DATASHELF_H
#define MZLIB_FLUENT_DATASHELF_H

#include "datashelf_foundation.h"

#include <algorithm>
#include <stack>

namespace mzlib {
namespace ds {

// "Certainly chaining is a common technique to use with fluent interfaces, 
// but true fluency is much more than that." (Martin Fowler)
//
// Here I am making it into a state machine, because it makes sense. When in state
// "working on attribute" function add_node makes no sense, because attributes
// can't have nested nodes, while add_node makes perfect sense in "working on
// nodes" state, because you can always add subnodes. This is simple example,
// more complicated are functions that change meaning with state. In "attribute"
// state get() should mean get me the attribute, whilst in "node" state it means
// get me the node. How would you otherwise overload for function return type?
// That, my friends, is impossible. Or when I start adding queries ... for example,
// when I have filtered all subnodes with certain name, what does add_node mean
// then? With state machine, all states can be programmed separately and I can
// get errors in compile time; for example, I can simply not implement add_node
// in a "filtered a collection of nodes" state. It all makes perfect sense at the
// moment, let's see the idea mature first before I brag too much :)
//
// Didn't expect fluent interface part of the project to be so interesting.

class fluent_state_attribute;
class fluent_state_filter_one;
   
class fluent
{

private:
   
   // all the nodes that are actively used
   std::stack<std::shared_ptr<node>> m_using_nodes;
   std::shared_ptr<node> m_last_added_node;
   std::shared_ptr<attribute> m_last_added_attribute;
   
   // temporary storage for the next states
   std::unique_ptr<fluent_state_attribute> m_attribute_state;
   std::unique_ptr<fluent_state_filter_one> m_state_filter_one;
   
   std::shared_ptr<node> current_node()
   {
      if (m_using_nodes.size() == 0)
         return node::empty();
      
      return m_using_nodes.top();
   }
   
public:
   
   explicit fluent(std::shared_ptr<node> shelf)
   {
      m_using_nodes.push(shelf);
   }
      
   fluent& set_name(std::string name)
   {
      current_node()->set_name(name);
      return *this;
   }
   
   fluent& set_value(std::string value)
   {
      current_node()->set_value(value);
      return *this;
   }
   
   std::string value()
   {
      return current_node()->value();
   }
   
   std::string name()
   {
      return current_node()->name();
   }
   
   fluent& add_attribute
      (std::string name, std::string value = "")
   {
      m_last_added_attribute = current_node()->add_attribute(name, value);
      return *this;
   }
   
   fluent_state_attribute& use_attribute()
   {
      m_attribute_state = std::make_unique<fluent_state_attribute>(
         *this,
         m_last_added_attribute);
      return *m_attribute_state.get();
   }
   
   fluent& add_node(std::string name = "", std::string value = "")
   {
      m_last_added_node = current_node()->add_node(name, value);
      return *this;
   }
   
   fluent& use()
   {
      if (m_last_added_node != nullptr) {
         m_using_nodes.push(m_last_added_node);
      }
      return *this;
   }
   
   fluent& stop_using()
   {
      if(m_using_nodes.size()>1) {
         m_using_nodes.pop();
      }
      return *this;
   }
   
   // queries
   
   std::shared_ptr<node> get()
   {
      return current_node();
   }
   
   fluent_state_filter_one& first(std::string name)
   {
      m_state_filter_one = std::make_unique<fluent_state_filter_one>(
         ::mzlib::ds::first(
            current_node()->nodes(), 
            name));
      return *m_state_filter_one.get();
   }
   
   fluent_state_filter_one& random (
      std::string name,
      decltype(get_random_element<typename node::iterator>) rnd = 
         get_random_element<typename node::iterator>)
   {
      m_state_filter_one = std::make_unique<fluent_state_filter_one>(
         ::mzlib::ds::random(
            current_node()->nodes(), 
            name, 
            rnd));
      return *m_state_filter_one.get();
   }
   
   attribute& get_attribute(std::string name)
   {
      std::shared_ptr<attribute> att = ::mzlib::ds::get_attribute(
         current_node(),
         name);
      return *att;
   }
   
   bool is_empty()
   {
      return current_node()->is_empty();
   }
   
   friend class fluent_state_attribute_added;
   friend class fluent_state_attribute;
};

class fluent_state_filter_one
{
private:
   
   std::shared_ptr<fluent> m_state_node;
   std::shared_ptr<node> m_filtered_one;
   
public:
   
   explicit fluent_state_filter_one(std::shared_ptr<node> origin) :
      m_filtered_one(origin)
   {
   }
   
   std::shared_ptr<node> get()
   {
      return m_filtered_one;
   }
      
   fluent_state_filter_one& first(std::string name)
   {
      m_filtered_one = ::mzlib::ds::first(
         m_filtered_one->nodes(), 
         name);
      return *this;
   }
   
   fluent_state_filter_one& random (
      std::string name,
      decltype(get_random_element<typename node::iterator>) rnd = 
         get_random_element<typename node::iterator>)
   {
      m_filtered_one = ::mzlib::ds::random(
         m_filtered_one->nodes(), 
         name, 
         rnd);
      return *this;
   }
   
   fluent_state_filter_one& next(std::string name)
   {
      m_filtered_one = ::mzlib::ds::next(
         m_filtered_one,
         name);
      return *this;
   }
   
   attribute& get_attribute(std::string name)
   {
      auto att = ::mzlib::ds::get_attribute(
         m_filtered_one,
         name);
      return *att;
   }
   
   std::string value()
   {
      return m_filtered_one->value();
   }
   
   std::string name()
   {
      return m_filtered_one->name();
   }
   
   fluent& use()
   {
      m_state_node = std::make_shared<fluent>(m_filtered_one);
      return *m_state_node.get();
   }
   
   fluent_state_filter_one& add_attribute
      (std::string name, std::string value = "")
   {
      m_filtered_one->add_attribute(name, value);
      return *this;
   }
   
   fluent_state_filter_one& add_node(std::string name = "", std::string value = "")
   {
      m_filtered_one->add_node(name, value);
      return *this;
   }
   
   bool is_empty()
   {
      return m_filtered_one->is_empty();
   }
   
   operator mzlib::ds::node& ()
   {
      return *m_filtered_one;
   }
   
   operator std::shared_ptr<mzlib::ds::node> ()
   {
      return m_filtered_one;
   }
};
        
class fluent_state_attribute
{
private:
   
   // origin state for going back
   fluent& m_state_node;
   std::shared_ptr<attribute> m_attribute;
   
public:

   fluent_state_attribute(
      fluent& origin,
      std::shared_ptr<attribute> the_attribute) :
         m_state_node(origin),
         m_attribute(the_attribute)
   {
   }

   
   fluent_state_attribute& set_name(std::string name)
   {
      m_attribute->set_name(name);
      return *this;
   }
   
   fluent_state_attribute& set_value(std::string value)
   {
      m_attribute->set_value(value);
      return *this;
   }

   attribute& get()
   {
      return *m_attribute;
   }
   
   fluent& stop_using()
   {
      return m_state_node;
   }
   
};


} // namespace ds

} // namespace mzlib

#endif // MZLIB_DATASHELF_H
