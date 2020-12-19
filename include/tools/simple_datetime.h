//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_SIMPLE_DATETIME_H
#define MZLIB_SIMPLE_DATETIME_H

#include "time_probe.h"
#include "time_operations.h"

namespace mzlib
{

bool is_leap_year(int year)
{
   return (year % 4 == 0 && year % 100 != 0 || year % 400 == 0);
}

int days_in_month(int month, int year)
{
   if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
      return 31;

   if (month == 4 || month == 6 || month == 9 || month == 11)
      return 30;

   if (month == 2 && is_leap_year(year))
      return 29;

   return 28;
}

/**
 * @brief Similar to std::tm but simplified.
 * @details Similar to std::tm, but without any timezone information or week day, or daylight saving time. The motivation
 * for this separate structure was so that I could implement some functionality on top of plain six integers for year,
 * month, etc. Functionality in question are subtraction, comparison, ability to encapsulate those six integers into
 * a higher abstraction, etc. The reason why I didn't want to use std::tm is that if I wrote an operator> for it I would
 * have to account for timezones and whatnot or risk misleading the users of the operator>, so instead I wanted something
 * simple that is good enough.
 * @details In addition, because of the std::tm quirk that year has 1900 subtracted from it and that
 * months are from 0-11, I had to write conversions between systems dealing with real year number and std::tm's year
 * number. With this I can avoid the conversion and it simplified some of my code already.
 * @warning Incorectly models timezones, daylight savings, leap seconds. Perhaps more, but at least those I am aware of.
 * @warning No checks are done whether values are valid. This is just a plain grouping of them.
 * @example
 * \code{.cpp}
 * mzlib::time_probe probe;
 * simple_datetime next_lunar_perigee{2029, 8, 10, 0, 0, 0};
 * simple_datetime current_time = probe.get_today_local();
 * simple_datetime time_until_lunar_perigee = next_lunar_perigee - current_time;
 * \endcode
 */
struct simple_datetime
{
   /**
    * @brief Constructor that converts from std::tm
    * @example
    * \code{.cpp}
    * mzlib::time_probe probe;
    * simple_datetime current_time = probe.get_today_local();
    * \endcode
   */
   explicit simple_datetime(
      const std::tm& tm_time
      )
   {
      year = tm_time.tm_year + 1900;
      month = tm_time.tm_mon + 1;
      day = tm_time.tm_mday;
      hour = tm_time.tm_hour;
      minute = tm_time.tm_min;
      second = tm_time.tm_sec;
   }

   /**
    * @brief Constructor that initialises all information in one call.
    * @example
    * \code{.cpp}
    * simple_datetime next_lunar_perigee{2029, 8, 10, 0, 0, 0};
    * \endcode
   */
   simple_datetime(int _year, int _month, int _day, int _hour, int _minute, int _second)
   {
      year = _year;
      month = _month;
      day = _day;
      hour = _hour;
      minute = _minute;
      second = _second;
   }

   int year;
   int month;
   int day;
   int hour;
   int minute;
   int second;
};


bool operator> (const simple_datetime& lhs, const simple_datetime& rhs)
{
   if (lhs.year > rhs.year) return true;
   if (lhs.year < rhs.year) return false;

   if (lhs.month > rhs.month) return true;
   if (lhs.month < rhs.month) return false;

   if (lhs.day > rhs.day) return true;
   if (lhs.day < rhs.day) return false;

   if (lhs.hour > rhs.hour) return true;
   if (lhs.hour < rhs.hour) return false;

   if (lhs.minute > rhs.minute) return true;
   if (lhs.minute < rhs.minute) return false;

   if (lhs.second > rhs.second) return true;
   if (lhs.second < rhs.second) return false;

   return false;
}

bool operator== (const simple_datetime& lhs, const simple_datetime& rhs)
{
   return
      lhs.year == lhs.year &
         lhs.month == lhs.month &&
         lhs.day == lhs.day &&
         lhs.hour == lhs.hour &&
         lhs.minute == lhs.minute &&
         lhs.second == lhs.second;
}

bool operator!= (const simple_datetime& lhs, const simple_datetime& rhs)
{
   return !(lhs == rhs);
}

bool operator< (const simple_datetime& lhs, const simple_datetime& rhs)
{
   return (lhs != rhs) && !(lhs > rhs);
}

/**
 * @brief Calculates difference between two date/times.
 * @details The difference isn't simply expressed in number of days or seconds or whatever, but actually says how many
 * years, months, ... are between the two date/times. Standard library and boost::date_time both have facilities to
 * calculate number of days, but I didn't find a function that would calculate the whole thing.
 * @warning I am not sure if it works correctly if you subtract future date from past date. It was meant to be used just
 * one way because I didn't need it that good yet. It was simple enough to do a comparison first before the call to this,
 * so I haven't done it.
 * @return Difference between the two date/times in terms of years, months, days, ..., seconds.
 */
simple_datetime
operator- (
   const simple_datetime& lhs, /**< [in] Bigger date/time, the future */
   const simple_datetime& rhs /**< [in] Smaller date/time, the past */
   )
{
   simple_datetime diff = lhs;

   diff.year -= rhs.year;
   diff.month -= rhs.month;
   diff.day -= rhs.day;
   diff.hour -= rhs.hour;
   diff.minute -= rhs.minute;
   diff.second -= rhs.second;

   if (diff.second < 0)
   {
      diff.minute -= 1;
      diff.second += 60;
   }
   if (diff.minute < 0)
   {
      diff.hour -= 1;
      diff.minute += 60;
   }
   if (diff.hour < 0)
   {
      diff.day -= 1;
      diff.hour += 24;
   }

   if (diff.day < 0)
   {
      diff.month -= 1;
   }
   if (diff.month < 0)
   {
      diff.year -= 1;
      diff.month += 12;
   }
   if (diff.day < 0)
   {
      diff.day += days_in_month(diff.month, rhs.year);
   }

   return diff;
}

/**
 * @brief Converter from simple_datetime to std::tm
 * @details Can be used to convert, but also to instantiate std::tm in one go rather than initialise each structure
 * member separately. Time probe is needed because std::tm contains more information than simple_datetime and this
 * conversion function will assume it needs to contain information as returned by std::localtime in current locale,
 * which is what time_probe can do in a way that is unit testable.
 * @example
 * \code{.cpp}
 * std::tm tm_time{ to_tm{ time_probe, {2029, 8, 10, 0, 0, 0} } };
 * \endcode
 * @return Manufactured std::tm structure.
 */
std::tm
to_tm(
   const mzlib::time_probe_interface& time_probe, /**< [in] To get information about timezone and such */
   const simple_datetime& simple_dt /**< [in] simple_datetime that needs conversion */)
{
   std::tm tm_time = mzlib::reset_except_local(time_probe.get_today_local());
   tm_time.tm_year = simple_dt.year-1900;
   tm_time.tm_mon = simple_dt.month-1;
   tm_time.tm_mday = simple_dt.day;
   tm_time.tm_hour = simple_dt.hour;
   tm_time.tm_min = simple_dt.minute;
   tm_time.tm_sec = simple_dt.second;
   return tm_time;
}

} // namespace

#endif
