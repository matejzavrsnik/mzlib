//
// Copyright (c) 2019 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_TIME_PROBE_H
#define MZLIB_TIME_PROBE_H

#include <ctime>

namespace mzlib {

// The point of having this fairly complicated structure
// in place just to effectively call two lines of code
// in the end is testability. When testing functions that 
// deal with time it is better to have time queries mocked.
   
class time_probe_interface
{
   
public:
   
   virtual std::tm get_today_local() = 0;
   
};

class time_probe : public time_probe_interface
{
   
public:
   
   std::tm get_today_local() override
   {
      std::time_t today = std::time(nullptr);
      return *std::localtime(&today);
   }
   
};



} // namespace

#endif // MZLIB_TIME_PROBE_H
