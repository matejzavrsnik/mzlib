//
// Copyright (c) 2019 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_STRING_VIEW_FIND_H
#define MZLIB_STRING_VIEW_FIND_H

#include "../lang/binary_options.h"

namespace mzlib {
   
// - Standard algorithm search can compare to functor, but return iterators.
// - std::string_view search can compare to 1..* chars, but not to functor.
// - std::string_view substring functions all take positions and lengths, 
//   not iterators.
// - To calculate positions and lengths from iterators I'd need to use 
//   std::distance.
// - Using std::distance and std::find would iterate string twice when it's
//   only necessary to iterate once.
   
// Unless I am missing something, I can't for example efficiently search for 
// std::isalpha in std::string_view, so I am writing my own algos.


// foundation: all options open
template<typename StringView, typename CharGroupIdentifier>
typename StringView::size_type find_first_of(
   StringView str,
   CharGroupIdentifier in_group,
   typename StringView::size_type pos,
   option::forward forward,
   option::match match)
{
   if (str.empty())
      return str.npos;
   
   typename StringView::size_type end_pos, next;
   
   end_pos = (forward ? str.size()-1 : 0);
   next = (forward ? 1 : -1);
   
   for (; ; pos += next) 
   {
      bool in = in_group(str[pos]);
      
      if (in == match)
         return pos;
      if (pos == end_pos)
         return str.npos;
   }
   return str.npos;
}

// overload: minimal forward yes_of
template<typename StringView, typename CharGroupIdentifier>
typename StringView::size_type find_first_of(
   StringView str,
   CharGroupIdentifier in_group)
{
   return find_first_of(
      str, in_group, 0, 
      option::forward::yes, 
      option::match::yes);
}

// overload: forward yes_of with selected start position
template<typename StringView, typename CharGroupIdentifier>
typename StringView::size_type find_first_of(
   StringView str,
   CharGroupIdentifier in_group,
   typename StringView::size_type pos)
{
   return find_first_of(
      str, in_group, pos, 
      option::forward::yes, 
      option::match::yes);
}

// overload: minimal reverse yes_of
template<typename StringView, typename CharGroupIdentifier>
typename StringView::size_type rfind_first_of(
   StringView str,
   CharGroupIdentifier in_group)
{
   return find_first_of(
      str, in_group, str.size()-1, 
      option::forward::no, 
      option::match::yes);
}

// overload: reverse yes_of with selected start position
template<typename StringView, typename CharGroupIdentifier>
typename StringView::size_type rfind_first_of(
   StringView str,
   CharGroupIdentifier in_group,
   typename StringView::size_type pos)
{
   return find_first_of(
      str, in_group, pos, 
      option::forward::no, 
      option::match::yes);
}

// overload: minimal forward not_of
template<typename StringView, typename CharGroupIdentifier>
typename StringView::size_type find_first_not_of(
   StringView str,
   CharGroupIdentifier in_group)
{
   return find_first_of(
      str, in_group, 0, 
      option::forward::yes, 
      option::match::no);
}

// overload: forward not_of with selected start position
template<typename StringView, typename CharGroupIdentifier>
typename StringView::size_type find_first_not_of(
   StringView str,
   CharGroupIdentifier in_group,
   typename StringView::size_type pos)
{
   return find_first_of(
      str, in_group, pos, 
      option::forward::yes, 
      option::match::no);
}

// overload: minimal reverse not_of
template<typename StringView, typename CharGroupIdentifier>
typename StringView::size_type rfind_first_not_of(
   StringView str,
   CharGroupIdentifier in_group)
{
   return find_first_of(
      str, in_group, str.size()-1, 
      option::forward::no, 
      option::match::no);
}

// overload: reverse not_of with selected start position
template<typename StringView, typename CharGroupIdentifier>
typename StringView::size_type rfind_first_not_of(
   StringView str,
   CharGroupIdentifier in_group,
   typename StringView::size_type pos)
{
   return find_first_of(
      str, in_group, pos, 
      option::forward::no, 
      option::match::no);
}

} // namespace

#endif // MZLIB_STRING_VIEW_FIND_H
