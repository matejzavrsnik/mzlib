//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_RANGE_IS_WITHIN_H
#define MZLIB_RANGE_IS_WITHIN_H

namespace mzlib {
   
template<typename Range>
bool is_within (const Range& lhs, const Range& rhs)
{
   return (
      lhs.begin() <= rhs.begin() &&
      lhs.end() >= rhs.end());
}

} // namespace

#endif // MZLIB_RANGE_IS_WITHIN_H
