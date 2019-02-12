//
// Copyright (c) 2019 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_TIME_OPERATIONS_H
#define MZLIB_TIME_OPERATIONS_H

#include "../nature/units.h"

#include <ctime>

namespace mzlib {

class tm_calc
{
   
private:
   
   std::time_t m_time;
   double m_number;
   
   std::tm add_to_time(std::time_t time_difference)
   {
      m_time += time_difference;
      return *std::localtime(&m_time);
   }
   
public:
   
   tm_calc(std::tm t) : 
      m_time(std::mktime(&t)),
      m_number(0) 
   {}
  
   tm_calc& plus(double n) 
   { 
      m_number = n; 
      return *this; 
   }
   
   tm_calc& minus(double n) 
   { 
      m_number = -n; 
      return *this; 
   }
   
   std::tm seconds()
   {
      using namespace units;
      return add_to_time( m_number * 1.0_s );
   }
   
   std::tm minutes()
   {
      using namespace units;
      return add_to_time( m_number * 1.0_min );
   }
   
   std::tm hours()
   {
      using namespace units;
      return add_to_time( m_number * 1.0_h );
   }
   
   std::tm days()
   {
      using namespace units;
      return add_to_time( m_number * 1.0_day );
   }
   
   std::tm years()
   {
      using namespace units;
      return add_to_time( m_number * 1.0_julian_year );
   }
   
};

} // namespace

#endif // MZLIB_TIME_OPERATIONS_H
