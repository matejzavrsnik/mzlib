//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_OPTIONAL_H
#define	MZLIB_OPTIONAL_H

#include "exceptions.h"
#include "binary_options.h"

namespace mzlib {

// basic optional type 
// doesn't really store references, waiting for C++17 or whenever, but good enough for now
template<class T>
class optional
{
   
private:
   
   T m_value;
   option::set m_set;
   
public:
   
   optional ()
   {
      m_set = option::set::no;
   }
   
   optional (const T& value)
   {
      m_value = value;
      m_set = option::set::yes; 
   }
   
   bool is_set() const
   {
      return m_set == option::set::yes;
   }

   // I was thinking of the name "reset", but that would clash with boost and std
   // constructs where "reset" also sets the object to a new value; this doesn't.
   void unset()
   {
      m_set = option::set::no;
   }
   
   // This function is needed because otherwise every operator would need to have 
   // optional overload on top of every other just to have means to force 
   // optional to cast to basic type. I had at first casting operator implemented 
   // but it only seamlessly worked when assigned directly to underlying type. 
   // That makes sense, because how else should compiler know what to convert 
   // optional to in case when, for instance, writing f = m * a, where m is 
   // optional and appropriate operator* doesn't exist.
   const T& get () const
   {
      if(m_set == option::set::no) throw exception::not_set();
      return m_value; 
   }
   
};

} // namespace

#endif	/* MZLIB_OPTIONAL_H */

#ifdef MZLIB_BUILDING_TESTS

TEST(optional, basic) 
{
   mzlib::optional<int> optional;
   ASSERT_THROW(optional.get(), mzlib::exception::not_set);
   ASSERT_FALSE(optional.is_set());
   optional = 5;
   ASSERT_NO_THROW(optional.get());
   ASSERT_EQ(5, optional.get());
   ASSERT_TRUE(optional.is_set()); 
   optional.unset();
   ASSERT_THROW(optional.get(), mzlib::exception::not_set);
}

#endif // MZLIB_BUILDING_TESTS