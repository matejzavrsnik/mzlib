//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_STRING_CASE_H
#define MZLIB_STRING_CASE_H

#include <algorithm>
#include <string>
#include <cwctype>

namespace mzlib {

// Overloads for std converters to lower and upper case chars.
// Standard converters have different names for narrow and for
// wide chars and they can't be used in templated context. These
// functions are implemented just for that purpose.
   
inline std::string::value_type tolower(
   std::string::value_type ch) 
{
   return std::tolower(ch);
}

inline std::wstring::value_type tolower(
   std::wstring::value_type ch)
{
   return std::towlower(ch);
}

inline std::string::value_type toupper(
   std::string::value_type ch) 
{
   return std::toupper(ch);
}

inline std::wstring::value_type toupper(
   std::wstring::value_type ch)
{
   return std::towupper(ch);
}

// And now the functionality

template<class String>
void to_lowercase_inplace(String& str)
{
   std::transform(str.begin(), str.end(), str.begin(), 
      [](typename String::value_type c) { 
         return tolower(c); 
      });
}

template<class String>
void to_uppercase_inplace(String& str)
{
   std::transform(str.begin(), str.end(), str.begin(), 
      [](typename String::value_type c) { 
         return toupper(c); 
      });
}

template<class String>
String to_lowercase_copy(const String& str)
{
   String str_copy = str; // explicitely make copy
   to_lowercase_inplace(str_copy);
   return str_copy; // rely on RVO
}

template<class String>
String to_uppercase_copy(const String& str)
{
   String str_copy = str; // explicitely make copy
   to_uppercase_inplace(str_copy);
   return str_copy; // rely on RVO
}

} // namespace

#endif // HEADER_H
