//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_GET_SUBSTRING_H
#define MZLIB_GET_SUBSTRING_H

namespace mzlib {

inline std::string_view get_substring_between (
   std::string_view str, 
   std::string_view start, 
   std::string_view end)
{
   std::string_view result;
   
   size_t pos_start = str.find(start);
   if (pos_start != std::string::npos)
      pos_start += start.length();
   
   size_t pos_end = str.find(end, pos_start);
   
   if (pos_start != std::string::npos && 
       pos_end   != std::string::npos) 
   {
      if (pos_end < pos_start) {
         std::swap(pos_start, pos_end);
      }
      result = str.substr(pos_start, pos_end-pos_start);
   }
   return result;
}

} // namespace

#endif // MZLIB_GET_SUBSTRING_H
