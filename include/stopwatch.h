//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_STOPWATCH_H
#define MZLIB_STOPWATCH_H

#include <chrono>
#include <ctime>

namespace mzlib {

class stopwatch
{
   
   struct tmoment
   {
      std::clock_t m_cpu_clock;
      std::chrono::time_point<std::chrono::high_resolution_clock> m_wall_clock;
   };
   
   std::vector<tmoment> m_moments;
   
   tmoment get_now ()
   {
      tmoment now;
      now.m_cpu_clock = std::clock();
      now.m_wall_clock = std::chrono::high_resolution_clock::now();
      return now;
   }
   
   size_t get_last_entry_marker ()
   {
      return m_moments.size()-1;
   }
   
public:
   
   size_t start()
   {
      m_moments.clear();
      return mark();
   }
   
   size_t stop ()
   {
      return mark();
   }
   
   double get_duration ()
   {
      return get_wall_clock (0, get_last_entry_marker() );
   }
   
   size_t mark ()
   {
      m_moments.push_back(get_now());
      return get_last_entry_marker();
   }
   
   double get_cpu_clock (size_t start_marker, size_t stop_marker)
   {
      return ((m_moments[stop_marker] .m_cpu_clock - 
               m_moments[start_marker].m_cpu_clock)
             / CLOCKS_PER_SEC) * 1000.0;
   }
   
   double get_wall_clock (size_t start_marker, size_t stop_marker)
   {
      return std::chrono::duration<double, std::milli>
             (m_moments[stop_marker] .m_wall_clock - 
              m_moments[start_marker].m_wall_clock).count();
   }

};

} // namespaces

#endif /* MZLIB_STOPWATCH_H */

