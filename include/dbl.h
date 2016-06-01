//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef DBL_H
#define	DBL_H

#include <cmath>
#include <limits>

namespace mzlib {
namespace util {

// to compare doubles for equality
class dbl
{

private:

   double m_val;
   double m_compared_to;
        
public:
        
   explicit dbl (double val) : 
      m_val(val),
      m_compared_to(val)
   {
   }
        
   dbl& equals (double val) 
   {
      m_compared_to = val;
      return *this;
   }
        
   operator bool () const 
   {
      const double delta = std::abs(m_val-m_compared_to);
      const double magnitude_candidate = std::abs(m_val+m_compared_to);
      const double magnitude = (magnitude_candidate >= 1 ? magnitude_candidate : 1);
      const int units_in_last_place = 4;
      const double allowed_delta = std::numeric_limits<double>::epsilon() * magnitude * units_in_last_place;
      return delta < allowed_delta || delta < std::numeric_limits<double>::min();
   }
        
   bool within_epsilon (double eps = 1e-10) const 
   {
      return std::abs(m_val-m_compared_to) <= eps;
   }

};

} } // namespace mzlib::util

#endif	/* DBL_H */

