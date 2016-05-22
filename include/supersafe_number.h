// 
// Author: Matej Zavrsnik (matejzavrsnik.com)
//

#ifndef SUPERSAFE_NUMBER_H
#define	SUPERSAFE_NUMBER_H

#include <vector>
#include <exception>

#include "utilities.h"

namespace mzlib
{

class compromised_number : public std::exception {};

template <typename T>
class csupersafe_number
{
private:

    const std::vector<double> m_keys;
    // not the first data in memory layout
    const T m_number; // important value
    const std::vector<double> m_controls;

    double calculate_control_value(const unsigned short index) const 
    {
        return (m_number + m_keys[index]);
    }

public:

  csupersafe_number(const T number) :
    m_keys{
      util::get_random_double(),
      util::get_random_double()},
    m_number{number},
    m_controls{
      calculate_control_value(0),
      calculate_control_value(1)}
  {
  }

  operator T() const
  {
    if(util::dbl(calculate_control_value(0)).equals(m_controls[0]) &&
       util::dbl(calculate_control_value(1)).equals(m_controls[1]))
    {
      // passed integrity control!
      return m_number;
    }
    else
    {
      // Didn't pass integrity control!
      // Nice try, Illuminati! HHAHAahha!!!11
      throw compromised_number(); // Abort the mission!
    }
  }

};

} // namespace

#endif	/* SUPERSAFE_NUMBER_H */

