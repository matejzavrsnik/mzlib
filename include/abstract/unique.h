//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_UNIQUE_H
#define	MZLIB_UNIQUE_H

namespace mzlib {

// adds to objects a capability to be easily identifiable across copies of itself
class unique
{
   
private:
   
   int m_id;
   
   static int get_unique_int()
   {
      static int m_unique_int = 0;
      return ++m_unique_int;
   }
   
public:
   
   unique()
   {
      m_id = get_unique_int();
   }
   
   unique(const unique&) = default;
   unique(unique && ) = default;
   unique& operator=(const unique&) = default;
   unique& operator=(unique&&) = default;
   ~unique() = default;   
   
   int id() const
   {
      return m_id;
   }
   
   bool operator== (const unique& other) const
   {
      if (&other == this) {
         return true;
      }
      return (this->id() == other.id());
   }
   
   bool operator!= (const unique& other) const
   {
      return !(*this == other);
   }
   
   // To enable "native" use od mzlib::unique with std::map
   bool operator <(const unique& rhs) const
   {
      return id() < rhs.id();
   }
   
};

} // namespace

#endif	/* MZLIB_UNIQUE_H */

#ifdef MZLIB_BUILDING_TESTS

#ifndef MZLIB_UNIQUE_TESTS_H
#define MZLIB_UNIQUE_TESTS_H

TEST(unique, demo) 
{
   mzlib::unique a;
   mzlib::unique b;
   ASSERT_NE(a.id(), b.id()); 
}

TEST(unique, unique_on_copy) 
{
   mzlib::unique a;
   mzlib::unique b;
   mzlib::unique c(a);
   mzlib::unique d = a;
   ASSERT_NE(a.id(), b.id());
   ASSERT_EQ(a.id(), c.id());
   ASSERT_EQ(a.id(), d.id());
}

#endif // MZLIB_UNIQUE_TESTS_H

#endif // MZLIB_BUILDING_TESTS
