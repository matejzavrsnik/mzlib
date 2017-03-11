//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_SUPERSAFE_NUMBER_H
#define MZLIB_SUPERSAFE_NUMBER_H

#include <vector>
#include <exception>

#include "utils/random.h"
#include "lang/dbl.h"

namespace mzlib {

class compromised_number : public std::exception {};

template <typename T>
class supersafe_number
{

private:

   const std::vector<double> m_keys;
   // not the first data in memory layout
   const T m_number; // important value
   const std::vector<double> m_controls;

   double calculate_control_value (const unsigned short index) const 
   {
       return (m_number + m_keys[index]);
   }

public:

   supersafe_number (const T number) :
      m_keys{
         get_random_double(),
         get_random_double()},
      m_number{number},
      m_controls{
         calculate_control_value(0),
         calculate_control_value(1)}
   {
   }

   operator T () const
   {
      if (dbl(calculate_control_value(0)).equals(m_controls[0]) &&
          dbl(calculate_control_value(1)).equals(m_controls[1]))
      {
         // passed integrity control!
         return m_number;
      }
      else {
         // Didn't pass integrity control!
         // Nice try, Illuminati! HHAHAahha!!!11
         throw compromised_number(); // Abort the mission!
      }
   }

};

} // namespace

#endif /* MZLIB_SUPERSAFE_NUMBER_H */

