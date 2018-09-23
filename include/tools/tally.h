//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_TALLY_H
#define MZLIB_TALLY_H

#include <map>

namespace mzlib {
    
// Useful for when you need a name for counter for some Thing

template<typename Thing> 
class tally
{
   
private:
   
   const Thing& m_itself;
   size_t m_count;
   
public:
   
   tally(const Thing& thing, size_t count = 0) :
      m_itself(thing),
      m_count(count)
   {}
      
   const Thing& itself()
   {
      return m_itself;
   }
   
   size_t count()
   {
      m_count;
   }
   
};

} // namespace

#endif // MZLIB_TALLY_H
