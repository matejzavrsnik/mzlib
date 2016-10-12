//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef C64_BASIC_FOR_H
#define	C64_BASIC_FOR_H

#include "optional.h"
#include "utils_missing_std.h" // std::make_unique
#include "exceptions.h"

#include <memory> // std::unique_ptr

namespace mzlib {
namespace util {

// A builder to be able to write for loops like I did in my old commodore basic.
// Serves no meaningful purpose but a regression into childhood :)
template<class T>
class c64_basic_for
{
   
private:
   
   mzlib::util::coptional_ref<T> m_from;
   mzlib::util::coptional_ref<T> m_to;
   mzlib::util::coptional_ref<T> m_step;
   
public:
   
   static std::unique_ptr<c64_basic_for> loop () 
   {
      return std::make_unique<c64_basic_for>();
   }
   
   c64_basic_for* from (T f) 
   { 
      m_from.set(f);
      return this; 
   }
   
   c64_basic_for* to (T t)
   {
      m_to.set(t);
      return this;
   }
   
   std::vector<T> step (T s)
   {
      std::vector<T> result;
      try {
         m_step.set(s);
         for (size_t val = m_from.get(); val < m_to.get(); val += m_step.get()) {
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

} } // namespace mzlib::util

#endif	/* C64_BASIC_FOR_H */

