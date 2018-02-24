//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_INTERNAL_FLUENT_DATASHELF_STATE_ATTRIBUTE_H
#define MZLIB_INTERNAL_FLUENT_DATASHELF_STATE_ATTRIBUTE_H

#include "../datashelf.h"

namespace mzlib {
   
namespace ds { 
   
class fluent;
   
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
   
   fluent_state_attribute& set_name(std::string_view name)
   {
      m_attribute->set_name(name);
      return *this;
   }
   
   fluent_state_attribute& set_value(std::string_view value)
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

} // namespace internal

} // namespace ds

#endif // MZLIB_INTERNAL_FLUENT_DATASHELF_STATE_ATTRIBUTE_H
