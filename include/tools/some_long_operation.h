//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_SOME_LONG_OPERATION_H
#define MZLIB_SOME_LONG_OPERATION_H

#include <chrono>

namespace mzlib {
    
// When you need a processor busy for some defined length of time.
void some_long_operation(std::chrono::milliseconds duration)
{
   auto end_time = std::chrono::high_resolution_clock::now() + duration;
   volatile long double j = 3.8724365871627836;
   while (std::chrono::high_resolution_clock::now() < end_time)
      j = j / 0.38064852124534;
}

} // namespace

#endif // MZLIB_SOME_LONG_OPERATION_H
