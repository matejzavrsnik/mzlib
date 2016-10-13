//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_OPTIONAL_H
#define	MZLIB_OPTIONAL_H

#include "exceptions.h"
#include "enums.h"

namespace mzlib {
namespace util {

// basic optional type 
// doesn't really store references, waiting for C++17 or whenever, but good enough for now
template<class T>
class coptional
{
   
private:
   
   T m_value;
   eset m_set = eset::no;
   
public:
      
   const T& get() 
   {
      if(m_set == eset::no) throw exception::not_set();
      return m_value; 
   }
   
   void set(const T& value)
   {
      m_value = value;
      m_set = eset::yes;
   }
   
   bool is_set()
   {
      return m_set == eset::yes;
   }
   
};

} } // namespace mzlib::util

#endif	/* MZLIB_OPTIONAL_H */

