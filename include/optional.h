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
   eset m_set;
   
public:
   
   coptional ()
   {
      m_set = eset::no;
   }
   
   coptional (const T& value)
   {
      m_value = value;
      m_set = eset::yes; 
   }
   
   bool is_set()
   {
      return m_set == eset::yes;
   }
   
   // A way to "decay" into underlying value type without much additional fuss,
   // although perhaps not the most intuitive. Should be nice to read though.
   // The "decay" is needed because otherwise every operator would need to have 
   // coptional overload on top of every other just to have means to force 
   // coptional to cast to basic type. I had at first casting operator implemented 
   // but it only seamlessly worked when assigned directly to underlying type. 
   // That makes sense, because how else should compiler know what to convert 
   // coptional to in case when, for instance, writing f = m * a, where m is 
   // coptional and appropriate operator* doesn't exist.
   const T& operator() ()
   {
      if(m_set == eset::no) throw exception::not_set();
      return m_value; 
   }
   
};

} } // namespace mzlib::util

#endif	/* MZLIB_OPTIONAL_H */

