//
// Copyright (c) 2019 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "time_operations.h"

#include "gtest/gtest.h"

std::tm create_some_time()
{
   std::tm some_time;
   some_time.tm_hour = 19;	
   some_time.tm_isdst = 0;	
   some_time.tm_mday = 10;	
   some_time.tm_min = 20;
   some_time.tm_mon = 1;
   some_time.tm_sec = 21;	
   some_time.tm_wday = 0;
   some_time.tm_yday = 40;	
   some_time.tm_year = 119;
//  Windows
#ifndef _WIN32
   some_time.tm_gmtoff = 0;
   some_time.tm_zone = "GMT";
#endif
   return some_time;
}

TEST(convert_to_string, demo) 
{
   std::tm some_time = create_some_time();
   
   std::string str_time = mzlib::convert_to_string(
      some_time, "%Y %m %d %H:%M");

   ASSERT_EQ(str_time, "2019 02 10 19:20");
}

TEST(convert_from_string, demo) 
{
   std::string_view str_some_time = "2019 02 10 19:20";
   std::tm tm_some_time = create_some_time();
   
   std::tm tm_returned_time = mzlib::convert_from_string(
      str_some_time, "%Y %m %d %H:%M", mzlib::time_probe{});
   
   ASSERT_EQ(tm_returned_time.tm_year, tm_some_time.tm_year);
   ASSERT_EQ(tm_returned_time.tm_mon, tm_some_time.tm_mon);
   ASSERT_EQ(tm_returned_time.tm_mday, tm_some_time.tm_mday);
   ASSERT_EQ(tm_returned_time.tm_hour, tm_some_time.tm_hour);
   ASSERT_EQ(tm_returned_time.tm_min, tm_some_time.tm_min);
   ASSERT_EQ(tm_returned_time.tm_sec, 0);
}

TEST(days_between, basic)
{
   std::tm start = mzlib::convert_from_string(
      "2019 02 10 19:20", "%Y %m %d %H:%M", mzlib::time_probe{});
   
   std::tm end = mzlib::convert_from_string(
      "2019 03 10 19:20", "%Y %m %d %H:%M", mzlib::time_probe{});
   
   double days_between = mzlib::days_between(start, end);
   
   ASSERT_DOUBLE_EQ(days_between, 28);
}

TEST(days_between, negative)
{
   std::tm start = mzlib::convert_from_string(
      "2019 02 10 19:20", "%Y %m %d %H:%M", mzlib::time_probe{});
   
   std::tm end = mzlib::convert_from_string(
      "2019 03 10 19:20", "%Y %m %d %H:%M", mzlib::time_probe{});
   
   double days_between = mzlib::days_between(end, start);
   
   ASSERT_DOUBLE_EQ(days_between, -28);
}

TEST(days_between, fraction_difference)
{
   std::tm start = mzlib::convert_from_string(
      "2019 02 10 19:20", "%Y %m %d %H:%M", mzlib::time_probe{});
   
   std::tm end = mzlib::convert_from_string(
      "2019 03 11 07:20", "%Y %m %d %H:%M", mzlib::time_probe{});
   
   double days_between = mzlib::days_between(start, end);
   
   ASSERT_DOUBLE_EQ(days_between, 28.5);
}