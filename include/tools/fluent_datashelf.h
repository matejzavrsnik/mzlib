//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_FLUENT_DATASHELF_H
#define MZLIB_FLUENT_DATASHELF_H

#include "datashelf.h"
#include "internal/fluent_datashelf_state_attribute.h"
#include "internal/fluent_datashelf_state_filter_one.h"

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
      
   fluent& set_name(std::string_view name)
   {
      current_node()->set_name(name);
      return *this;
   }
   
   fluent& set_value(std::string_view value)
   {
      current_node()->set_value(value);
      return *this;
   }
   
   std::string_view value()
   {
      return current_node()->value();
   }
   
   std::string_view name()
   {
      return current_node()->name();
   }
   
   fluent& add_attribute
      (std::string_view name, std::string_view value = "")
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
   
   fluent& add_node(std::string_view name = "", std::string_view value = "")
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
   
   fluent_state_filter_one& first(std::string_view name)
   {
      m_state_filter_one = std::make_unique<fluent_state_filter_one>(
         ::mzlib::ds::first(
            current_node()->nodes(), 
            name));
      return *m_state_filter_one.get();
   }
   
   fluent_state_filter_one& random (
      std::string_view name,
      decltype(get_random_element<typename node::iterator>) rnd = 
         get_random_element<typename node::iterator>)
   {
      std::shared_ptr<node> random_node = 
         ::mzlib::ds::random(
            current_node()->nodes(), 
            name, 
            rnd);
      m_state_filter_one = std::make_unique<fluent_state_filter_one>(random_node);
      return *m_state_filter_one.get();
   }
   
   attribute& get_attribute(std::string_view name)
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
   
   friend class fluent_state_attribute;
};


        
} // namespace ds

} // namespace mzlib

#endif // MZLIB_DATASHELF_H
