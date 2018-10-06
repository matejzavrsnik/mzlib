//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_TALLY_H
#define MZLIB_TALLY_H

namespace mzlib {
    
// Useful for when you need a name for counter for some Thing
   
template<typename Thing, typename SizeT = unsigned> 
class tally
{
   
private:
   
   const Thing m_itself;
   SizeT m_count;
   
public:
   
   tally(const Thing& thing, SizeT count = 0) :
      m_itself(thing),
      m_count(count)
   {}
      
   const Thing& itself() const
   {
      return m_itself;
   }
   
   SizeT count() const
   {
      return m_count;
   }
   
};

} // namespace

#endif // MZLIB_TALLY_H
