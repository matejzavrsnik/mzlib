//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_CONVERTERS_H
#define MZLIB_CONVERTERS_H

#include <string_view>

namespace mzlib {
    
// basic function template; meant to be specialised
template<class To, class From>
To convert(const From& value)
{
   return To(value);
}

// std::string_view <-> Glib::ustring (from libxml++)
#ifdef _GLIBMM_USTRING_H

template<>
inline std::string_view convert(
   const Glib::ustring& value)
{
   return value.c_str();
}

template<>
inline Glib::ustring convert(
   const std::string_view& value)
{
   return value.data();
}

#endif // _GLIBMM_USTRING_H

// 2-dimensional mzlib::vector <-> std::pair
#ifdef MZLIB_VECTOR_H

// todo: figure out how to do this specialization for all types, not just double
template<>
inline vector<double, 2> convert(
   const std::pair<double,double>& pair)
{
   return {pair.first, pair.second};
}

template<>
inline std::pair<double,double> convert(
   const vector<double, 2>& vec)
{
   return {vec[0], vec[1]};
}

#endif // MZLIB_VECTOR_H

} // namespace mzlib



#endif // MZLIB_CONVERTERS_H