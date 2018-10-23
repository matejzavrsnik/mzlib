//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_REMEMBERATOR_H
#define MZLIB_REMEMBERATOR_H

#include <set>

namespace mzlib {

// remembers
template<typename T>
class rememberator
{
   
private:
   
   std::set<int> m_seen;
   std::hash<T> m_hasher;   
   
public:
   
   void remember(const T& thing)
   {
      m_seen.insert(m_hasher(thing));
   }
   
   bool can_recall(const T& thing)
   {
      return m_seen.find(m_hasher(thing)) != m_seen.end();
   }
   
   bool recall_remember(const T& thing)
   {
      bool recalled = can_recall(thing);
      if (!recalled) remember(thing);
      return recalled;
   }
};

} // namespace

#endif /* MZLIB_REMEMBERATOR_H */

