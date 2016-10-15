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
class cunique
{
   
private:
   
   int m_id;
   
   static int get_unique_int()
   {
      static int m_unique_int = 0;
      return ++m_unique_int;
   }
   
public:
   
   cunique()
   {
      m_id = get_unique_int();
   }
   
   cunique(const cunique&) = default;
   cunique(cunique && ) = default;
   cunique& operator=(const cunique&) = default;
   cunique& operator=(cunique&&) = default;
   ~cunique() = default;   
   
   int id() const
   {
      return m_id;
   }
};

} // namespace

#endif	/* MZLIB_UNIQUE_H */

