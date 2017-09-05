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

// basic optional type if you can't use C++17 yet
// doesn't store references
template<class T>
class [[deprecated]] optional
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

#endif	// MZLIB_OPTIONAL_H

#ifdef MZLIB_BUILDING_TESTS

#ifndef MZLIB_OPTIONAL_TESTS_H
#define MZLIB_OPTIONAL_TESTS_H

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
TEST(optional, throws_when_not_set) 
{
   mzlib::optional<int> optional;
   ASSERT_THROW(optional.get(), mzlib::exception::not_set);
}

TEST(optional, throws_not_when_set) 
{
   mzlib::optional<int> optional = 5;
   ASSERT_NO_THROW(optional.get());
}

TEST(optional, reports_when_not_set) 
{
   mzlib::optional<int> optional;
   ASSERT_FALSE(optional.is_set());
}

TEST(optional, reports_when_set) 
{
   mzlib::optional<int> optional = 5;
   ASSERT_TRUE(optional.is_set());
}

TEST(optional, gets_value_when_set) 
{
   mzlib::optional<int> optional = 5;
   ASSERT_EQ(5, optional.get());
}

TEST(optional, can_unset) 
{
   mzlib::optional<int> optional = 5;
   optional.unset();
   ASSERT_FALSE(optional.is_set());
}
#pragma GCC diagnostic warning "-Wdeprecated-declarations"

#endif // MZLIB_OPTIONAL_TESTS_H

#endif // MZLIB_BUILDING_TESTS