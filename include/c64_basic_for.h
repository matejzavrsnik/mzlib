//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_C64_BASIC_FOR_H
#define	MZLIB_C64_BASIC_FOR_H

#include "optional.h"
#include "utils_missing_std.h" // std::make_unique
#include "exceptions.h"

#include <memory> // std::unique_ptr

namespace mzlib {

// A builder to be able to write for loops like I did in my old commodore basic.
// Serves no meaningful purpose but a regression into childhood :)
template<class T>
class c64_basic_for
{
   
private:
   
   optional<T> m_from;
   optional<T> m_to;
   optional<T> m_step;
   
public:
   
   static std::unique_ptr<c64_basic_for> loop () 
   {
      return std::make_unique<c64_basic_for>();
   }
   
   c64_basic_for* from (T f) 
   { 
      m_from = f;
      return this; 
   }
   
   c64_basic_for* to (T t)
   {
      m_to = t;
      return this;
   }
   
   std::vector<T> step (T s)
   {
      std::vector<T> result;
      try {
         m_step = s;
         for (auto val = m_from.get(); val < m_to.get(); val += m_step.get()) {
            result.push_back(val);
         }
      }
      catch (exception::not_set& e) {
         // ah, well. c'est la vie ...
         // let it return empty vector
      }
      return result;
   }
};

} // namespace

#endif	/* MZLIB_C64_BASIC_FOR_H */

