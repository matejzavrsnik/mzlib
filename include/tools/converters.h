//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_CONVERTERS_H
#define MZLIB_CONVERTERS_H

#include <string_view>
#include <filesystem>

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

#ifdef QSTRING_H

template<>
inline QString convert(
   const std::wstring_view& value)
{
   // inefficient but I don't know how else to do it...
   return QString::fromStdWString(std::wstring(value));
}

template<>
inline QString convert(
   const std::wstring& value)
{
   // inefficient but I don't know how else to do it...
   return QString::fromStdWString(value);
}

template<>
inline std::filesystem::path convert(
   const QString& value)
{
   return std::filesystem::path{value.toStdWString()};
}

template<>
inline QString convert(
   const std::filesystem::path& path)
{
   return QString::fromStdWString(path.wstring());
}

template<>
inline std::wstring convert(
   const QByteArray& value)
{
   // is QByteArray always UTF8? There is no fromUtf16 ...
   QString q_string = QString::fromUtf8(value);
   return q_string.toStdWString();
}

template<>
inline std::string convert(
   const QByteArray& value)
{
   // is QByteArray always UTF8? There is no fromUtf16 ...
   QString q_string = QString::fromUtf8(value);
   return q_string.toStdString();
}

template<>
inline QByteArray convert(
   const std::wstring& value)
{
   QByteArray converted = QString::fromStdWString(value).toUtf8();
   return converted;
}

template<>
inline QByteArray convert(
   const std::string& value)
{
   QByteArray converted = QString::fromStdString(value).toUtf8();
   return converted;
}

#endif // QSTRING_H

#ifdef QJSONVALUE_H

template<>
inline QJsonValue convert(
   const std::wstring& value
   )
{
   return QJsonValue(QString::fromStdWString(value));
}

#endif // QJSONVALUE_H

} // namespace mzlib



#endif // MZLIB_CONVERTERS_H