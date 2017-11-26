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
      j /= 0.38064852124534;
}

} // namespace

#endif // MZLIB_SOME_LONG_OPERATION_H

#ifdef MZLIB_SOME_LONG_OPERATION_TESTS_H
#undef MZLIB_SOME_LONG_OPERATION_TESTS_H

using namespace std::chrono_literals;

TEST(some_long_operation, demo) 
{
   auto start_time = std::chrono::high_resolution_clock::now();
   mzlib::some_long_operation(20ms);
   auto end_time = std::chrono::high_resolution_clock::now();
   auto duration = end_time - start_time;
   ASSERT_TRUE(21ms > duration);
   ASSERT_TRUE(19ms < duration);
}

#endif // MZLIB_SOME_LONG_OPERATION_TESTS_H
