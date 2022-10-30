//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_STRING_JOIN_H
#define MZLIB_STRING_JOIN_H

#include <string>
#include <string_view>

namespace mzlib {
   
// because boost::join can't work with string_view

template<typename ResultString, typename Collection, typename DelimiterString>
ResultString basic_join (Collection strs, DelimiterString del)
{
   ResultString joined;
   bool first = true;
   for(auto& str : strs)
   {
      if(!first) joined += del;
      joined += str;
      first = false;
   }
   return joined;
}

// Would be nice if I could just say something like:
// template<,,> using join  = basic_join<,,std::string>;
// template<,,> using wjoin = basic_join<,,std::wstring>;

// but I can't do that with functions, just with types, 
// so I need to resort to some dirty macros:

#define MZLIB_ALIAS_BASIC_JOIN(name, result_type) \
template<typename Collection, typename DelimiterString> \
result_type name (Collection s, DelimiterString d) { \
   return basic_join< result_type >(s, d); \
}

MZLIB_ALIAS_BASIC_JOIN( join,    std::string)
MZLIB_ALIAS_BASIC_JOIN( wjoin,   std::wstring)
// MZLIB_ALIAS_BASIC_JOIN( u8join,  std::u8string)  not available yet in my compiler
MZLIB_ALIAS_BASIC_JOIN( u16join, std::u16string)
MZLIB_ALIAS_BASIC_JOIN( u32join, std::u32string)

#undef MZLIB_ALIAS_BASIC_JOIN

} // namespace

#endif // MZLIB_STRING_JOIN_H
