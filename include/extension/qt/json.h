//
// Copyright (c) 2021 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_QT_JSON_H
#define MZLIB_QT_JSON_H

#include "../../lang/exceptions.h"
#include <string>

// Needs a bunch of QT includes before this compiles, I am using QJSONDOCUMENT_H, which defined
// when you include <QJsonDocument> as a hint that QT includes were done.
#ifdef QJSONDOCUMENT_H

namespace mzlib
{

inline QJsonObject
get_json_object (const std::wstring& json_string)
{
   auto byteArray = QString::fromStdWString(json_string).toUtf8();
   QJsonParseError parseError;
   QJsonDocument json_document = QJsonDocument::fromJson(byteArray, &parseError);
   if (parseError.error != QJsonParseError::NoError)
      throw mzlib::exception::parse_error(parseError.errorString().toStdString());
   QJsonObject root_object = json_document.object();
   return root_object;
}


inline QJsonValue
read_json_value (
   const QJsonObject& json_object,
   const QString key
)
{
   if (!json_object.contains(key))
      throw mzlib::exception::parse_error(
         std::string("Tried to read ") + key.toStdString() + std::string(" from settings file but it wasn't there.")
      );

   return json_object.value(key);
}

inline std::wstring
read_string (
   const QJsonObject& json_object,
   const QString key
)
{
   QJsonValue json_value = read_json_value(json_object, key);

   if (!json_value.isString())
      throw mzlib::exception::parse_error(
         std::string("Tried to read ") + key.toStdString() + std::string(" as string, but it isn't a string.")
      );

   std::wstring value = json_value.toString().toStdWString();
   return value;
}

inline QJsonArray
read_array (
   const QJsonObject& json_object,
   const QString key
)
{
   QJsonValue json_value = read_json_value(json_object, key);

   if (!json_value.isArray())
      throw mzlib::exception::parse_error(
         std::string("Tried to read ") + key.toStdString() + std::string(" as array, but it isn't an array.")
      );

   return json_value.toArray();
}

template <typename Number>
std::vector<Number>
read_as_numbers (QJsonArray arr)
{
   std::vector<Number> numbers;
   for (auto number: arr)
      if (!number.isDouble())
         throw mzlib::exception::parse_error("expected only numbers");
      else
      {
         if constexpr(std::is_integral_v<Number>)
            numbers.push_back(number.toInt());
         else
            numbers.push_back(number.toDouble());
      }

   return numbers;
}

} // namespace

#endif // QJSONDOCUMENT_H

#endif //MZLIB_QT_JSON_H