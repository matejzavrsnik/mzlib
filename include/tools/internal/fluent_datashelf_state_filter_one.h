//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_INTERNAL_FLUENT_DATASHELF_STATE_FILTER_ONE_H
#define MZLIB_INTERNAL_FLUENT_DATASHELF_STATE_FILTER_ONE_H

#include "../datashelf.h"

namespace mzlib {
   
namespace ds { 
   
class fluent;
   
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
      m_filtered_one = ::mzlib::ds::next(m_filtered_one);
      return *this;
   }
   
   attribute& get_attribute(std::string name)
   {
      auto att = ::mzlib::ds::get_attribute(
         m_filtered_one,
         name);
      return *att;
   }
   
   std::string_view value()
   {
      return m_filtered_one->value();
   }
   
   std::string_view name()
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

} // namespace ds

} // namespace mzlib

#endif // MZLIB_INTERNAL_FLUENT_DATASHELF_STATE_FILTER_ONE_H
