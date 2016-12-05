//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_BINARY_OPTIONS_H
#define	MZLIB_BINARY_OPTIONS_H

// More readable substitutes for simple booleans for specific meanings.
// Let's see if I am correct in that I'll need more of them in the future and that
// they'll make reading my programs a joyful experience.

namespace mzlib {
namespace option {
   
class binary_option
{
   
public:
   
   enum /*not class*/ named_options { no, yes } m_named_value = no;

   binary_option () : 
      m_named_value(no)
   {
   }
   
   // create from option
   binary_option (named_options named_value) : 
      m_named_value(named_value)
   {
   }
   
   // compare to option
   bool operator== (named_options named_value) const
   {
      return m_named_value == named_value;
   }

   // convert from bool
   binary_option (bool boolean_value) :
      m_named_value(boolean_value ? yes : no)
   {
   }
   
   // convert to bool
   operator bool () const
   {
      return m_named_value == yes;
   }

};

// a generator to create real ones
#define MZLIB_GENERATE_NEW_BINARY_OPTION(name) \
class name : public binary_option \
{ \
public: \
   using binary_option::binary_option; \
};

MZLIB_GENERATE_NEW_BINARY_OPTION( recursive      )
MZLIB_GENERATE_NEW_BINARY_OPTION( include_hidden )
MZLIB_GENERATE_NEW_BINARY_OPTION( set            )
MZLIB_GENERATE_NEW_BINARY_OPTION( exists         )
MZLIB_GENERATE_NEW_BINARY_OPTION( removed        )
MZLIB_GENERATE_NEW_BINARY_OPTION( expanded       )
MZLIB_GENERATE_NEW_BINARY_OPTION( changed        )
MZLIB_GENERATE_NEW_BINARY_OPTION( stop           )

#undef MZLIB_GENERATE_NEW_BINARY_OPTION

}} // namespace

#endif	/* MZLIB_BINARY_OPTIONS_H */

