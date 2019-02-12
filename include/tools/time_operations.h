//
// Copyright (c) 2019 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_TIME_OPERATIONS_H
#define MZLIB_TIME_OPERATIONS_H

#include "../nature/units.h"
#include "time_probe.h"

#include <ctime>
#include <cstring>
#include <string>
#include <sstream>
#include <iomanip>

namespace mzlib {

inline std::tm reset_except_local(std::tm time)
{
   // leave these alone:
   //time.tm_gmtoff;
   //time.tm_isdst;
   //time.tm_zone;
   
   time.tm_sec = 0;	
   time.tm_min = 0;
   time.tm_hour = 0;
   time.tm_mon = 0;
   time.tm_year = 0;
   time.tm_mday = 0;
   time.tm_wday = 0;
   time.tm_yday = 0;

   return time;
}
   
inline std::string convert_to_string(
   std::tm date, 
   std::string_view date_format)
{
   std::stringstream ss;
   ss << std::put_time(&date, date_format.data());
   std::string today = ss.str();
   return today;
}

inline std::tm convert_from_string(
   std::string_view str_date, 
   std::string_view date_format,
   const mzlib::time_probe_interface& time_probe)
{
   std::istringstream ss_date(str_date.data());
   
   // assume string represents local time
   // fill in local values
   std::tm tm_date = reset_except_local(time_probe.get_today_local());
   
   // then change to what the format string requested
   ss_date >> std::get_time(&tm_date, date_format.data());
   return tm_date;
}

inline std::tm convert_to_local_time(
   std::tm utc_time)
{
   std::time_t utc_time_t = std::mktime(&utc_time);
   return *std::localtime(&utc_time_t);
}

inline double days_between(
   std::tm time_end, 
   std::tm time_beg)
{
   using namespace units;
   
   double passed_time = 
      std::difftime(
         std::mktime(&time_beg), 
         std::mktime(&time_end));
   
   double days = passed_time / 1.0_day;
   return days;
}

inline bool equals(
   std::tm t1, 
   std::tm t2)
{
   return 
      t1.tm_gmtoff == t2.tm_gmtoff &&
      t1.tm_hour   == t2.tm_hour   &&
      t1.tm_isdst  == t2.tm_isdst  &&	
      t1.tm_mday   == t2.tm_mday   &&
      t1.tm_min    == t2.tm_min    &&
      t1.tm_mon    == t2.tm_mon    &&
      t1.tm_sec    == t2.tm_sec    &&	
      t1.tm_wday   == t2.tm_wday   &&
      t1.tm_yday   == t2.tm_yday   &&	
      t1.tm_year   == t2.tm_year   &&	
      std::strcmp(t1.tm_zone, t2.tm_zone);
}

} // namespace

#endif // MZLIB_TIME_OPERATIONS_H
