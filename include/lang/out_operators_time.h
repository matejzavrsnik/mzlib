//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_OUT_OPERATORS_TIME_H
#define MZLIB_OUT_OPERATORS_TIME_H

#include <chrono>
#include <ostream>


#define MZ_OUT_OPERATOR_TIME_DEF(q_stream, q_unit, q_symbol) \
inline q_stream & operator<< (q_stream & stream, q_unit duration) \
{ \
   return stream << duration.count() << q_symbol; \
}

MZ_OUT_OPERATOR_TIME_DEF( std::ostream, std::chrono::nanoseconds,  "ns"  )
MZ_OUT_OPERATOR_TIME_DEF( std::ostream, std::chrono::microseconds, "us"  )
MZ_OUT_OPERATOR_TIME_DEF( std::ostream, std::chrono::milliseconds, "ms"  )
MZ_OUT_OPERATOR_TIME_DEF( std::ostream, std::chrono::seconds,      "s"   )
MZ_OUT_OPERATOR_TIME_DEF( std::ostream, std::chrono::minutes,      "min" )
MZ_OUT_OPERATOR_TIME_DEF( std::ostream, std::chrono::hours,        "h"   )

#undef MZ_OUT_OPERATOR_TIME_DEF

#endif /* MZLIB_OUT_OPERATORS_TIME_H */

