//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_TWOWAY_STREAMBUF_H
#define	MZLIB_TWOWAY_STREAMBUF_H

#include <memory>

namespace mzlib {

// This is a buffered two-way streambuf that enables in streams and out streams
// from the same buffer. It is useful for unit tests. If you need it for other
// purposes you probably need to think harder about the problem.

// This is a minimal implementation; it doesn't properly do eof for a start.
// If it ever grows up it can become circular buffer for native C++ streams!
   
template <typename TYPE, typename TRAITS, typename ALLOCATOR = std::allocator<TYPE>>
class basic_twoway_streambuf : public std::basic_streambuf<TYPE, TRAITS>
{
   
private:

   TYPE* m_buffer;
   std::streamsize m_buffer_size;
   ALLOCATOR m_allocator;

public:
   
   basic_twoway_streambuf (std::streamsize buffer_size) :
      m_buffer_size(buffer_size)
   {
      m_buffer = m_allocator.allocate(m_buffer_size);
        
      TYPE* beginning = m_buffer;
      TYPE* next = m_buffer;
      TYPE* end = m_buffer + (m_buffer_size - 1);
        
      this->setg(beginning, next, end); // setup get pointer
      this->setp(beginning, end); // setup put pointer
   }

   virtual ~basic_twoway_streambuf ()
   {
      m_allocator.deallocate(m_buffer, m_buffer_size);
   }
    
   basic_twoway_streambuf (const basic_twoway_streambuf&) = delete;
   basic_twoway_streambuf& operator= (const basic_twoway_streambuf&) = delete;
    
};

// Convenient types

using twoway_streambuf = basic_twoway_streambuf<char, std::char_traits<char>>;

} // namespace mzlib

#endif	/* MZLIB_TWOWAY_STREAMBUF_H */

