//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_STARTS_WITH_H
#define MZLIB_STARTS_WITH_H

#include <iterator>

namespace mzlib {

// To see if a collection starts with other collection or not. First meant to
// be used for strings, but why not make it for all iterable collections. Even
// for strings this is more useful then .find and check if it returned 0, because
// if it does not start with, it can stop searching immediately as opposed to
// .find which would search to the end of the string. For general collections 
// find_first_of could be used, but would suffer the same performance penalty.
// With C++20 we'll get .starts_with for strings, but not for generic containers.
// Also, it's just couple of beautifully overly-concise lines of code with the
// ratio of reserved keywords to everything else close to 1-2 :)
template<class Iterator1, class Iterator2>
bool starts_with(
   Iterator1 full_it, Iterator1 full_end_it, 
   Iterator2 sub_it,  Iterator2 sub_end_it)
{
   if (sub_it == sub_end_it) return true;
   if (full_it == full_end_it) return false;
   do if (*full_it != *sub_it) return false;
   while (++full_it, ++sub_it, full_it != full_end_it && sub_it != sub_end_it);
   if (full_it == full_end_it && sub_it != sub_end_it) return false;
   return true;
}

// Overloads for convenience

template<class Collection1, class Collection2>
bool starts_with(
   Collection1&& full, 
   Collection2&& sub)
{
   return starts_with(
      std::cbegin(full), std::cend(full),
      std::cbegin(sub), std::cend(sub));
}

template<class Collection1, class Collection2>
bool ends_with(
   Collection1&& full, 
   Collection2&& sub)
{
   return starts_with(
      std::crbegin(full), std::crend(full),
      std::crbegin(sub), std::crend(sub));
}

} // namespace

#endif // MZLIB_STARTS_WITH_H
