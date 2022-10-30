//
// Copyright (c) 2019 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_OPTIONAL_STRING_H
#define MZLIB_OPTIONAL_STRING_H

#include <optional>
#include <string>

namespace mzlib {

// A collection of questionable utilities that (ab)use user-defined
// string literals to become conversions to optionals.
   
// "string"
inline
std::optional<std::string> operator "" _ostr(const char* str, size_t)
{ 
   return std::make_optional<std::string>(str); 
}

// "string"
inline
std::optional<std::string_view> operator "" _ostrv(const char* str, size_t)
{ 
   return std::make_optional<std::string_view>(str); 
}

// L"string"
inline
std::optional<std::wstring> operator "" _ostr(const wchar_t* str, size_t)
{ 
   return std::make_optional<std::wstring>(str); 
}

// L"string"
inline
std::optional<std::wstring_view> operator "" _ostrv(const wchar_t* str, size_t)
{ 
   return std::make_optional<std::wstring_view>(str); 
}


// to uncomment when I upgrade g++ to v9

//// u8"string"
//inline
//std::optional<std::u8string> operator "" _ostr(const char8_t* str, size_t)
//{ 
//   return std::make_optional<std::u8string>(str); 
//}
//
//// u8"string"
//inline
//std::optional<std::u8string_view> operator "" _ostrv(const char8_t* str, size_t)
//{ 
//   return std::make_optional<std::u8string_view>(str); 
//}

// u"string"
inline
std::optional<std::u16string> operator "" _ostr(const char16_t* str, size_t)
{ 
   return std::make_optional<std::u16string>(str); 
}

// u"string"
inline
std::optional<std::u16string_view> operator "" _ostrv(const char16_t* str, size_t)
{ 
   return std::make_optional<std::u16string_view>(str); 
}

// U"string"
inline
std::optional<std::u32string> operator "" _ostr(const char32_t* str, size_t)
{ 
   return std::make_optional<std::u32string>(str); 
}

// U"string"
inline
std::optional<std::u32string_view> operator "" _ostrv(const char32_t* str, size_t)
{ 
   return std::make_optional<std::u32string_view>(str); 
}

} // namespace

#endif // MZLIB_OPTIONAL_STRING_H
