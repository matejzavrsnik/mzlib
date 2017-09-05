//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_C64_BASIC_FOR_H
#define	MZLIB_C64_BASIC_FOR_H

#include <optional>

#include "exceptions.h"

#include <memory> // std::unique_ptr

namespace mzlib {

// A builder to be able to write for loops like I did in my old commodore basic.
// Serves no meaningful purpose but a regression into childhood :)
template<class T>
class c64_basic_for
{
   
private:
   
   std::optional<T> m_from;
   std::optional<T> m_to;
   std::optional<T> m_step;
   
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
         for (auto val = m_from.value(); val < m_to.value(); val += m_step.value()) {
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

#ifdef MZLIB_BUILDING_TESTS

#ifndef MZLIB_C64_BASIC_FOR_TESTS_H
#define MZLIB_C64_BASIC_FOR_TESTS_H

TEST(c64_basic_for, demo) 
{
   int should_be = 0;
   int use_step = 10;
   using c64_for = mzlib::c64_basic_for<int>;
   for(int is : c64_for::loop()->from(0)->to(1000)->step(use_step))
   {
      ASSERT_EQ(should_be, is);
      should_be += use_step;
   }
}

#endif // MZLIB_C64_BASIC_FOR_TESTS_H

#endif // MZLIB_BUILDING_TESTS
